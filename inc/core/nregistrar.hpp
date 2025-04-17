#pragma once

#include "nfactory.hpp"

namespace ntr
{

class NTR_API nregistrar
{

public:
    NTR_SINGLETON_IMPL(nregistrar)

    template <typename T>
    NTR_INLINE static auto& factory_wrapper();

    template <typename T>
    NTR_INLINE static const ntype* get_type();

    template <typename T>
    NTR_INLINE auto& regist(std::string_view name);

    const ntype* get_type(std::string_view name);
    void regist(std::string_view name, ntype* type);

private:
    nregistrar() = default;
    ~nregistrar() = default;

    std::unordered_map<std::string_view, const ntype*> _type_map;
};

} // namespace ntr