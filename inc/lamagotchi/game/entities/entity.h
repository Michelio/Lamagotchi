#ifndef ENTITY_H
#define ENTITY_H

#include "object.h"

namespace Game
{

struct Vector2D
{
public:
    Vector2D() = default;
    explicit Vector2D(float x, float y);

public:
    float x = 0;
    float y = 0;
};

struct Vector3D : Vector2D
{
public:
    Vector3D() = default;
    explicit Vector3D(float x, float y, float z);

public:
    float z = 0;
};

class Entity : public Object
{
public:
    Entity();
    explicit Entity(const uint32_t objectId, std::wstring_view objectName, const Vector3D position);

    Vector3D getPosition() const;
    void setPosition(const Vector3D position);

protected:
    Vector3D m_position{};
};

} // namespace Game

#endif // ENTITY_H
