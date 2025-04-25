#include "../../inc/core/nobject.hpp"
#include "../../inc/implement.hpp"

namespace ntr
{

enum class estorage_type : uint8_t
{
    esmall_object,
    eheap
};

enum class eobtain_status : uint8_t
{
    enone,
    eallocated,
    einitialized,
};

enum class eref_status : uint8_t
{
    einvalid,
    evalid,
};

NTR_INLINE nobject::eobject& object_kind(std::array<std::byte, 8>& status)
{
    return reinterpret_cast<nobject::eobject&>(status[0]);
}

NTR_INLINE const nobject::eobject& object_kind(const std::array<std::byte, 8>& status)
{
    return reinterpret_cast<const nobject::eobject&>(status[0]);
}

NTR_INLINE estorage_type& storage_type(std::array<std::byte, 8>& status)
{
    return reinterpret_cast<estorage_type&>(status[1]);
}

NTR_INLINE const estorage_type& storage_type(const std::array<std::byte, 8>& status)
{
    return reinterpret_cast<const estorage_type&>(status[1]);
}

NTR_INLINE eobtain_status& obtain_status(std::array<std::byte, 8>& status)
{
    return reinterpret_cast<eobtain_status&>(status[2]);
}

NTR_INLINE const eobtain_status& obtain_status(const std::array<std::byte, 8>& status)
{
    return reinterpret_cast<const eobtain_status&>(status[2]);
}

NTR_INLINE eref_status& ref_status(std::array<std::byte, 8>& status)
{
    return reinterpret_cast<eref_status&>(status[3]);
}

NTR_INLINE const eref_status& ref_status(const std::array<std::byte, 8>& status)
{
    return reinterpret_cast<const eref_status&>(status[3]);
}

nobject::nobject(const ntype* type, eobject kind) : _type(type), _status(), _bytes()
{
    object_kind(_status) = kind;
    if (type->size() > _bytes.size() && kind == eobject::eobtain)
        storage_type(_status) = estorage_type::eheap;
}

nobject::nobject(nobject&& other)
    : _type(other._type), _status(other._status), _bytes(other._bytes)
{
    switch (object_kind(other._status))
    {
    case eobject::eobtain:
        obtain_status(other._status) = eobtain_status::enone;
        break;
    case eobject::eref:
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
    switch (object_kind(_status))
    {
    case eobject::eobtain:
        if (obtain_status(_status) == eobtain_status::einitialized)
            type()->ops()->destruct(data());
        if (obtain_status(_status) >= eobtain_status::eallocated &&
            storage_type(_status) == estorage_type::eheap)
            std::free(data());
        break;
    case eobject::eref:
        break;
    }
}

nobject& nobject::alloc()
{
    if (object_kind(_status) == eobject::eref)
        throw std::runtime_error(
            "nobject::allocate : object is reference, cannot allocate");
    if (obtain_status(_status) >= eobtain_status::eallocated)
        throw std::runtime_error("nobject::allocate : object is already allocated");
    if (_type->size() > 0)
    {
        if (storage_type(_status) == estorage_type::eheap)
        {
            void* ptr = std::aligned_alloc(_type->align(), _type->size());
            if (!ptr)
                throw std::runtime_error("nobject::allocate : failed to allocate memory");
            *reinterpret_cast<void**>(_bytes.data()) = ptr;
        }
        obtain_status(_status) = eobtain_status::eallocated;
    }
    return *this;
}

nobject& nobject::init()
{
    if (object_kind(_status) == eobject::eref)
        throw std::runtime_error(
            "nobject::init : object is reference, cannot initialize");
    if (obtain_status(_status) == eobtain_status::einitialized)
        throw std::runtime_error("nobject::init : object is already initialized");
    if (obtain_status(_status) == eobtain_status::eallocated)
    {
        if (type()->ops()->default_construct)
        {
            type()->ops()->default_construct(data());
            obtain_status(_status) = eobtain_status::einitialized;
        }
        else
            throw std::runtime_error(
                "nobject::init : default_construct operation not found");
    }
    return *this;
}

nobject& nobject::init_copy(const nwrapper& wrapper)
{
    if (wrapper.type() != type())
        throw std::invalid_argument(
            "nobject::init_copy : wrapper's type is different from object's type");
    if (object_kind(_status) == eobject::eref)
        throw std::runtime_error(
            "nobject::init_copy : object is reference, cannot initialize");
    if (obtain_status(_status) == eobtain_status::einitialized)
        throw std::runtime_error("nobject::init_copy : object is already initialized");
    if (obtain_status(_status) == eobtain_status::eallocated)
    {
        if (type()->ops()->copy_construct)
        {
            type()->ops()->copy_construct(data(), wrapper.data());
            obtain_status(_status) = eobtain_status::einitialized;
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
    if (object_kind(_status) == eobject::eref)
        throw std::runtime_error(
            "nobject::init_move : object is reference, cannot initialize");
    if (obtain_status(_status) == eobtain_status::einitialized)
        throw std::runtime_error("nobject::init_move : object is already initialized");
    if (obtain_status(_status) == eobtain_status::eallocated)
    {
        if (type()->ops()->move_construct)
        {
            type()->ops()->move_construct(data(), wrapper.data());
            obtain_status(_status) = eobtain_status::einitialized;
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
    if (object_kind(_status) == eobject::eobtain)
        throw std::runtime_error("nobject::hold_ref : object is not reference");
    *reinterpret_cast<void**>(_bytes.data()) = wrapper.data();
    ref_status(_status) = eref_status::evalid;
    return *this;
}

nobject::eobject nobject::kind() const
{
    return object_kind(_status);
}

bool nobject::is_valid() const
{
    switch (object_kind(_status))
    {
    case eobject::eobtain:
        return obtain_status(_status) == eobtain_status::einitialized;
    case eobject::eref:
        return ref_status(_status) == eref_status::evalid;
    }
}

void* nobject::data()
{
    if (object_kind(_status) == eobject::eref ||
        storage_type(_status) == estorage_type::eheap)
        return *reinterpret_cast<void**>(_bytes.data());
    return _bytes.data();
}

const void* nobject::data() const
{
    if (object_kind(_status) == eobject::eref ||
        storage_type(_status) == estorage_type::eheap)
        return *reinterpret_cast<const void* const*>(_bytes.data());
    return _bytes.data();
}

} // namespace ntr
