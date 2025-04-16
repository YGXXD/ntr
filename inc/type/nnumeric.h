#pragma once

#include "ntype.h"

namespace ntr
{

class NTR_API nnumeric : public ntype
{
public:
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

    nnumeric(enumeric numeric_kind, std::string_view name);

    NTR_INLINE enumeric numeric_kind() const { return _numeric_kind; }
    NTR_INLINE bool is_signed() const { return _is_signed; }
    NTR_INLINE bool is_floating_point() const { return !_is_integral; }
    NTR_INLINE bool is_integral() const { return _is_integral; }

private:
    enumeric _numeric_kind;
    bool _is_signed;
    bool _is_integral;
};

} // namespace ntr
