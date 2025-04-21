#include "../../inc/type/nnumeric.hpp"
#include "../../inc/type/ntraits.hpp"
#include "../../inc/core/nobject.hpp"

namespace ntr
{

using I8 = decltype(make_numeric_type<nnumeric::enumeric::eint8>());
using I16 = decltype(make_numeric_type<nnumeric::enumeric::eint16>());
using I32 = decltype(make_numeric_type<nnumeric::enumeric::eint32>());
using I64 = decltype(make_numeric_type<nnumeric::enumeric::eint64>());
using U8 = decltype(make_numeric_type<nnumeric::enumeric::euint8>());
using U16 = decltype(make_numeric_type<nnumeric::enumeric::euint16>());
using U32 = decltype(make_numeric_type<nnumeric::enumeric::euint32>());
using U64 = decltype(make_numeric_type<nnumeric::enumeric::euint64>());
using F32 = decltype(make_numeric_type<nnumeric::enumeric::efloat>());
using F64 = decltype(make_numeric_type<nnumeric::enumeric::edouble>());

double nnumeric::get_value(nobject& numeric)
{
    if (!numeric.type()->is_numeric())
        throw std::runtime_error("nnumeric::get_value : type mismatch");
    double value = 0;
    switch (numeric.type()->as_numeric()->numeric_kind())
    {
    case enumeric::eint8:
        value = static_cast<double>(*reinterpret_cast<I8*>(numeric.data()));
        break;
    case enumeric::eint16:
        value = static_cast<double>(*reinterpret_cast<I16*>(numeric.data()));
        break;
    case enumeric::eint32:
        value = static_cast<double>(*reinterpret_cast<I32*>(numeric.data()));
        break;
    case enumeric::eint64:
        value = static_cast<double>(*reinterpret_cast<I64*>(numeric.data()));
        break;
    case enumeric::euint8:
        value = static_cast<double>(*reinterpret_cast<U8*>(numeric.data()));
        break;
    case enumeric::euint16:
        value = static_cast<double>(*reinterpret_cast<U16*>(numeric.data()));
        break;
    case enumeric::euint32:
        value = static_cast<double>(*reinterpret_cast<U32*>(numeric.data()));
        break;
    case enumeric::euint64:
        value = static_cast<double>(*reinterpret_cast<U64*>(numeric.data()));
        break;
    case enumeric::efloat:
        value = static_cast<double>(*reinterpret_cast<F32*>(numeric.data()));
        break;
    case enumeric::edouble:
        value = static_cast<double>(*reinterpret_cast<F64*>(numeric.data()));
        break;
    }
    return value;
}

void nnumeric::set_value(nobject& numeric, double value)
{
    if (!numeric.type()->is_numeric())
        throw std::runtime_error("nnumeric::set_value : type mismatch");
    switch (numeric.type()->as_numeric()->numeric_kind())
    {
    case enumeric::eint8:
        *reinterpret_cast<I8*>(numeric.data()) = static_cast<I8>(value);
        break;
    case enumeric::eint16:
        *reinterpret_cast<I16*>(numeric.data()) = static_cast<I16>(value);
        break;
    case enumeric::eint32:
        *reinterpret_cast<I32*>(numeric.data()) = static_cast<I32>(value);
        break;
    case enumeric::eint64:
        *reinterpret_cast<I64*>(numeric.data()) = static_cast<I64>(value);
        break;
    case enumeric::euint8:
        *reinterpret_cast<U8*>(numeric.data()) = static_cast<U8>(value);
        break;
    case enumeric::euint16:
        *reinterpret_cast<U16*>(numeric.data()) = static_cast<U16>(value);
        break;
    case enumeric::euint32:
        *reinterpret_cast<U32*>(numeric.data()) = static_cast<U32>(value);
        break;
    case enumeric::euint64:
        *reinterpret_cast<U64*>(numeric.data()) = static_cast<U64>(value);
        break;
    case enumeric::efloat:
        *reinterpret_cast<F32*>(numeric.data()) = static_cast<F32>(value);
        break;
    case enumeric::edouble:
        *reinterpret_cast<F64*>(numeric.data()) = value;
        break;
    }
}

nnumeric::nnumeric(enumeric numeric_kind, uint32_t size, operations* ops,
                   std::string_view name)
    : ntype(etype::enumeric, size, ops, name), _numeric_kind(numeric_kind)
{
    switch (numeric_kind)
    {
    case enumeric::eint8:
    case enumeric::eint16:
    case enumeric::eint32:
    case enumeric::eint64:
        _is_signed = true;
        _is_integral = true;
        break;
    case enumeric::euint8:
    case enumeric::euint16:
    case enumeric::euint32:
    case enumeric::euint64:
        _is_signed = false;
        _is_integral = true;
        break;
    case enumeric::efloat:
    case enumeric::edouble:
        _is_signed = false;
        _is_integral = false;
        break;
    }
}

} // namespace ntr
