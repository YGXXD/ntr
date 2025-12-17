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

enum eobtain_status : uint8_t
{
    eobtain_status_none,
    eobtain_status_allocated,
    eobtain_status_initialized,
};

enum ereference_status : uint8_t
{
    ereference_status_none,
    ereference_status_holding,
};

nobject::nobject(const ntype* type, eobject kind)
    : _type(type), _kind(kind),
      _is_heap(type->size() > sizeof(_bytes) && kind == eobject::eobtain),
      _obtain_status(eobtain_status_none), _ref_status(ereference_status_none), _bytes()
{
}

nobject::nobject(nobject&& other)
    : _type(other._type), _status(other._status), _bytes(other._bytes)
{
    switch (other._kind)
    {
    case eobject::eobtain:
        other._obtain_status = eobtain_status_none;
        break;
    case eobject::ereference:
        break;
    }
}

nobject& nobject::operator=(nobject&& other)
{
    if (this != &other)
    {
        nobject temp(std::move(other));
        std::swap(_type, temp._type);
        std::swap(_status, temp._status);
        std::swap(_bytes, temp._bytes);
    }
    return *this;
}

nobject::~nobject()
{
    switch (_kind)
    {
    case eobject::eobtain:
        if (_obtain_status == eobtain_status_initialized)
            type()->ops()->destruct(data());
        if (_obtain_status >= eobtain_status_allocated && _is_heap)
            _ntr_align_free(data());
        break;
    case eobject::ereference:
        break;
    }
}

nobject& nobject::alloc()
{
    if (_kind == eobject::ereference)
        throw std::runtime_error(
            "nobject::allocate : object is reference, cannot allocate");
    if (_obtain_status >= eobtain_status_allocated)
        throw std::runtime_error("nobject::allocate : object is already allocated");
    if (_type->size() > 0)
    {
        if (_is_heap)
        {
            void* ptr = _ntr_align_alloc(_type->size(), _type->align());
            if (!ptr)
                throw std::runtime_error("nobject::allocate : failed to allocate memory");
            *reinterpret_cast<void**>(_bytes.data()) = ptr;
        }
        _obtain_status = eobtain_status_allocated;
    }
    return *this;
}

nobject& nobject::init_default()
{
    if (_kind == eobject::ereference)
        throw std::runtime_error(
            "nobject::init_default : object is reference, cannot initialize");
    if (_obtain_status == eobtain_status_initialized)
        throw std::runtime_error("nobject::init : object is already initialized");
    if (_obtain_status == eobtain_status_allocated)
    {
        if (type()->ops()->default_construct)
        {
            type()->ops()->default_construct(data());
            _obtain_status = eobtain_status_initialized;
        }
        else
            throw std::runtime_error(
                "nobject::init_default : default_construct operation not found");
    }
    return *this;
}

nobject& nobject::init_copy(const nwrapper& wrapper)
{
    if (wrapper.type() != type())
        throw std::invalid_argument(
            "nobject::init_copy : wrapper's type is different from object's type");
    if (_kind == eobject::ereference)
        throw std::runtime_error(
            "nobject::init_copy : object is reference, cannot initialize");
    if (_obtain_status == eobtain_status_initialized)
        throw std::runtime_error("nobject::init_copy : object is already initialized");
    if (_obtain_status == eobtain_status_allocated)
    {
        if (type()->ops()->copy_construct)
        {
            type()->ops()->copy_construct(data(), wrapper.data());
            _obtain_status = eobtain_status_initialized;
        }
        else
            throw std::runtime_error(
                "nobject::init_copy : copy_construct operation not found");
    }
    return *this;
}

nobject& nobject::init_move(const nwrapper& wrapper)
{
    if (wrapper.type() != type())
        throw std::invalid_argument(
            "nobject::init_move : wrapper's type is different from object's type");
    if (_kind == eobject::ereference)
        throw std::runtime_error(
            "nobject::init_move : object is reference, cannot initialize");
    if (_obtain_status == eobtain_status_initialized)
        throw std::runtime_error("nobject::init_move : object is already initialized");
    if (_obtain_status == eobtain_status_allocated)
    {
        if (type()->ops()->move_construct)
        {
            type()->ops()->move_construct(data(), wrapper.data());
            _obtain_status = eobtain_status_initialized;
        }
        else
            throw std::runtime_error(
                "nobject::init_move : move_construct operation not found");
    }
    return *this;
}

nobject& nobject::hold_ref(const nwrapper& wrapper)
{
    if (wrapper.type() != type())
        throw std::invalid_argument(
            "nobject::hold_ref : wrapper's type is different from object's type");
    if (_kind == eobject::eobtain)
        throw std::runtime_error("nobject::hold_ref : object is not reference");
    *reinterpret_cast<void**>(_bytes.data()) = wrapper.data();
    _ref_status = ereference_status_holding;
    return *this;
}

bool nobject::is_valid() const
{
    switch (_kind)
    {
    case eobject::eobtain:
        return _obtain_status == eobtain_status_initialized;
    case eobject::ereference:
        return _ref_status == ereference_status_holding;
    }
    return false;
}

void* nobject::data()
{
    if (_kind == eobject::ereference || _is_heap)
        return *reinterpret_cast<void**>(_bytes.data());
    return _bytes.data();
}

const void* nobject::data() const
{
    if (_kind == eobject::ereference || _is_heap)
        return *reinterpret_cast<const void* const*>(_bytes.data());
    return _bytes.data();
}

nobject nobject::clone() const
{
    return std::move(nobject(_type, eobject::eobtain).alloc().init_copy(wrapper()));
}

nobject nobject::steal() const
{
    return std::move(nobject(_type, eobject::eobtain).alloc().init_move(wrapper()));
}

nobject nobject::handle() const
{
    return std::move(nobject(_type, eobject::ereference).hold_ref(wrapper()));
}

} // namespace ntr
