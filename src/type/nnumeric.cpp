//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "type/nnumeric.hpp"

#include <type_traits>
#include <stdexcept>

namespace ntr
{

template <nnumeric::enumeric numeric_kind>
using get_numeric_type_t =
    std::tuple_element_t<static_cast<size_t>(numeric_kind), nnumeric::numeric_types>;

using b8 = get_numeric_type_t<nnumeric::enumeric::ebool>;
using c8 = get_numeric_type_t<nnumeric::enumeric::echar>;
using wc = get_numeric_type_t<nnumeric::enumeric::ewchar>;
using c16 = get_numeric_type_t<nnumeric::enumeric::echar16>;
using c32 = get_numeric_type_t<nnumeric::enumeric::echar32>;
using i8 = get_numeric_type_t<nnumeric::enumeric::eint8>;
using i16 = get_numeric_type_t<nnumeric::enumeric::eint16>;
using i32 = get_numeric_type_t<nnumeric::enumeric::eint32>;
using i64 = get_numeric_type_t<nnumeric::enumeric::eint64>;
using u8 = get_numeric_type_t<nnumeric::enumeric::euint8>;
using u16 = get_numeric_type_t<nnumeric::enumeric::euint16>;
using u32 = get_numeric_type_t<nnumeric::enumeric::euint32>;
using u64 = get_numeric_type_t<nnumeric::enumeric::euint64>;
using f32 = get_numeric_type_t<nnumeric::enumeric::efloat>;
using f64 = get_numeric_type_t<nnumeric::enumeric::edouble>;

double nnumeric::get_value(const nwrapper& numeric)
{
    if (!numeric.type()->is_numeric())
        throw std::invalid_argument(
            "nnumeric::get_value : numeric's type is not numeric type");
    double value = 0;
    switch (numeric.type()->as_numeric()->numeric_kind())
    {
    case enumeric::ebool:
        value = *reinterpret_cast<const b8*>(numeric.data());
        break;
    case enumeric::echar:
        value = *reinterpret_cast<const c8*>(numeric.data());
        break;
    case enumeric::ewchar:
        value = *reinterpret_cast<const wc*>(numeric.data());
        break;
    case enumeric::echar16:
        value = *reinterpret_cast<const c16*>(numeric.data());
        break;
    case enumeric::echar32:
        value = *reinterpret_cast<const c32*>(numeric.data());
        break;
    case enumeric::eint8:
        value = *reinterpret_cast<const i8*>(numeric.data());
        break;
    case enumeric::eint16:
        value = *reinterpret_cast<const i16*>(numeric.data());
        break;
    case enumeric::eint32:
        value = *reinterpret_cast<const i32*>(numeric.data());
        break;
    case enumeric::eint64:
        value = *reinterpret_cast<const i64*>(numeric.data());
        break;
    case enumeric::euint8:
        value = *reinterpret_cast<const u8*>(numeric.data());
        break;
    case enumeric::euint16:
        value = *reinterpret_cast<const u16*>(numeric.data());
        break;
    case enumeric::euint32:
        value = *reinterpret_cast<const u32*>(numeric.data());
        break;
    case enumeric::euint64:
        value = *reinterpret_cast<const u64*>(numeric.data());
        break;
    case enumeric::efloat:
        value = *reinterpret_cast<const f32*>(numeric.data());
        break;
    case enumeric::edouble:
        value = *reinterpret_cast<const f64*>(numeric.data());
        break;
    }
    return value;
}

void nnumeric::set_value(const nwrapper& numeric, double value)
{
    if (!numeric.type()->is_numeric())
        throw std::invalid_argument(
            "nnumeric::set_value : numeric's type is not numeric type");
    switch (numeric.type()->as_numeric()->numeric_kind())
    {
    case enumeric::ebool:
        *reinterpret_cast<b8*>(numeric.data()) = static_cast<b8>(value);
        break;
    case enumeric::echar:
        *reinterpret_cast<c8*>(numeric.data()) = static_cast<c8>(value);
        break;
    case enumeric::ewchar:
        *reinterpret_cast<wc*>(numeric.data()) = static_cast<wc>(value);
        break;
    case enumeric::echar16:
        *reinterpret_cast<c16*>(numeric.data()) = static_cast<c16>(value);
        break;
    case enumeric::echar32:
        *reinterpret_cast<c32*>(numeric.data()) = static_cast<c32>(value);
        break;
    case enumeric::eint8:
        *reinterpret_cast<i8*>(numeric.data()) = static_cast<i8>(value);
        break;
    case enumeric::eint16:
        *reinterpret_cast<i16*>(numeric.data()) = static_cast<i16>(value);
        break;
    case enumeric::eint32:
        *reinterpret_cast<i32*>(numeric.data()) = static_cast<i32>(value);
        break;
    case enumeric::eint64:
        *reinterpret_cast<i64*>(numeric.data()) = static_cast<i64>(value);
        break;
    case enumeric::euint8:
        *reinterpret_cast<u8*>(numeric.data()) = static_cast<u8>(value);
        break;
    case enumeric::euint16:
        *reinterpret_cast<u16*>(numeric.data()) = static_cast<u16>(value);
        break;
    case enumeric::euint32:
        *reinterpret_cast<u32*>(numeric.data()) = static_cast<u32>(value);
        break;
    case enumeric::euint64:
        *reinterpret_cast<u64*>(numeric.data()) = static_cast<u64>(value);
        break;
    case enumeric::efloat:
        *reinterpret_cast<f32*>(numeric.data()) = static_cast<f32>(value);
        break;
    case enumeric::edouble:
        *reinterpret_cast<f64*>(numeric.data()) = value;
        break;
    }
}

nnumeric::nnumeric(enumeric numeric_kind, uint16_t size, uint16_t align, operations* ops)
    : ntype(etype::enumeric, size, align, ops), _numeric_kind(numeric_kind)
{
    switch (numeric_kind)
    {
    case enumeric::ebool:
        _is_signed = std::is_signed_v<b8>;
        _is_integral = std::is_integral_v<b8>;
        _is_floating_point = std::is_floating_point_v<b8>;
        break;
    case enumeric::echar:
        _is_signed = std::is_signed_v<c8>;
        _is_integral = std::is_integral_v<c8>;
        _is_floating_point = std::is_floating_point_v<c8>;
        break;
    case enumeric::ewchar:
        _is_signed = std::is_signed_v<wc>;
        _is_integral = std::is_integral_v<wc>;
        _is_floating_point = std::is_floating_point_v<wc>;
        break;
    case enumeric::echar16:
        _is_signed = std::is_signed_v<c16>;
        _is_integral = std::is_integral_v<c16>;
        _is_floating_point = std::is_floating_point_v<c16>;
        break;
    case enumeric::echar32:
        _is_signed = std::is_signed_v<c32>;
        _is_integral = std::is_integral_v<c32>;
        _is_floating_point = std::is_floating_point_v<c32>;
        break;
    case enumeric::eint8:
        _is_signed = std::is_signed_v<i8>;
        _is_integral = std::is_integral_v<i8>;
        _is_floating_point = std::is_floating_point_v<i8>;
        break;
    case enumeric::eint16:
        _is_signed = std::is_signed_v<i16>;
        _is_integral = std::is_integral_v<i16>;
        _is_floating_point = std::is_floating_point_v<i16>;
        break;
    case enumeric::eint32:
        _is_signed = std::is_signed_v<i32>;
        _is_integral = std::is_integral_v<i32>;
        _is_floating_point = std::is_floating_point_v<i32>;
        break;
    case enumeric::eint64:
        _is_signed = std::is_signed_v<i64>;
        _is_integral = std::is_integral_v<i64>;
        _is_floating_point = std::is_floating_point_v<i64>;
        break;
    case enumeric::euint8:
        _is_signed = std::is_signed_v<u8>;
        _is_integral = std::is_integral_v<u8>;
        _is_floating_point = std::is_floating_point_v<u8>;
        break;
    case enumeric::euint16:
        _is_signed = std::is_signed_v<u16>;
        _is_integral = std::is_integral_v<u16>;
        _is_floating_point = std::is_floating_point_v<u16>;
        break;
    case enumeric::euint32:
        _is_signed = std::is_signed_v<u32>;
        _is_integral = std::is_integral_v<u32>;
        _is_floating_point = std::is_floating_point_v<u32>;
        break;
    case enumeric::euint64:
        _is_signed = std::is_signed_v<u64>;
        _is_integral = std::is_integral_v<u64>;
        _is_floating_point = std::is_floating_point_v<u64>;
        break;
    case enumeric::efloat:
        _is_signed = std::is_signed_v<f32>;
        _is_integral = std::is_integral_v<f32>;
        _is_floating_point = std::is_floating_point_v<f32>;
        break;
    case enumeric::edouble:
        _is_signed = std::is_signed_v<f64>;
        _is_integral = std::is_integral_v<f64>;
        _is_floating_point = std::is_floating_point_v<f64>;
        break;
    }
}

nnumeric::~nnumeric() = default;

} // namespace ntr
