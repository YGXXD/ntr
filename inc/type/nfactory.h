#pragma once

#include "ntype.h"
#include "../singleton.h"

namespace ntr
{

template <ntype::etype E, typename T>
struct nfactory;

template <typename T>
struct nfactory<ntype::etype::eunknown, T>
    : singleton<nfactory<ntype::etype::eunknown, T>>
{
    template <typename U>
    friend struct singleton;
    friend struct nephren;

private:
    nfactory();
    ~nfactory() = default;

    std::unique_ptr<ntype> _type;
};

template <typename T>
struct nfactory<ntype::etype::enumeric, T>
    : singleton<nfactory<ntype::etype::enumeric, T>>
{
    static_assert(
        ntype::is_numeric<T>(),
        "ntype::etype::enumeric factory template param \"T\" must be numeric type");

    template <typename U>
    friend struct singleton;
    friend struct nephren;

private:
    nfactory();
    ~nfactory() = default;

    std::unique_ptr<struct nnumeric> _type;
};

template <typename T>
struct nfactory<ntype::etype::eenum, T> : singleton<nfactory<ntype::etype::eenum, T>>
{
    static_assert(ntype::is_enum<T>(),
                  "ntype::etype::eenum factory template param \"T\" must be enum type");

    template <typename U>
    friend struct singleton;
    friend struct nephren;

    nfactory& item(std::string_view name, T value);
    nfactory& remove(std::string_view name);

private:
    nfactory();
    ~nfactory() = default;

    std::unique_ptr<struct nenum> _type;
};

template <typename T>
struct nfactory<ntype::etype::eclass, T> : singleton<nfactory<ntype::etype::eclass, T>>
{
    static_assert(
        ntype::is_class<T>(),
        "ntype::etype::eclass factory template param \"T\" must be class or struct type");

    template <typename U>
    friend struct singleton;
    friend struct nephren;

    template <typename Ret, typename... Args>
    nfactory& function(std::string_view name, Ret (*fun)(Args...));
    template <typename Ret, typename... Args>
    nfactory& function(std::string_view name, Ret (T::*fun)(Args...));
    template <typename Ret, typename... Args>
    nfactory& function(std::string_view name, Ret (T::*fun)(Args...) const);

    template <typename U>
    nfactory& property(std::string_view name, U(T::*member));
    template <typename U>
    nfactory& property(std::string_view name, U (T::*getter)() const,
                       void (T::*setter)(const U&));

    nfactory& remove(std::string_view name);

private:
    nfactory();
    ~nfactory() = default;

    std::unique_ptr<struct nclass> _type;
};

} // namespace ntr
