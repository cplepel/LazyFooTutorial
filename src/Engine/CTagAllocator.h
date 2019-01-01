//--------------------------------------------------------------------------------------------------
//
// Copyright 2017 Cody Plepel, Cat Morgan, Matthew Grubb, Geoff Tucker
//
// SDL2 Used under the ZLIB license.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted 
// provided that the following conditions are met :
//
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and 
// the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions 
// and the following disclaimer in the documentation and / or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
// FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
// LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//----------------------------------------------------------------------------------------------
#pragma once

#include <mutex>
#include <array>
#include <cassert>
#include <utility>

template <typename TObject, size_t PoolSize>
class CTagAllocator;

template <typename TObject, size_t PoolSize>
class Tag {
public:
    Tag () : m_index(), m_counter() {}
    Tag (uint32_t index, uint32_t counter) : m_index{index}, m_counter{counter} {}
    bool IsAssigned () const { return m_counter > 0; }

private:
    friend CTagAllocator<TObject, PoolSize>;
    uint32_t m_index;
    uint32_t m_counter;
};

template <typename TObject, size_t PoolSize>
class CTagRecycler {
public:
    using TagType = Tag<TObject, PoolSize>;
    using TagAllocator = CTagAllocator<TObject, PoolSize>;

    CTagRecycler () : m_tag() {}
    TagType Tag () const { return m_tag; }

    static TObject* Create ();
    static TObject* Deref (TagType tag);
    static void Destroy (TagType tag);

private:
    TagType m_tag;
};

template <typename TObject, size_t PoolSize>
class CTagAllocator {
public:
    static CTagAllocator& Get () {
        static CTagAllocator allocator;
        return allocator;
    }

    using Tag = Tag<TObject, PoolSize>;

    CTagAllocator () {
        InitPool();
    }

    CTagAllocator (const CTagAllocator&) = delete;
    CTagAllocator (CTagAllocator&&) = delete;

    virtual ~CTagAllocator () {}

    CTagAllocator& operator= (const CTagAllocator&) = delete;
    CTagAllocator& operator= (CTagAllocator&&) = delete;

    Tag Create () {
        return Create<>();
    }

    TObject* Deref (Tag tag) {
        // $NOTE CPP: This might be very expensive and a bad spot for a mutex.
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
TObject* CTagRecycler<TObject, PoolSize>::Create () {
    const TagType tag = CTagAllocator<TObject, PoolSize>::Get().Create();
    TObject* created = CTagAllocator<TObject, PoolSize>::Get().Deref(tag);
    if (auto* recycler = static_cast<CTagRecycler<TObject, PoolSize>*>(created)) {
        recycler->m_tag = tag;
    }
    return created;
}

template <typename TObject, size_t PoolSize>
TObject* CTagRecycler<TObject, PoolSize>::Deref (TagType tag) {
    return TagAllocator::Get().Deref(tag);
}

template <typename TObject, size_t PoolSize>
void CTagRecycler<TObject, PoolSize>::Destroy (TagType tag) {
    return TagAllocator::Get().Deallocate(tag);
}
