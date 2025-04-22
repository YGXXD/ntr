#include "../../inc/type/nnumeric.hpp"
#include "../../inc/type/ntraits.hpp"
#include "../../inc/core/nobject.hpp"

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

double nnumeric::get_value(nobject& numeric)
{
    if (!numeric.type()->is_numeric())
        throw std::invalid_argument(
            "nnumeric::get_value : numeric's type is not numeric type");
    double value = 0;
    switch (numeric.type()->as_numeric()->numeric_kind())
    {
    case enumeric::ebool:
    {
        value = static_cast<double>(*reinterpret_cast<B8*>(numeric.data()));
        break;
    }
    case enumeric::echar:
    {
        value = static_cast<double>(*reinterpret_cast<C8*>(numeric.data()));
        break;
    }
    case enumeric::ewchar:
    {
        value = static_cast<double>(*reinterpret_cast<WC*>(numeric.data()));
        break;
    }
    case enumeric::echar16:
    {
        value = static_cast<double>(*reinterpret_cast<C16*>(numeric.data()));
        break;
    }
    case enumeric::echar32:
    {
        value = static_cast<double>(*reinterpret_cast<C32*>(numeric.data()));
        break;
    }
    case enumeric::eint8:
    {
        value = static_cast<double>(*reinterpret_cast<I8*>(numeric.data()));
        break;
    }
    case enumeric::eint16:
    {
        value = static_cast<double>(*reinterpret_cast<I16*>(numeric.data()));
        break;
    }
    case enumeric::eint32:
    {
        value = static_cast<double>(*reinterpret_cast<I32*>(numeric.data()));
        break;
    }
    case enumeric::eint64:
    {
        value = static_cast<double>(*reinterpret_cast<I64*>(numeric.data()));
        break;
    }
    case enumeric::euint8:
    {
        value = static_cast<double>(*reinterpret_cast<U8*>(numeric.data()));
        break;
    }
    case enumeric::euint16:
    {
        value = static_cast<double>(*reinterpret_cast<U16*>(numeric.data()));
        break;
    }
    case enumeric::euint32:
    {
        value = static_cast<double>(*reinterpret_cast<U32*>(numeric.data()));
        break;
    }
    case enumeric::euint64:
    {
        value = static_cast<double>(*reinterpret_cast<U64*>(numeric.data()));
        break;
    }
    case enumeric::efloat:
    {
        value = static_cast<double>(*reinterpret_cast<F32*>(numeric.data()));
        break;
    }
    case enumeric::edouble:
    {
        value = static_cast<double>(*reinterpret_cast<F64*>(numeric.data()));
        break;
    }
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
    {
        *reinterpret_cast<B8*>(numeric.data()) = static_cast<B8>(value);
        break;
    }
    case enumeric::echar:
    {
        *reinterpret_cast<C8*>(numeric.data()) = static_cast<C8>(value);
        break;
    }
    case enumeric::ewchar:
    {
        *reinterpret_cast<WC*>(numeric.data()) = static_cast<WC>(value);
        break;
    }
    case enumeric::echar16:
    {
        *reinterpret_cast<C16*>(numeric.data()) = static_cast<C16>(value);
        break;
    }
    case enumeric::echar32:
    {
        *reinterpret_cast<C32*>(numeric.data()) = static_cast<C32>(value);
        break;
    }
    case enumeric::eint8:
    {
        *reinterpret_cast<I8*>(numeric.data()) = static_cast<I8>(value);
        break;
    }
    case enumeric::eint16:
    {
        *reinterpret_cast<I16*>(numeric.data()) = static_cast<I16>(value);
        break;
    }
    case enumeric::eint32:
    {
        *reinterpret_cast<I32*>(numeric.data()) = static_cast<I32>(value);
        break;
    }
    case enumeric::eint64:
    {
        *reinterpret_cast<I64*>(numeric.data()) = static_cast<I64>(value);
        break;
    }
    case enumeric::euint8:
    {
        *reinterpret_cast<U8*>(numeric.data()) = static_cast<U8>(value);
        break;
    }
    case enumeric::euint16:
    {
        *reinterpret_cast<U16*>(numeric.data()) = static_cast<U16>(value);
        break;
    }
    case enumeric::euint32:
    {
        *reinterpret_cast<U32*>(numeric.data()) = static_cast<U32>(value);
        break;
    }
    case enumeric::euint64:
    {
        *reinterpret_cast<U64*>(numeric.data()) = static_cast<U64>(value);
        break;
    }
    case enumeric::efloat:
    {
        *reinterpret_cast<F32*>(numeric.data()) = static_cast<F32>(value);
        break;
    }
    case enumeric::edouble:
    {
        *reinterpret_cast<F64*>(numeric.data()) = value;
        break;
    }
    }
}

