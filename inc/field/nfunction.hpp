//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "nfield.hpp"
#include "core/nobject.hpp"
#include "core/nwrapper.hpp"

namespace ntr
{

class NTR_API nfunction : public nfield
{
public:
    nfunction(const ntype* parent_type, std::string_view name);
    template <typename Ret, typename... Args>
    nfunction(const ntype* parent_type, std::string_view name, Ret (*fun)(Args...));
    template <typename Ret, typename ClassT, typename... Args>
    nfunction(const ntype* parent_type, std::string_view name,
              Ret (ClassT::*fun)(Args...));
    template <typename Ret, typename ClassT, typename... Args>
    nfunction(const ntype* parent_type, std::string_view name,
              Ret (ClassT::*fun)(Args...) const);

    nobject call(const std::vector<nwrapper>& arg_arr) const;

    const class nclass* class_type() const;
    NTR_INLINE const ntype* return_type() const { return _return_type; }
    NTR_INLINE const auto& argument_types() const { return _argument_types; }

private:
    template <typename Ret, typename... Args, typename OP>
    static NTR_INLINE nobject wrapper_call(OP op,
                                           std::vector<nwrapper>::const_iterator it);

    template <typename Ret, typename... Args>
    NTR_INLINE void init_function_types();

    const ntype* _return_type;
    std::vector<const ntype*> _argument_types;
    std::function<nobject(const std::vector<nwrapper>&)> _function;
};

} // namespace ntr
