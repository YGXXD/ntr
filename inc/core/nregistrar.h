#pragma once

#include "nfactory.h"
#include "singleton.h"

namespace ntr
{

class nregistrar : public singleton<nregistrar>
{

public:
    template <typename T>
    friend class singleton;

    template <typename T>
    static auto& factory_wrapper();

    template <typename T>
    static const ntype* get_type();

    template <typename T>
    auto& regist(std::string_view name);

    const ntype* get_type(std::string_view name);
    void regist(std::string_view name, ntype* type);

private:
    nregistrar() = default;
    ~nregistrar() = default;

    std::unordered_map<std::string_view, const ntype*> _type_map;
};

} // namespace ntr