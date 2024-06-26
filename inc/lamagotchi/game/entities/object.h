#ifndef OBJECT_H
#define OBJECT_H

#include <cstdint>
#include <string>
#include <string_view>

namespace Lamagotchi
{

namespace Game
{

class Object
{
public:
    uint32_t getObjectId() const;
    void setObjectId(const uint32_t objectId);
    std::wstring_view getObjectName() const;
    void setObjectName(const std::wstring_view objectName);
    std::wstring_view getObjectTitle() const;
    void setObjectTitle(const std::wstring_view objectTitle);

protected:
    Object() = default;
    explicit Object(const uint32_t objectId, std::wstring_view objectName);
    Object(const Object& other);
    Object(Object&& other) noexcept;
    Object& operator=(const Object& other);
    Object& operator=(Object&& other) noexcept;

protected:
    uint32_t m_objectId = -1;
    std::wstring m_objectName = L"No name";
    std::wstring m_objectTitle = L"No title";
};

} // namespace Game
} // namespace Lamagotchi

#endif // OBJECT_H
