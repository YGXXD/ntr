#pragma once

#include "ntype.hpp"

namespace ntr
{

class NTR_API nlist : public ntype
{
public:
    static void push_back(nobject& list, const nwrapper& wrapper);
    static void push_front(nobject& list, const nwrapper& wrapper);

    static nobject back(nobject& list);
    static nobject front(nobject& list);

    static void insert_copy(nobject& list, size_t index, const nwrapper& wrapper);
    static void insert_move(nobject& list, size_t index, const nwrapper& wrapper);

    static void erase(nobject& list, size_t index);

    nlist(std::string_view name, uint32_t size, operations* ops);
};

} // namespace ntr