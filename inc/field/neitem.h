#pragma once

#include "nfield.h"

namespace ntr
{

class neitem : public nfield
{
public:
    neitem(ntype* parent_type, std::string_view name, long value);

    inline long value() const { return _value; }

private:
    long _value;
};

} // namespace ntr
