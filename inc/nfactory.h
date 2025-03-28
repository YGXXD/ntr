#pragma once

#include "util.h"

namespace ntr
{

template <etype E, typename T>
struct nfactory;

template <typename T>
struct nfactory<etype::ebasic, T> : singleton<nfactory<etype::ebasic, T>>
{
    static_assert(std::is_fundamental_v<T>,
                  "basic type factory must be used with a fundamental type");

    template <typename U>
    friend struct singleton;
    friend struct nefuren;

private:
    nfactory() = default;
    ~nfactory() = default;

    inline nfactory& init(std::string_view name)
    {
        if (_type == nullptr)
            _type = std::make_unique<nbasic>(cast_ebasic<T>(), name);
        return *this;
    }

    std::unique_ptr<nbasic> _type = nullptr;
};

template <typename T>
struct nfactory<etype::eenum, T> : singleton<nfactory<etype::eenum, T>>
{
    static_assert(std::is_enum_v<T>, "enum type factory must be used with an enum type");

    template <typename U>
    friend struct singleton;
    friend struct nefuren;

    inline nfactory& add(std::string_view name, T value)
    {
        _type->add_item(name, value);
        return *this;
    }

    inline nfactory& remove(std::string_view name)
    {
        _type->remove_item(name);
        return *this;
    }

private:
    nfactory() = default;
    ~nfactory() = default;

    inline nfactory& init(std::string_view name)
    {
        if (_type == nullptr)
            _type = std::make_unique<nenum>(name);
        return *this;
    }

    std::unique_ptr<nenum> _type = nullptr;
};

} // namespace ntr
