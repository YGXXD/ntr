//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "nhash_table.hpp"

namespace ntr
{

template <class Value>
struct table_set_traits
{
    using key_type = Value;
    using value_type = Value;
    using item_type = Value;
    static constexpr auto get_key = [](void* item_data) -> void*
    {
        return static_cast<key_type*>(item_data);
    };
};

template <class Value, class Hash = std::hash<Value>>
class nhash_set : public nhash_table<table_set_traits<Value>, Hash>
{
};

} // namespace ntr