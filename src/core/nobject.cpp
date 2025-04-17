#include "../../inc/core/nobject.hpp"
#include "../../inc/type/ntype.hpp"

namespace ntr
{

nobject::nobject(const nobject& other)
    : _type(other._type), _data_ops(other._data_ops), _small_data()
{
    if (_data_ops && _data_ops->copy)
        _data_ops->copy(_large_data, other._large_data);
    else
        throw std::runtime_error(std::string(_type->name()) + " has no copy operation");
}

nobject::nobject(nobject&& other)
    : _type(other._type), _data_ops(other._data_ops), _small_data()
{
    if (_data_ops && _data_ops->move)
        _data_ops->move(_large_data, other._large_data);
    else
        throw std::runtime_error(std::string(_type->name()) + " has no move operation");
}

nobject& nobject::operator=(const nobject& other)
{
    if (this != &other)
    {
        _type = other._type;
        _data_ops = other._data_ops;
        if (_data_ops && _data_ops->copy)
            _data_ops->copy(_large_data, other._large_data);
        else
            throw std::runtime_error(std::string(_type->name()) +
                                     " has no copy operation");
    }
    return *this;
}

nobject& nobject::operator=(nobject&& other)
{
    if (this != &other)
    {
        _type = other._type;
        _data_ops = other._data_ops;
        if (_data_ops && _data_ops->move)
            _data_ops->move(_large_data, other._large_data);
        else
            throw std::runtime_error(std::string(_type->name()) +
                                     " has no move operation");
    }
    return *this;
}

nobject::~nobject()
{
    if (_data_ops && _data_ops->release)
        _data_ops->release(_large_data);
}

} // namespace ntr
