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
    NTR_SINGLETON_IMPL(ncontainer_ops_factory)
    ncontainer::operations ops;
};

template <typename... Args>
struct ncontainer_ops_factory<nhash_map<Args...>>
{
private:
    ncontainer_ops_factory();
    ~ncontainer_ops_factory() = default;

public:
    NTR_SINGLETON_IMPL(ncontainer_ops_factory)
    ncontainer::operations ops;
};

template <typename... Args>
struct ncontainer_ops_factory<nhash_set<Args...>>
{
private:
    ncontainer_ops_factory();
    ~ncontainer_ops_factory() = default;

public:
    NTR_SINGLETON_IMPL(ncontainer_ops_factory)
    ncontainer::operations ops;
};

template <typename... Args>
struct ncontainer_ops_factory<std::vector<Args...>>
{
private:
    ncontainer_ops_factory();
    ~ncontainer_ops_factory() = default;

public:
    NTR_SINGLETON_IMPL(ncontainer_ops_factory)
    ncontainer::operations ops;
};

template <typename... Args>
struct ncontainer_ops_factory<std::map<Args...>>
{
private:
    ncontainer_ops_factory();
    ~ncontainer_ops_factory() = default;

public:
    NTR_SINGLETON_IMPL(ncontainer_ops_factory)
    ncontainer::operations ops;
};

template <typename... Args>
struct ncontainer_ops_factory<std::unordered_map<Args...>>
{
private:
    ncontainer_ops_factory();
    ~ncontainer_ops_factory() = default;

public:
    NTR_SINGLETON_IMPL(ncontainer_ops_factory)
    ncontainer::operations ops;
};

template <typename... Args>
struct ncontainer_ops_factory<std::set<Args...>>
{
private:
    ncontainer_ops_factory();
    ~ncontainer_ops_factory() = default;

public:
    NTR_SINGLETON_IMPL(ncontainer_ops_factory)
    ncontainer::operations ops;
};

template <typename... Args>
struct ncontainer_ops_factory<std::unordered_set<Args...>>
{
private:
    ncontainer_ops_factory();
    ~ncontainer_ops_factory() = default;

public:
    NTR_SINGLETON_IMPL(ncontainer_ops_factory)
    ncontainer::operations ops;
};

} // namespace ntr