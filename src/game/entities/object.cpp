#include "game/entities/object.h"

#include <cstdint>
#include <string>
#include <string_view>

namespace Game 
{

Object::Object(const uint32_t objectId, std::wstring_view objectName) : m_objectId{objectId}, m_objectName{objectName}
{

}

uint32_t Object::getObjectId() const
{
    return m_objectId;
}

void Object::setObjectId(const uint32_t objectId)
{
    m_objectId = objectId;
}

std::wstring_view Object::getObjectName() const
{
    return m_objectName;
}

void Object::setObjectName(const std::wstring_view objectName)
{
    m_objectName = objectName;
}

}
