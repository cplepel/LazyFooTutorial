#pragma once

#include <mutex>
#include <array>
#include <cassert>
#include <utility>

template <typename TObject, size_t PoolSize>
class TagAllocator;

template <typename TObject, size_t PoolSize>
class Tag {
public:
    Tag () : m_index(), m_counter() {}
    Tag (uint32_t index, uint32_t counter) : m_index{index}, m_counter{counter} {}
    bool IsAssigned () const { return m_counter > 0; }

private:
    friend TagAllocator<TObject, PoolSize>;
    uint32_t m_index;
    uint32_t m_counter;
};

template <typename TObject, size_t PoolSize>
class TagRecycler {
public:
    using TagType = Tag<TObject, PoolSize>;
    using TagAllocator = TagAllocator<TObject, PoolSize>;

    TagRecycler () : m_tag() {}
    TagType Tag () const { return m_tag; }

    static TObject* Create ();
    static TObject* Deref (TagType tag);
    static void Destroy (TagType tag);

private:
    TagType m_tag;
};

template <typename TObject, size_t PoolSize>
class TagAllocator {
public:
    static TagAllocator& Get () {
        static TagAllocator allocator;
        return allocator;
    }

    using Tag = Tag<TObject, PoolSize>;

    TagAllocator () {
        InitPool();
    }

    TagAllocator (const TagAllocator&) = delete;
    TagAllocator (TagAllocator&&) = delete;

    virtual ~TagAllocator () {}

    TagAllocator& operator= (const TagAllocator&) = delete;
    TagAllocator& operator= (TagAllocator&&) = delete;

    Tag Create () {
        return Create<>();
    }

    TObject* Deref (Tag tag) {
        std::lock_guard<std::mutex> lock(m_mutex);
        assert(tag.m_index >= 0 && tag.m_index < PoolSize);
        PoolNode& node = m_pool[tag.m_index];
        if (node.m_counter == tag.m_counter) {
            return &node.m_union.m_content.m_object;
        }
        return nullptr;
    }

    template <class... Args>
    Tag Create (Args&&... args) {
        std::lock_guard<std::mutex> lock(m_mutex);
        assert(m_firstAvailable);
        const Tag tag(m_firstAvailable - m_pool.data(), ++m_firstAvailable->m_counter);

        RefCountObject* obj = reinterpret_cast<RefCountObject*>(&m_firstAvailable->m_union);
        m_firstAvailable = m_firstAvailable->m_union.m_next;

        new(&obj->m_object) TObject(std::forward<Args>(args)...);
        ++obj->m_refCount;

        return tag;
    }

    void Deallocate (Tag tag) {
        std::lock_guard<std::mutex> lock(m_mutex);
        assert(tag.m_index >= 0 && tag.m_index < PoolSize);
        PoolNode& node = m_pool[tag.m_index];
        if (node.m_counter == tag.m_counter) {
            ++node.m_counter;
            node.m_union.m_content.m_refCount = 0;
            node.m_union.m_content.m_object.~TObject();
            node.m_union.m_next = m_firstAvailable;
            m_firstAvailable = &node;
        }
    }

private:
    struct RefCountObject {
        TObject m_object;
        uint32_t m_refCount;
    };
    struct PoolNode {
        union NodeUnion {
            RefCountObject m_content;
            PoolNode* m_next;
            NodeUnion () {}
            ~NodeUnion () {}
        } m_union;
        uint32_t m_counter;
        PoolNode () {}
        ~PoolNode () {}
    };
    std::array<PoolNode, PoolSize> m_pool;
    PoolNode* m_firstAvailable;
    std::mutex m_mutex;

    void InitPool () {
        m_firstAvailable = &m_pool[0];
        for (size_t i = 0; i < PoolSize - 1; ++i) {
            m_pool[i].m_union.m_next = &m_pool[i + 1];
        }
        m_pool[PoolSize - 1].m_union.m_next = nullptr;
    }
};

template <typename TObject, size_t PoolSize>
TObject* TagRecycler<TObject, PoolSize>::Create () {
    const TagType tag = TagAllocator::Get().Create();
    TObject* created = TagAllocator::Get().Deref(tag);
    if (auto* recycler = static_cast<TagRecycler<TObject, PoolSize>*>(created)) {
        recycler->m_tag = tag;
    }
    return created;
}

template <typename TObject, size_t PoolSize>
TObject* TagRecycler<TObject, PoolSize>::Deref (TagType tag) {
    return TagAllocator::Get().Deref(tag);
}

template <typename TObject, size_t PoolSize>
void TagRecycler<TObject, PoolSize>::Destroy (TagType tag) {
    return TagAllocator::Get().Deallocate(tag);
}
