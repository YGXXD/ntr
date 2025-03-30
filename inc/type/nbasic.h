#pragma once

#include "ntype.h"

namespace ntr
{

struct nbasic : ntype
{
    enum class ebasic
    {
        ebool,
        echar,
        ewchar,
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
        elongdouble,
    };

    template <typename T>
    static constexpr ebasic to_ebasic();

    nbasic(ebasic basic_kind, std::string_view name);

    ebasic basic_kind() const;

private:
    ebasic _basic_kind;
};

} // namespace ntr
