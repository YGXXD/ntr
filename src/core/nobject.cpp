#include "../../inc/core/nobject.hpp"
#include "../../inc/type/ntype.hpp"

namespace ntr
{

nobject nobject::new_(const ntype* type)
{
    nobject obj(type);
    if (obj.is_valid())
    {
        if (obj.type()->ops()->construct)
            obj.type()->ops()->construct(obj.data());
        else
            throw std::runtime_error("nobject::new_ : construct operation not found");
    }
    return obj;
}

nobject nobject::new_copy_(const ntype* type, const void* const data)
{
    nobject obj(type);
    if (obj.is_valid())
    {
        if (obj.type()->ops()->copy)
            obj.type()->ops()->copy(obj.data(), data);
        else
            throw std::runtime_error("nobject::new_copy_ : copy operation not found");
    }
    return obj;
}

nobject nobject::new_steal_(const ntype* type, void* data)
{
    nobject obj(type);
    if (obj.is_valid())
    {
        if (obj.type()->ops()->move)
            obj.type()->ops()->move(obj.data(), data);
        else
            throw std::runtime_error("nobject::new_move_ : move operation not found");
    }
    return obj;
}

nobject::nobject(const class ntype* type) : _type(type), _small_data()
{
    if (is_heap())
        _large_data = new std::byte[_type->size()];
    else if (_type->size() > 0)
        _small_data[0] = static_cast<std::byte>(1);
}

nobject::nobject(nobject&& other) : _type(other._type)
{
    if (is_heap())
    {
        _large_data = other._large_data;
        other._large_data = nullptr;
    }
    else
    {
        _small_data = other._small_data;
        other._small_data[0] = static_cast<std::byte>(0);
    }
}

nobject& nobject::operator=(nobject&& other)
{
    if (this != &other)
    {
        nobject temp(std::move(other));
        std::swap(_type, temp._type);
        if (is_heap())
            std::swap(_large_data, temp._large_data);
        else
            std::swap(_small_data, temp._small_data);
    }
    return *this;
}

nobject::~nobject()
{
    if (is_valid())
        type()->ops()->destruct(data());
    if (is_heap())
        delete[] _large_data;
}

bool nobject::is_heap() const
{
    return _type->size() > _small_data.size() - 1;
}

bool nobject::is_valid() const
{
    return is_heap() ? static_cast<bool>(_large_data) : static_cast<bool>(_small_data[0]);
}

std::byte* nobject::data()
{
    return is_heap() ? _large_data : _small_data.data() + 1;
}

const std::byte* nobject::data() const
{
    return is_heap() ? _large_data : _small_data.data() + 1;
}

} // namespace ntr
