//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"

namespace ntr
{

class NTR_API nfield
{
public:
    enum class efield
    {
        eeitem,
        eproperty,
        efunction
    };

    nfield(const class ntype* parent_type, efield kind, std::string_view name);

    NTR_INLINE const ntype* parent_type() const { return _parent_type; }
    NTR_INLINE efield kind() const { return _kind; }
    NTR_INLINE std::string_view name() const { return _name; }

private:
    efield _kind;
    std::string _name;
    const ntype* _parent_type;
};

} // namespace ntr
