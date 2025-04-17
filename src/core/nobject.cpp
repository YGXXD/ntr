#include "../../inc/core/nobject.hpp"
#include "../../inc/type/ntype.hpp"

namespace ntr
{

nobject::nobject(const nobject& other) : nobject()
{
    copy(other);
}

nobject::nobject(nobject&& other) : nobject()
{
    move(std::move(other));
}

nobject& nobject::operator=(const nobject& other)
{
    if (this != &other)
    {
        destruct();
        copy(other);
    }
    return *this;
}

nobject& nobject::operator=(nobject&& other)
{
    if (this != &other)
    {
        move(std::move(other));
    }
    return *this;
}

nobject::~nobject()
{
    destruct();
}

void nobject::copy(const nobject& other)
{
    if (other._type)
    {
        _type = other._type;
        if (_type->ops()->copy)
        {
            if (_type->size() <= sizeof(_small_data))
                _type->ops()->copy(_small_data, other._small_data);
            else
            {
                _large_data = new std::byte[_type->size()];
                _type->ops()->copy(_large_data, other._large_data);
            }
        }
        else
            throw std::runtime_error(std::string(_type->name()) +
                                     " has no copy operation");
    }
}

void nobject::move(nobject&& other)
{
    _type = other._type;
    other._type = nullptr;
    if constexpr (sizeof(_small_data) > sizeof(_large_data))
    {
        std::copy(other._small_data, other._small_data + sizeof(_small_data),
                  _small_data);
        std::fill(other._small_data, other._small_data + sizeof(_small_data),
                  std::byte(0));
    }
    else
    {
        _large_data = other._large_data;
        other._large_data = nullptr;
    }
}

void nobject::destruct()
{
    if (_type)
    {
        if (_type->size() <= sizeof(_small_data) && _type->ops()->destruct)
            _type->ops()->destruct(_small_data);
        else if (_large_data)
        {
            if (_type->ops()->destruct)
                _type->ops()->destruct(_large_data);
            delete[] _large_data;
        }
    }
}

std::byte* nobject::data()
{
    return _type->size() <= sizeof(_small_data) ? _small_data : _large_data;
}

const std::byte* nobject::data() const
{
    return _type->size() <= sizeof(_small_data) ? _small_data : _large_data;
}

nobject nobject::void_ = nobject();

} // namespace ntr
