#pragma once

#include "ntype.h"

namespace ntr
{

struct nnumeric : ntype
{
    enum class enumeric : uint8_t
    {
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

    template <typename T>
    static constexpr enumeric to_enumeric();

    nnumeric(enumeric numeric_kind, std::string_view name);

    inline enumeric numeric_kind() const { return _numeric_kind; }
    inline bool is_signed() const { return _is_signed; }
    inline bool is_floating_point() const { return !_is_integral; }
    inline bool is_integral() const { return _is_integral; }

private:
    enumeric _numeric_kind;
    bool _is_signed;
    bool _is_integral;
};

} // namespace ntr
