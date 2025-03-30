#pragma once

#include "nfield.h"

namespace ntr
{

struct neitem : nfield
{
    template <typename E>
    neitem(ntype* parent_type, std::string_view name, E value);

    long value() const;

private:
    long _value;
};

} // namespace ntr
