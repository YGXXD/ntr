#pragma once

#include "nbasic.h"
#include "nenum.h"
#include "nclass.h"

namespace ntr
{

template <etype E, typename T>
struct nfactory;

template <typename T>
struct nfactory<etype::eenum, T>
{
    static_assert(std::is_enum_v<T>, "enum type factory must be used with an enum type");
    friend struct nregister;

    static inline nfactory& instance()
    {
        static nfactory _instance;
        return _instance;
    }

    inline nfactory& add(const std::string& name, T value)
    {
        _type->add_item(name, value);
        return *this;
    }

    inline nfactory& remove(const std::string& name)
    {
        _type->remove_item(name);
        return *this;
    }

private:
    nfactory() = default;
    ~nfactory() = default;

    inline nfactory& init(const std::string& name)
    {
        if (_type == nullptr)
            _type = std::make_unique<nenum>(name);
        return *this;
    }

    std::unique_ptr<nenum> _type = nullptr;
};

} // namespace ntr
