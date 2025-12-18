//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "core/nobject.hpp"
#include "type/ntype.hpp"

namespace ntr
{

template <size_t N>
NTR_INLINE bool use_sso(const ntype* type)
{
    return type->size() <= N;
}

nobject nobject::new_(const ntype* type)
{
    nobject object {};
    object._type = type;
    if (object._type->size() > 0)
    {
        if (!type->ops()->default_construct)
            throw std::invalid_argument(
                "nobject::new_: type does not support default construction");
        if (use_sso<sizeof(nobject::_obtain)>(object._type))
        {
            object._handle = object._obtain;
            object._type->ops()->default_construct(object._handle);
        }
        else
        {
            void*& data = *reinterpret_cast<void**>(object._obtain);
            data = _ntr_align_alloc(object._type->size(), object._type->align());
            object._type->ops()->default_construct(data);
        }
    }
    return std::move(object);
}

nobject nobject::copy(const nwrapper& other)
{
    nobject object {};
    object._type = other.type();
    if (object._type->size() > 0)
    {
        if (!other.type()->ops()->copy_construct)
            throw std::invalid_argument(
                "nobject::copy: type does not support default construction");
        if (use_sso<sizeof(nobject::_obtain)>(object._type))
        {
            object._handle = object._obtain;
            object._type->ops()->copy_construct(object._handle, other.data());
        }
        else
        {
            void*& data = *reinterpret_cast<void**>(object._obtain);
            data = _ntr_align_alloc(object._type->size(), object._type->align());
            object._type->ops()->copy_construct(data, other.data());
        }
    }
    return std::move(object);
}

nobject nobject::move(const nwrapper& other)
{
    nobject object {};
    object._type = other.type();
    if (object._type->size() > 0)
    {
        if (!other.type()->ops()->move_construct)
            throw std::invalid_argument(
                "nobject::move: type does not support move construction");
        if (use_sso<sizeof(nobject::_obtain)>(object._type))
        {
            object._handle = object._obtain;
            object._type->ops()->move_construct(object._handle, other.data());
        }
        else
        {
            void*& data = *reinterpret_cast<void**>(object._obtain);
            data = _ntr_align_alloc(object._type->size(), object._type->align());
            object._type->ops()->move_construct(data, other.data());
        }
    }
    return std::move(object);
}

nobject nobject::ref(const nwrapper& reference)
{
    nobject object {};
    object._type = reference.type();
    object._handle = reference.data();
    return std::move(object);
}

nobject::nobject() : _type(nullptr), _handle(), _obtain {}
{
}

nobject::nobject(nobject&& other)
    : _type(other._type), _handle(other._handle),
      _obtain { other._obtain[0], other._obtain[1] }
{
    // sso
    if (other._handle == other._obtain)
    {
        _handle = _obtain;
        other._handle = nullptr;
    }
    // sso or heap
    if (!other._handle)
    {
        other._obtain[0] = 0;
        other._obtain[1] = 0;
    }
}

nobject& nobject::operator=(nobject&& other)
{
    if (this != &other)
    {
        this->~nobject();
        _type = other._type;
        _handle = other._handle;
        _obtain[0] = other._obtain[0];
        _obtain[1] = other._obtain[1];
        // sso
        if (other._handle == other._obtain)
        {
            _handle = _obtain;
            other._handle = nullptr;
        }
        // sso or heap
        if (!other._handle)
        {
            other._obtain[0] = 0;
            other._obtain[1] = 0;
        }
    }
    return *this;
}

nobject::~nobject()
{
    // sso
    if (_handle == _obtain)
        _type->ops()->destruct(_handle);
    // heap
    else if (void* data = *reinterpret_cast<void**>(_obtain))
    {
        type()->ops()->destruct(data);
        _ntr_align_free(data);
    }
}

nobject nobject::clone() const
{
    return copy(wrapper());
}

nobject nobject::steal() const
{
    return move(wrapper());
}

nobject nobject::hold() const
{
    return ref(wrapper());
}

void* nobject::data()
{
    return _handle ? _handle : *reinterpret_cast<void**>(_obtain);
}

const void* nobject::data() const
{
    return _handle ? _handle : *reinterpret_cast<void* const*>(_obtain);
}

} // namespace ntr
