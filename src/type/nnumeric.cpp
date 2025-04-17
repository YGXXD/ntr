#include "../../inc/type/nnumeric.hpp"

namespace ntr
{

nnumeric::nnumeric(enumeric numeric_kind, uint32_t size, operations* ops,
                   std::string_view name)
    : ntype(etype::enumeric, size, ops, name), _numeric_kind(numeric_kind)
{
    switch (numeric_kind)
    {
    case enumeric::eint8:
    case enumeric::eint16:
    case enumeric::eint32:
    case enumeric::eint64:
        _is_signed = true;
        _is_integral = true;
        break;
    case enumeric::euint8:
    case enumeric::euint16:
    case enumeric::euint32:
    case enumeric::euint64:
        _is_signed = false;
        _is_integral = true;
        break;
    case enumeric::efloat:
    case enumeric::edouble:
        _is_signed = false;
        _is_integral = false;
        break;
    }
}

} // namespace ntr
