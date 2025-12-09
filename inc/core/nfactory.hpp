//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../type/ntype.hpp"
#include "../type/nnumeric.hpp"
#include "../type/nenum.hpp"
#include "../type/nclass.hpp"
#include "../type/npointer.hpp"
#include "../util/ntype_traits.hpp"

namespace ntr
{

template <ntype::etype E, typename T>
class nfactory;

template <>
class NTR_API nfactory<ntype::etype::eunknown, void>
{
public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(nfactory<ntype::etype::eunknown, void>)

private:
    nfactory();
    ~nfactory() = default;

    ntype _type;
};

template <typename T>
class nfactory<ntype::etype::eunknown, T>
{
public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(nfactory<ntype::etype::eunknown, T>)

private:
    nfactory();
    ~nfactory() = default;

    ntype _type;
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

    nnumeric _type;
};

template <typename T>
class nfactory<ntype::etype::eenum, T>
{
    static_assert(
        is_etype_enum<T>(),
        "ntype::etype::eenum factory template parameter \"T\" must be enum type");

public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(nfactory<ntype::etype::eenum, T>)

    NTR_INLINE nfactory& item(std::string_view name, T value);
    NTR_INLINE nfactory& remove(std::string_view name);

private:
    nfactory();
    ~nfactory() = default;

    nenum _type;
};

template <typename T>
class nfactory<ntype::etype::eclass, T>
{
    static_assert(is_etype_class<T>(), "ntype::etype::eclass factory template parameter "
                                       "\"T\" must be struct or class type");

public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(nfactory<ntype::etype::eclass, T>)

    template <typename U, typename = std::enable_if_t<std::is_base_of_v<U, T>>>
    NTR_INLINE nfactory& base_type();

    template <typename Ret, typename... Args>
    NTR_INLINE nfactory& function(std::string_view name, Ret (*fun)(Args...));
    template <typename Ret, typename... Args>
    NTR_INLINE nfactory& function(std::string_view name, Ret (T::*fun)(Args...));
    template <typename Ret, typename... Args>
    NTR_INLINE nfactory& function(std::string_view name, Ret (T::*fun)(Args...) const);

    template <typename U>
    NTR_INLINE nfactory& property(std::string_view name, U(T::* member));
    template <typename U>
    NTR_INLINE nfactory& property(std::string_view name, const U& (T::*getter)() const,
                                  void (T::*setter)(const U&));

    NTR_INLINE nfactory& remove(std::string_view name);

private:
    nfactory();
    ~nfactory() = default;

    nclass _type;
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

    npointer _type;
};

} // namespace ntr
