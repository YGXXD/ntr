#pragma once

#include "nbasic.h"
#include "nenum.h"
#include "nclass.h"

namespace ntr
{

template <ntype::etype E, typename T>
struct nfactory;

template <typename T>
struct nfactory<ntype::etype::ebasic, T> : singleton<nfactory<ntype::etype::ebasic, T>>
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
            _type = std::make_unique<nbasic>(nbasic::to_ebasic<T>(), name);
        return *this;
    }

    std::unique_ptr<nbasic> _type = nullptr;
};

template <typename T>
struct nfactory<ntype::etype::eenum, T> : singleton<nfactory<ntype::etype::eenum, T>>
{
    static_assert(std::is_enum_v<T>, "enum type factory must be used with an enum type");

    template <typename U>
    friend struct singleton;
    friend struct nefuren;

    inline nfactory& add(std::string_view name, T value)
    {
        _type->add_eitem(name, value);
        return *this;
    }

    inline nfactory& remove(std::string_view name)
    {
        _type->remove_eitem(name);
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