nnumeric::nnumeric(enumeric numeric_kind, uint32_t size, operations* ops,
                   std::string_view name)
    : ntype(etype::enumeric, size, ops, name), _numeric_kind(numeric_kind)
{
    switch (numeric_kind)
    {
    case enumeric::ebool:
    {
        _is_signed = std::is_signed_v<bool>;
        _is_integral = std::is_integral_v<bool>;
        _is_floating_point = std::is_floating_point_v<bool>;
        break;
    }
    case enumeric::echar:
    {
        _is_signed = std::is_signed_v<char>;
        _is_integral = std::is_integral_v<char>;
        _is_floating_point = std::is_floating_point_v<char>;
        break;
    }
    case enumeric::ewchar:
    {
        _is_signed = std::is_signed_v<wchar_t>;
        _is_integral = std::is_integral_v<wchar_t>;
        _is_floating_point = std::is_floating_point_v<wchar_t>;
        break;
    }
    case enumeric::echar16:
    {
        _is_signed = std::is_signed_v<char16_t>;
        _is_integral = std::is_integral_v<char16_t>;
        _is_floating_point = std::is_floating_point_v<char16_t>;
        break;
    }
    case enumeric::echar32:
    {
        _is_signed = std::is_signed_v<char32_t>;
        _is_integral = std::is_integral_v<char32_t>;
        _is_floating_point = std::is_floating_point_v<char32_t>;
        break;
    }
    case enumeric::eint8:
    {
        _is_signed = std::is_signed_v<int8_t>;
        _is_integral = std::is_integral_v<int8_t>;
        _is_floating_point = std::is_floating_point_v<int8_t>;
        break;
    }
    case enumeric::eint16:
    {
        _is_signed = std::is_signed_v<int16_t>;
        _is_integral = std::is_integral_v<int16_t>;
        _is_floating_point = std::is_floating_point_v<int16_t>;
        break;
    }
    case enumeric::eint32:
    {
        _is_signed = std::is_signed_v<int32_t>;
        _is_integral = std::is_integral_v<int32_t>;
        _is_floating_point = std::is_floating_point_v<int32_t>;
        break;
    }
    case enumeric::eint64:
    {
        _is_signed = std::is_signed_v<int64_t>;
        _is_integral = std::is_integral_v<int64_t>;
        _is_floating_point = std::is_floating_point_v<int64_t>;
        break;
    }
    case enumeric::euint8:
    {
        _is_signed = std::is_signed_v<uint8_t>;
        _is_integral = std::is_integral_v<uint8_t>;
        _is_floating_point = std::is_floating_point_v<uint8_t>;
        break;
    }
    case enumeric::euint16:
    {
        _is_signed = std::is_signed_v<uint16_t>;
        _is_integral = std::is_integral_v<uint16_t>;
        _is_floating_point = std::is_floating_point_v<uint16_t>;
        break;
    }
    case enumeric::euint32:
    {
        _is_signed = std::is_signed_v<uint32_t>;
        _is_integral = std::is_integral_v<uint32_t>;
        _is_floating_point = std::is_floating_point_v<uint32_t>;
        break;
    }
    case enumeric::euint64:
    {
        _is_signed = std::is_signed_v<uint64_t>;
        _is_integral = std::is_integral_v<uint64_t>;
        _is_floating_point = std::is_floating_point_v<uint64_t>;
        break;
    }
    case enumeric::efloat:
    {
        _is_signed = std::is_signed_v<float>;
        _is_integral = std::is_integral_v<float>;
        _is_floating_point = std::is_floating_point_v<float>;
        break;
    }
    case enumeric::edouble:
    {
        _is_signed = std::is_signed_v<double>;
        _is_integral = std::is_integral_v<double>;
        _is_floating_point = std::is_floating_point_v<double>;
        break;
    }
    }
}

} // namespace ntr
