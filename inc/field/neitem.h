#pragma once

#include "nfield.h"

namespace ntr
{

class NTR_API neitem : public nfield
{
public:
    neitem(ntype* parent_type, std::string_view name, long value);

    const class nenum* enum_type() const;
    NTR_INLINE long value() const { return _value; }

private:
    long _value;
};

} // namespace ntr
