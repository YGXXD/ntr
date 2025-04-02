#pragma once

#include "nfield.h"

namespace ntr
{

struct neitem : nfield
{
    neitem(ntype* parent_type, std::string_view name, long value);

    inline long value() const { return _value; }

private:
    long _value;
};

} // namespace ntr
