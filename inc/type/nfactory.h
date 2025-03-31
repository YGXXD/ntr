#pragma once

#include "ntype.h"
#include "../singleton.h"
#include <memory>

namespace ntr
{

template <ntype::etype E, typename T>
struct nfactory;

template <typename T>
struct nfactory<ntype::etype::ebasic, T> : singleton<nfactory<ntype::etype::ebasic, T>>
{
    static_assert(
        std::is_fundamental_v<T>,
        "ntype::etype::ebasic factory template param \"T\" must be fundamental type");

    template <typename U>
    friend struct singleton;
    friend struct nephren;

private:
    nfactory() = default;
    ~nfactory() = default;

    nfactory& init(std::string_view name);

    std::unique_ptr<struct nbasic> _type = nullptr;
};

template <typename T>
struct nfactory<ntype::etype::eenum, T> : singleton<nfactory<ntype::etype::eenum, T>>
{
    static_assert(std::is_enum_v<T>,
                  "ntype::etype::eenum factory template param \"T\" must be enum type");

    template <typename U>
    friend struct singleton;
    friend struct nephren;

    nfactory& item(std::string_view name, T value);
    nfactory& remove(std::string_view name);

private:
    nfactory() = default;
    ~nfactory() = default;

    nfactory& init(std::string_view name);

    std::unique_ptr<struct nenum> _type = nullptr;
};

template <typename T>
struct nfactory<ntype::etype::eclass, T> : singleton<nfactory<ntype::etype::eclass, T>>
{
    static_assert(
        std::is_class_v<T>,
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
                       void (T::*setter)(U));

    nfactory& remove(std::string_view name);

private:
    nfactory() = default;
    ~nfactory() = default;

    nfactory& init(std::string_view name);

    std::unique_ptr<struct nclass> _type = nullptr;
};

} // namespace ntr
