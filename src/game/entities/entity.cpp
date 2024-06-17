#include "game/entities/entity.h"

namespace Game
{

Vector2D::Vector2D(float x, float y = 0.0f) : x{x}, y{y}
{
}

Vector3D::Vector3D(float x, float y = 0.0f, float z = 0.0f) : Vector2D{x, y}, z{z}
{
}

Entity::Entity() : Object{}
{
}

Entity::Entity(const uint32_t objectId, std::wstring_view objectName, const Vector3D position)
    : Object{objectId, objectName}, m_position{position}
{
}

} // namespace Game
