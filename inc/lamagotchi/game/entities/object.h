#ifndef OBJECT_H
#define OBJECT_H

#include <cstdint>
#include <string>
#include <string_view>

namespace Game
{

class Object
{
public:
    Object() = default;
    explicit Object(const uint32_t objectId, std::wstring_view objectName);
    virtual ~Object() = default;

    uint32_t getObjectId() const;
    void setObjectId(const uint32_t objectId);
    std::wstring_view getObjectName() const;
    void setObjectName(const std::wstring_view objectName);

protected:
    uint32_t m_objectId = 0;
    std::wstring m_objectName = L"No name";
};

} // namespace Game

#endif // OBJECT_H
