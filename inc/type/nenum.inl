#pragma once

#include "nenum.h"

namespace ntr
{

template <typename T>
const neitem* nenum::get_eitem(std::enable_if_t<!std::is_same_v<T, long>, T> value) const
{
    return get_eitem(static_cast<long>(value));
}

} // namespace ntr