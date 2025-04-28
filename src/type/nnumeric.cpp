#include "type/nnumeric.hpp"
#include "implement.hpp"

namespace ntr
{

using B8 = make_numeric_type_t<nnumeric::enumeric::ebool>;
using C8 = make_numeric_type_t<nnumeric::enumeric::echar>;
using WC = make_numeric_type_t<nnumeric::enumeric::ewchar>;
using C16 = make_numeric_type_t<nnumeric::enumeric::echar16>;
using C32 = make_numeric_type_t<nnumeric::enumeric::echar32>;
using I8 = make_numeric_type_t<nnumeric::enumeric::eint8>;
using I16 = make_numeric_type_t<nnumeric::enumeric::eint16>;
using I32 = make_numeric_type_t<nnumeric::enumeric::eint32>;
using I64 = make_numeric_type_t<nnumeric::enumeric::eint64>;
using U8 = make_numeric_type_t<nnumeric::enumeric::euint8>;
using U16 = make_numeric_type_t<nnumeric::enumeric::euint16>;
using U32 = make_numeric_type_t<nnumeric::enumeric::euint32>;
using U64 = make_numeric_type_t<nnumeric::enumeric::euint64>;
using F32 = make_numeric_type_t<nnumeric::enumeric::efloat>;
using F64 = make_numeric_type_t<nnumeric::enumeric::edouble>;

double nnumeric::get_value(const nobject& numeric)
{
    if (!numeric.type()->is_numeric())
        throw std::invalid_argument(
            "nnumeric::get_value : numeric's type is not numeric type");
    double value = 0;
    switch (numeric.type()->as_numeric()->numeric_kind())
    {
    case enumeric::ebool:
        value = numeric.as<B8>();
        break;
    case enumeric::echar:
        value = numeric.as<C8>();
        break;
    case enumeric::ewchar:
        value = numeric.as<WC>();
        break;
    case enumeric::echar16:
        value = numeric.as<C16>();
        break;
    case enumeric::echar32:
        value = numeric.as<C32>();
        break;
    case enumeric::eint8:
        value = numeric.as<I8>();
        break;
    case enumeric::eint16:
        value = numeric.as<I16>();
        break;
    case enumeric::eint32:
        value = numeric.as<I32>();
        break;
    case enumeric::eint64:
        value = numeric.as<I64>();
        break;
    case enumeric::euint8:
        value = numeric.as<U8>();
        break;
    case enumeric::euint16:
        value = numeric.as<U16>();
        break;
    case enumeric::euint32:
        value = numeric.as<U32>();
        break;
    case enumeric::euint64:
        value = numeric.as<U64>();
        break;
    case enumeric::efloat:
        value = numeric.as<F32>();
        break;
    case enumeric::edouble:
        value = numeric.as<F64>();
        break;
    }
    return value;
}

void nnumeric::set_value(nobject& numeric, double value)
{
    if (!numeric.type()->is_numeric())
        throw std::invalid_argument(
            "nnumeric::set_value : numeric's type is not numeric type");
    switch (numeric.type()->as_numeric()->numeric_kind())
    {
    case enumeric::ebool:
        numeric.as<B8>() = static_cast<B8>(value);
        break;
    case enumeric::echar:
        numeric.as<C8>() = static_cast<C8>(value);
        break;
    case enumeric::ewchar:
        numeric.as<WC>() = static_cast<WC>(value);
        break;
    case enumeric::echar16:
        numeric.as<C16>() = static_cast<C16>(value);
        break;
    case enumeric::echar32:
        numeric.as<C32>() = static_cast<C32>(value);
        break;
    case enumeric::eint8:
        numeric.as<I8>() = static_cast<I8>(value);
        break;
    case enumeric::eint16:
        numeric.as<I16>() = static_cast<I16>(value);
        break;
    case enumeric::eint32:
        numeric.as<I32>() = static_cast<I32>(value);
        break;
    case enumeric::eint64:
        numeric.as<I64>() = static_cast<I64>(value);
        break;
    case enumeric::euint8:
        numeric.as<U8>() = static_cast<U8>(value);
        break;
    case enumeric::euint16:
        numeric.as<U16>() = static_cast<U16>(value);
        break;
    case enumeric::euint32:
        numeric.as<U32>() = static_cast<U32>(value);
        break;
    case enumeric::euint64:
        numeric.as<U64>() = static_cast<U64>(value);
        break;
    case enumeric::efloat:
        numeric.as<F32>() = static_cast<F32>(value);
        break;
    case enumeric::edouble:
        numeric.as<F64>() = value;
        break;
    }
}

nnumeric::nnumeric(enumeric numeric_kind, uint32_t size, uint32_t align, operations* ops,
                   std::string_view name)
    : ntype(etype::enumeric, size, align, ops, name), _numeric_kind(numeric_kind)
{
    switch (numeric_kind)
    {
    case enumeric::ebool:
        _is_signed = std::is_signed_v<B8>;
        _is_integral = std::is_integral_v<B8>;
        _is_floating_point = std::is_floating_point_v<B8>;
        break;
    case enumeric::echar:
        _is_signed = std::is_signed_v<C8>;
        _is_integral = std::is_integral_v<C8>;
        _is_floating_point = std::is_floating_point_v<C8>;
        break;
    case enumeric::ewchar:
        _is_signed = std::is_signed_v<WC>;
        _is_integral = std::is_integral_v<WC>;
        _is_floating_point = std::is_floating_point_v<WC>;
        break;
    case enumeric::echar16:
        _is_signed = std::is_signed_v<C16>;
        _is_integral = std::is_integral_v<C16>;
        _is_floating_point = std::is_floating_point_v<C16>;
        break;
    case enumeric::echar32:
        _is_signed = std::is_signed_v<C32>;
        _is_integral = std::is_integral_v<C32>;
        _is_floating_point = std::is_floating_point_v<C32>;
        break;
    case enumeric::eint8:
        _is_signed = std::is_signed_v<I8>;
        _is_integral = std::is_integral_v<I8>;
        _is_floating_point = std::is_floating_point_v<I8>;
        break;
    case enumeric::eint16:
        _is_signed = std::is_signed_v<I16>;
        _is_integral = std::is_integral_v<I16>;
        _is_floating_point = std::is_floating_point_v<I16>;
        break;
    case enumeric::eint32:
        _is_signed = std::is_signed_v<I32>;
        _is_integral = std::is_integral_v<I32>;
        _is_floating_point = std::is_floating_point_v<I32>;
        break;
    case enumeric::eint64:
        _is_signed = std::is_signed_v<I64>;
        _is_integral = std::is_integral_v<I64>;
        _is_floating_point = std::is_floating_point_v<I64>;
        break;
    case enumeric::euint8:
        _is_signed = std::is_signed_v<U8>;
        _is_integral = std::is_integral_v<U8>;
        _is_floating_point = std::is_floating_point_v<U8>;
        break;
    case enumeric::euint16:
        _is_signed = std::is_signed_v<U16>;
        _is_integral = std::is_integral_v<U16>;
        _is_floating_point = std::is_floating_point_v<U16>;
        break;
    case enumeric::euint32:
        _is_signed = std::is_signed_v<U32>;
        _is_integral = std::is_integral_v<U32>;
        _is_floating_point = std::is_floating_point_v<U32>;
        break;
    case enumeric::euint64:
        _is_signed = std::is_signed_v<U64>;
        _is_integral = std::is_integral_v<U64>;
        _is_floating_point = std::is_floating_point_v<U64>;
        break;
    case enumeric::efloat:
        _is_signed = std::is_signed_v<F32>;
        _is_integral = std::is_integral_v<F32>;
        _is_floating_point = std::is_floating_point_v<F32>;
        break;
    case enumeric::edouble:
        _is_signed = std::is_signed_v<F64>;
        _is_integral = std::is_integral_v<F64>;
        _is_floating_point = std::is_floating_point_v<F64>;
        break;
    }
}

} // namespace ntr
