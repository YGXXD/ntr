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
    npointer(const ntype* dereference_type);
    NTR_DELETE_COPY_MOVE_CONSTRUCTORS(npointer)
    ~npointer();

    static void* get_value(const nobject& pointer);
    static void set_value(nobject& pointer, void* value);

    nobject dereference(const nwrapper& pointer) const;
    NTR_INLINE const ntype* dereference_type() const { return _dereference_type; }

private:
    const ntype* _dereference_type;
};

} // namespace ntr
