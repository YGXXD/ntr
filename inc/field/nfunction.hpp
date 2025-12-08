//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "nfield.hpp"
#include "../tool/nvector.hpp"
#include "../core/nobject.hpp"

namespace ntr
{

class NTR_API nfunction : public nfield
{
public:
    nfunction(const ntype* parent_type, std::string_view name, bool is_static);
    template <typename Ret, typename... Args>
    nfunction(const ntype* parent_type, std::string_view name, Ret (*fun)(Args...));
    template <typename Ret, typename ClassT, typename... Args>
    nfunction(const ntype* parent_type, std::string_view name,
              Ret (ClassT::*fun)(Args...));
    template <typename Ret, typename ClassT, typename... Args>
    nfunction(const ntype* parent_type, std::string_view name,
              Ret (ClassT::*fun)(Args...) const);
    NTR_DELETE_COPY_MOVE_CONSTRUCTORS(nfunction)
    ~nfunction();

    nobject call(const nvector<nwrapper>& arg_arr) const;

    const class nclass* class_type() const;
    NTR_INLINE bool is_static() const { return _is_static; }
    NTR_INLINE const ntype* return_type() const { return _return_type; }
    NTR_INLINE const auto& argument_types() const { return _argument_types; }

private:
    template <typename Ret, typename... Args, typename OP>
    static NTR_INLINE nobject wrapper_call(OP op, nvector<nwrapper>::iterator it);

    template <typename Ret, typename... Args>
    NTR_INLINE void init_function_types();

    bool _is_static;
    const ntype* _return_type;
    nvector<const ntype*> _argument_types;
    std::function<nobject(const nvector<nwrapper>&)> _function;
};

} // namespace ntr

#include "../impl/field/nfunction.inl"