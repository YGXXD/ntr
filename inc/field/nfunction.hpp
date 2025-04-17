#pragma once

#include "nfield.hpp"
#include "../core/nobject.hpp"
#include "../core/nreference.hpp"

namespace ntr
{

class NTR_API nfunction : public nfield
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

    nobject invoke(const std::vector<nreference>& args) const;

    const class nclass* class_type() const;
    NTR_INLINE const ntype* return_type() const { return _return_type; }
    NTR_INLINE const auto& argument_types() const { return _argument_types; }

private:
    template <typename Ret, typename... Args>
    NTR_INLINE void init_function_types();

    const ntype* _return_type;
    std::vector<const ntype*> _argument_types;
    std::function<nobject(const std::vector<nreference>&)> _function;
};

} // namespace ntr
