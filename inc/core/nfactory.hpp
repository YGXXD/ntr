//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../type/ntraits.hpp"

namespace ntr
{

template <ntype::etype E, typename T>
class nfactory;

template <typename T>
class nfactory<ntype::etype::eunknown, T>
{
public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(nfactory<ntype::etype::eunknown, T>)

private:
    nfactory();
    ~nfactory() = default;

    std::unique_ptr<class ntype> _type;
};

template <typename T>
class nfactory<ntype::etype::enumeric, T>
{
    static_assert(
        is_etype_numeric<T>(),
        "ntype::etype::enumeric factory template parameter \"T\" must be numeric type");

public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(nfactory<ntype::etype::enumeric, T>)

private:
    nfactory();
    ~nfactory() = default;

    std::unique_ptr<class nnumeric> _type;
};

template <typename T>
class nfactory<ntype::etype::eenum, T>
{
    static_assert(is_etype_enum<T>(),
                  "ntype::etype::eenum factory template parameter \"T\" must be enum type");

public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(nfactory<ntype::etype::eenum, T>)

    NTR_INLINE nfactory& item(std::string_view name, T value);
    NTR_INLINE nfactory& remove(std::string_view name);

private:
    nfactory();
    ~nfactory() = default;

    std::unique_ptr<class nenum> _type;
};

template <typename T>
class nfactory<ntype::etype::eclass, T>
{
    static_assert(
        is_etype_class<T>(),
        "ntype::etype::eclass factory template parameter \"T\" must be struct or class type");

public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(nfactory<ntype::etype::eclass, T>)

    template <typename Ret, typename... Args>
    NTR_INLINE nfactory& function(std::string_view name, Ret (*fun)(Args...));
    template <typename Ret, typename... Args>
    NTR_INLINE nfactory& function(std::string_view name, Ret (T::*fun)(Args...));
    template <typename Ret, typename... Args>
    NTR_INLINE nfactory& function(std::string_view name, Ret (T::*fun)(Args...) const);

    template <typename U>
    NTR_INLINE nfactory& property(std::string_view name, U(T::*member));
    template <typename U>
    NTR_INLINE nfactory& property(std::string_view name, const U& (T::*getter)() const,
                                  void (T::*setter)(const U&));

    NTR_INLINE nfactory& remove(std::string_view name);

private:
    nfactory();
    ~nfactory() = default;

    std::unique_ptr<class nclass> _type;
};

template <typename T>
class nfactory<ntype::etype::epointer, T>
{
    static_assert(
        is_etype_pointer<T>(),
        "ntype::etype::epointer factory template parameter \"T\" must be pointer type");

public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(nfactory<ntype::etype::epointer, T>)

private:
    nfactory();
    ~nfactory() = default;

    std::unique_ptr<class npointer> _type;
};

} // namespace ntr
