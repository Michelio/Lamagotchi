#include "game/entities/object.h"

namespace Lamagotchi
{

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

std::wstring_view Object::getObjectTitle() const
{
    return m_objectTitle;
}

void Object::setObjectTitle(const std::wstring_view objectTitle)
{
    m_objectTitle = objectTitle;
}

} // namespace Game
} // namespace Lamagotchi
