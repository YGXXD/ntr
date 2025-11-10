//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "type/nnumeric.hpp"
#include "type/ntraits.hpp"

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
        value = *reinterpret_cast<const B8*>(numeric.data());
        break;
    case enumeric::echar:
        value = *reinterpret_cast<const C8*>(numeric.data());
        break;
    case enumeric::ewchar:
        value = *reinterpret_cast<const WC*>(numeric.data());
        break;
    case enumeric::echar16:
        value = *reinterpret_cast<const C16*>(numeric.data());
        break;
    case enumeric::echar32:
        value = *reinterpret_cast<const C32*>(numeric.data());
        break;
    case enumeric::eint8:
        value = *reinterpret_cast<const I8*>(numeric.data());
        break;
    case enumeric::eint16:
        value = *reinterpret_cast<const I16*>(numeric.data());
        break;
    case enumeric::eint32:
        value = *reinterpret_cast<const I32*>(numeric.data());
        break;
    case enumeric::eint64:
        value = *reinterpret_cast<const I64*>(numeric.data());
        break;
    case enumeric::euint8:
        value = *reinterpret_cast<const U8*>(numeric.data());
        break;
    case enumeric::euint16:
        value = *reinterpret_cast<const U16*>(numeric.data());
        break;
    case enumeric::euint32:
        value = *reinterpret_cast<const U32*>(numeric.data());
        break;
    case enumeric::euint64:
        value = *reinterpret_cast<const U64*>(numeric.data());
        break;
    case enumeric::efloat:
        value = *reinterpret_cast<const F32*>(numeric.data());
        break;
    case enumeric::edouble:
        value = *reinterpret_cast<const F64*>(numeric.data());
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
        *reinterpret_cast<B8*>(numeric.data()) = static_cast<B8>(value);
        break;
    case enumeric::echar:
        *reinterpret_cast<C8*>(numeric.data()) = static_cast<C8>(value);
        break;
    case enumeric::ewchar:
        *reinterpret_cast<WC*>(numeric.data()) = static_cast<WC>(value);
        break;
    case enumeric::echar16:
        *reinterpret_cast<C16*>(numeric.data()) = static_cast<C16>(value);
        break;
    case enumeric::echar32:
        *reinterpret_cast<C32*>(numeric.data()) = static_cast<C32>(value);
        break;
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

nnumeric::~nnumeric() = default;

} // namespace ntr
