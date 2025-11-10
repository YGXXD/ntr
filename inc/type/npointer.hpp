//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "ntype.hpp"

namespace ntr
{

class NTR_API npointer : public ntype
{
public:
    npointer(uint8_t depth, bool pointing_is_const, const ntype* pointed_type,
             operations* ops, std::string_view name);
    NTR_DELETE_COPY_MOVE_CONSTRUCTORS(npointer)
    ~npointer();

    static void* get_value(const class nobject& pointer);
    static void set_value(nobject& pointer, void* value);
    static nobject get_target(const nobject& pointer);

    NTR_INLINE uint8_t depth() const { return _depth; }
    NTR_INLINE bool pointing_is_const() const { return _pointing_is_const; }
    NTR_INLINE const ntype* pointing_type() const { return _pointing_type; }

private:
    uint8_t _depth;
    bool _pointing_is_const;
    const ntype* _pointing_type;
};

} // namespace ntr
