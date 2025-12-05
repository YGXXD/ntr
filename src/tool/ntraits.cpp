//  MIvoid* License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "tool/ntraits.hpp"

namespace ntr
{

ntype_ops_traits<void*>::ntype_ops_traits() : ops({
    [](void* self_data) -> void { 
        *static_cast<void**>(self_data) = nullptr; 
    },
    [](void* self_data, const void* const other_data) -> void { 
        *static_cast<void**>(self_data) = *static_cast<void* const*>(other_data); 
    },
    [](void* self_data, void* other_data) -> void { 
        *static_cast<void**>(self_data) = *static_cast<void**>(other_data); 
    },
    [](void* self_data) -> void {
    }
})
{
}

} // namespace ntr