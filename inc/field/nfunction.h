#pragma once

#include "nfield.h"
#include <functional>

namespace ntr
{

struct nfunction : nfield
{
    template <typename F>
    nfunction(ntype* parent_type, std::string_view name, F fun);

    const ntype* return_type() const;
    const std::vector<ntype*>& argument_types() const;

private:
    nfunction(ntype* parent_type, std::string_view name);

    template <typename F, size_t... Is>
    void init_argument_types(F fun, std::index_sequence<Is...>);

    ntype* _return_type;
    std::vector<ntype*> _argument_types;
    // std::vector<ntype*> _argument_types;
    // std::function<void*(void*)> _function;
};

} // namespace ntr
