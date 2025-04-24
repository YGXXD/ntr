#pragma once

#include "ntype.hpp"

namespace ntr
{

class NTR_API npointer : public ntype
{
public:
    npointer(uint8_t depth, const ntype* pointed_type, std::string_view name, operations* ops);

    static void* get_value(const class nobject& pointer);
    static void set_value(nobject& pointer, void* value);
    static nobject get_target(const nobject& pointer);

    NTR_INLINE uint8_t depth() const { return _depth; }
    NTR_INLINE const ntype* pointing_type() const { return _pointing_type; }

private:
    uint8_t _depth;
    const ntype* _pointing_type;
};

} // namespace ntr
