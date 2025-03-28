#pragma once

#include "ntype.h"

namespace ntr
{

enum class ebasic
{
    ebool = 0,
    echar,
    ewchar,
    eint8_t,
    eint16_t,
    eint32_t,
    eint64_t,
    euint8_t,
    euint16_t,
    euint32_t,
    euint64_t,
    efloat,
    edouble,
    elongdouble,
};

struct nbasic : ntype
{
    nbasic(ebasic basic_kind, const std::string& name)
        : ntype(etype::ebasic, name), _basic_kind(basic_kind)
    {
    }
    nbasic(ebasic basic_kind, std::string&& name)
        : ntype(etype::ebasic, std::move(name)), _basic_kind(basic_kind)
    {
    }

    inline ebasic basic_kind() const { return _basic_kind; }

private:
    ebasic _basic_kind;
};

} // namespace ntr
