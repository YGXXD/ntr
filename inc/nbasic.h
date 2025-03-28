#pragma once

#include "ntype.h"

namespace ntr
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

struct nbasic : ntype
{
    nbasic(ebasic basic_kind, std::string_view name)
        : ntype(etype::ebasic, name), _basic_kind(basic_kind)
    {
    }

    virtual std::vector<const nfield*> fields() const { return {}; }
    inline ebasic basic_kind() const { return _basic_kind; }

private:
    ebasic _basic_kind;
};

} // namespace ntr
