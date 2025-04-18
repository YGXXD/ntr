#include "../../inc/core/nobject.hpp"
#include "../../inc/type/ntype.hpp"

namespace ntr
{

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
    _type = other._type;
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

nobject nobject::new_(const ntype* type)
{
    nobject object(type);
    if (object.type()->ops()->construct)
        object.type()->ops()->construct(object.data());
    else
        throw std::runtime_error("nobject::new_ : construct operation not found");
    return object;
}

nobject nobject::new_copy_(const ntype* type, const void* const data)
{
    nobject object(type);
    if (object.type()->ops()->copy)
        object.type()->ops()->copy(object.data(), data);
    else
        throw std::runtime_error("nobject::new_copy_ : copy operation not found");
    return object;
}

nobject nobject::new_move_(const ntype* type, void* data)
{
    nobject object(type);
    if (object.type()->ops()->move)
        object.type()->ops()->move(object.data(), data);
    else
        throw std::runtime_error("nobject::new_move_ : move operation not found");
    return object;
}

} // namespace ntr
