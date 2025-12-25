//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../type/ncontainer.hpp"

namespace ntr
{

template <typename T>
struct ncontainer_ops_factory;

template <typename... Args>
struct ncontainer_ops_factory<nvector<Args...>>
{
private:
    ncontainer_ops_factory();
    ~ncontainer_ops_factory() = default;

public:
    NTR_SINGLETON_IMPL(ncontainer_ops_factory<nvector<Args...>>)
    ncontainer::operations ops;
};

template <typename... Args>
struct ncontainer_ops_factory<nhash_map<Args...>>
{
private:
    ncontainer_ops_factory();
    ~ncontainer_ops_factory() = default;

public:
    NTR_SINGLETON_IMPL(ncontainer_ops_factory<nhash_map<Args...>>)
    ncontainer::operations ops;
};

template <typename... Args>
struct ncontainer_ops_factory<nhash_set<Args...>>
{
private:
    ncontainer_ops_factory();
    ~ncontainer_ops_factory() = default;

public:
    NTR_SINGLETON_IMPL(ncontainer_ops_factory<nhash_set<Args...>>)
    ncontainer::operations ops;
};

} // namespace ntr