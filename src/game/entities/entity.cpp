#include "game/entities/entity.h"
#include "game/entities/object.h"
#include <cstdint>
#include <string_view>

namespace Game 
{

Entity::Entity() : Object{}
{}

Entity::Entity(const uint32_t objectId, std::wstring_view objectName, const Vector3D position) : Object{objectId, objectName}, m_position{position}
{}

}
