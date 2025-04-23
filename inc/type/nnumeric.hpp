#pragma once

#include "ntype.hpp"

namespace ntr
{

class NTR_API nnumeric : public ntype
{
public:
    enum class enumeric : uint8_t
    {
        ebool,
        echar,
        ewchar,
        echar16,
        echar32,
        eint8,
        eint16,
        eint32,
        eint64,
        euint8,
        euint16,
        euint32,
        euint64,
        efloat,
        edouble,
    };

    using numeric_types =
        std::tuple<bool, char, wchar_t, char16_t, char32_t, int8_t, int16_t, int32_t,
                   int64_t, uint8_t, uint16_t, uint32_t, uint64_t, float, double>;

    static double get_value(class nobject& numeric);
    static void set_value(nobject& numeric, double value);

    nnumeric(enumeric numeric_kind, uint32_t size, uint32_t align, operations* ops,
             std::string_view name);

    NTR_INLINE enumeric numeric_kind() const { return _numeric_kind; }
    NTR_INLINE bool is_signed() const { return _is_signed; }
    NTR_INLINE bool is_floating_point() const { return _is_floating_point; }
    NTR_INLINE bool is_integral() const { return _is_integral; }

private:
    enumeric _numeric_kind;
    bool _is_signed;
    bool _is_integral;
    bool _is_floating_point;
};

} // namespace ntr
