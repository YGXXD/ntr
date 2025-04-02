#pragma once

#include "nfield.h"

namespace ntr
{

class nfunction : public nfield
{
public:
    nfunction(ntype* parent_type, std::string_view name);
    template <typename Ret, typename... Args>
    nfunction(ntype* parent_type, std::string_view name, Ret (*fun)(Args...));
    template <typename Ret, typename ClassT, typename... Args>
    nfunction(ntype* parent_type, std::string_view name, Ret (ClassT::*fun)(Args...));
    template <typename Ret, typename ClassT, typename... Args>
    nfunction(ntype* parent_type, std::string_view name,
              Ret (ClassT::*fun)(Args...) const);

    inline const ntype* return_type() const { return _return_type; }
    inline const auto& argument_types() const { return _argument_types; }

private:
    template <typename Ret, typename... Args>
    void init_function_types();

    const ntype* _return_type;
    std::vector<const ntype*> _argument_types;
    // std::vector<ntype*> _argument_types;
    // std::function<void*(void*)> _function;
};

} // namespace ntr
