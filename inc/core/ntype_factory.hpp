//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"
#include "../type/ntype.hpp"
#include "../type/nnumeric.hpp"
#include "../type/nenum.hpp"
#include "../type/nclass.hpp"
#include "../type/npointer.hpp"
#include "../type/ncontainer.hpp"
#include "../util/ntype_traits.hpp"

namespace ntr
{

template <ntype::etype E, typename T>
class ntype_factory;

template <>
class NTR_API ntype_factory<ntype::etype::eunknown, void>
{
public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(ntype_factory)

private:
    ntype_factory();
    ~ntype_factory() = default;

    ntype _type;
};

template <typename T>
class ntype_factory<ntype::etype::eunknown, T>
{
public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(ntype_factory)

private:
    ntype_factory();
    ~ntype_factory() = default;

    ntype _type;
};

template <typename T>
class ntype_factory<ntype::etype::enumeric, T>
{
    static_assert(
        is_etype_numeric<T>::value,
        "ntype::etype::enumeric factory template parameter \"T\" must be numeric type");

public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(ntype_factory)

private:
    ntype_factory();
    ~ntype_factory() = default;

    nnumeric _type;
};

template <typename T>
class ntype_factory<ntype::etype::eenum, T>
{
    static_assert(
        is_etype_enum<T>::value,
        "ntype::etype::eenum factory template parameter \"T\" must be enum type");

public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(ntype_factory)

    NTR_INLINE ntype_factory& item(std::string_view name, T value);
    NTR_INLINE ntype_factory& remove(std::string_view name);

private:
    ntype_factory();
    ~ntype_factory() = default;

    nenum _type;
};

template <typename T>
class ntype_factory<ntype::etype::eclass, T>
{
    static_assert(is_etype_class<T>::value,
                  "ntype::etype::eclass factory template parameter "
                  "\"T\" must be struct or class type");

public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(ntype_factory)

    template <typename U, typename = std::enable_if_t<std::is_base_of_v<U, T>>>
    NTR_INLINE ntype_factory& base_type();

    template <typename Ret, typename... Args>
    NTR_INLINE ntype_factory& function(std::string_view name, Ret (*fun)(Args...));
    template <typename Ret, typename... Args>
    NTR_INLINE ntype_factory& function(std::string_view name, Ret (T::*fun)(Args...));
    template <typename Ret, typename... Args>
    NTR_INLINE ntype_factory& function(std::string_view name,
                                       Ret (T::*fun)(Args...) const);

    template <typename U>
    NTR_INLINE ntype_factory& property(std::string_view name, U(T::* member));
    template <typename U>
    NTR_INLINE ntype_factory& property(std::string_view name,
                                       const U& (T::*getter_fun)() const,
                                       void (T::*setter_fun)(const U&));

    NTR_INLINE ntype_factory& remove(std::string_view name);

private:
    ntype_factory();
    ~ntype_factory() = default;

    nclass _type;
};

template <typename T>
class ntype_factory<ntype::etype::epointer, T>
{
    static_assert(
        is_etype_pointer<T>::value,
        "ntype::etype::epointer factory template parameter \"T\" must be pointer type");

public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(ntype_factory)

private:
    ntype_factory();
    ~ntype_factory() = default;

    npointer _type;
};

template <typename T>
class ntype_factory<ntype::etype::econtainer, T>
{
    static_assert(is_etype_container<T>::value,
                  "ntype::etype::econtainer factory template "
                  "parameter \"T\" must be container(ntr::nvector, ntr::nhash_map, "
                  "ntr::nhash_set) type");

public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(ntype_factory)

private:
    ntype_factory();
    ~ntype_factory() = default;

    ncontainer _type;
};

} // namespace ntr