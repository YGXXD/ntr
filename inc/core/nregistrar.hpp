//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "nfactory.hpp"
#include "../tool/ntable.hpp"

namespace ntr
{

class NTR_API nregistrar
{

public:
    NTR_SINGLETON_IMPL(nregistrar)

    template <typename T>
    static NTR_INLINE auto& factory_wrapper();

    template <typename T>
    static NTR_INLINE const auto* get_type();

    template <typename T>
    NTR_INLINE auto& regist_type(std::string_view name);

    const ntype* get_type(std::string_view name);
    void regist_type(std::string_view name, ntype* type);

private:
    nregistrar() = default;
    ~nregistrar() = default;

    nhash_map<std::string_view, const ntype*> _type_map;
};

} // namespace ntr