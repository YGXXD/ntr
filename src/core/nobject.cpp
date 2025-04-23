#include "../../inc/core/nobject.hpp"
#include "../../inc/type/ntype.hpp"

namespace ntr
{

nobject::nobject(const class ntype* type) : _type(type), _bytes()
{
}

nobject::nobject(nobject&& other) : _type(other._type)
{
    _bytes = other._bytes;
    other._bytes[0] = static_cast<std::byte>(0);
    other._bytes[1] = static_cast<std::byte>(0);
}

nobject& nobject::operator=(nobject&& other)
{
    if (this != &other)
    {
        nobject temp(std::move(other));
        std::swap(_type, temp._type);
        std::swap(_bytes, temp._bytes);
    }
    return *this;
}

nobject::~nobject()
{
    if (is_init())
        type()->ops()->destruct(data());
    if (is_alloc() && is_heap())
        delete[] data();
}

nobject& nobject::alloc()
{
    if (is_alloc())
        throw std::runtime_error("nobject::allocate : object is already allocated");
    if (_type->size() > 0)
    {
        _bytes[0] = static_cast<std::byte>(1);
        if (is_heap())
        {
            std::byte* ptr = new std::byte[_type->size()];
            *reinterpret_cast<std::byte**>(_bytes.data() + 2) = ptr;
        }
    }
    return *this;
}

nobject& nobject::init()
{
    if (is_init())
        throw std::runtime_error("nobject::init : object is already initialized");
    if (is_alloc())
    {
        _bytes[1] = static_cast<std::byte>(1);
        if (type()->ops()->default_construct)
            type()->ops()->default_construct(data());
        else
            throw std::runtime_error(
                "nobject::init : default_construct operation not found");
    }
    return *this;
}

nobject& nobject::init_copy(const void* const value)
{
    if (is_init())
        throw std::runtime_error("nobject::init_copy : object is already initialized");
    if (is_alloc())
    {
        _bytes[1] = static_cast<std::byte>(1);
        if (type()->ops()->copy_construct)
            type()->ops()->copy_construct(data(), value);
        else
            throw std::runtime_error(
                "nobject::init_copy : copy_construct operation not found");
    }
    return *this;
}

nobject& nobject::init_move(void* value)
{
    if (is_init())
        throw std::runtime_error("nobject::init_move : object is already initialized");
    if (is_alloc())
    {
        _bytes[1] = static_cast<std::byte>(1);
        if (type()->ops()->move_construct)
            type()->ops()->move_construct(data(), value);
        else
            throw std::runtime_error(
                "nobject::init_move : move_construct operation not found");
    }
    return *this;
}

bool nobject::is_heap() const
{
    return _type->size() > _bytes.size() - 2;
}

bool nobject::is_alloc() const
{
    return static_cast<bool>(_bytes[0]);
}

bool nobject::is_init() const
{
    return static_cast<bool>(_bytes[1]);
}

std::byte* nobject::data()
{
    std::byte* ptr = _bytes.data() + 2;
    return is_heap() ? *reinterpret_cast<std::byte**>(ptr) : ptr;
}

const std::byte* nobject::data() const
{
    std::byte* ptr = const_cast<std::byte*>(_bytes.data() + 2);
    return is_heap() ? *reinterpret_cast<const std::byte**>(ptr) : ptr;
}

} // namespace ntr
