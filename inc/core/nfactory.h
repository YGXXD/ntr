#pragma once

#include "factory_util.h"

namespace ntr
{

template <ntype::etype E, typename T,
          typename = std::enable_if_t<!std::is_reference_v<T>>>
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

    std::unique_ptr<ntype> _type;
};

template <typename T>
class nfactory<ntype::etype::enumeric, T>
{
    static_assert(
        is_etype_numeric<T>(),
        "ntype::etype::enumeric factory template param \"T\" must be numeric type");

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
                  "ntype::etype::eenum factory template param \"T\" must be enum type");

public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(nfactory<ntype::etype::eenum, T>)

    nfactory& item(std::string_view name, T value);
    nfactory& remove(std::string_view name);

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
        "ntype::etype::eclass factory template param \"T\" must be class or class type");

public:
    friend class nregistrar;
    NTR_SINGLETON_IMPL(nfactory<ntype::etype::eclass, T>)

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

    std::unique_ptr<class nclass> _type;
};

} // namespace ntr
