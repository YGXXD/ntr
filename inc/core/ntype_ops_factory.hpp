//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../type/ntype.hpp"

namespace ntr
{

template <typename T>
struct ntype_ops_factory
{
private:
    ntype_ops_factory();
    ~ntype_ops_factory() = default;

public:
    NTR_SINGLETON_IMPL(ntype_ops_factory)
    ntype::operations ops;
};

template <typename T>
struct ntype_ops_factory<T*>
{
    static_assert(false, "pointer type pos must use void*");
};

template <>
struct NTR_API ntype_ops_factory<void*>
{
private:
    ntype_ops_factory();
    ~ntype_ops_factory() = default;

public:
    NTR_SINGLETON_IMPL(ntype_ops_factory)
    ntype::operations ops;
};

} // namespace ntr