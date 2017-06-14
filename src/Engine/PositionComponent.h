#pragma once

struct PositionComponent {
    PositionComponent (float x, float y) : m_x{x}, m_y{y} {}
    float m_x{};
    float m_y{};
};