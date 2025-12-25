//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"
#include "nobject.hpp"
#include "../field/neitem.hpp"
#include "../field/nfunction.hpp"
#include "../field/nproperty.hpp"

namespace ntr
{

class NTR_API nfield_factory
{
public:
    static std::unique_ptr<neitem> make_eitem(ntype* parent_type, std::string_view name,
                                              nenum::enum_integer_type value);

    template <typename T, typename ClassT>
    static NTR_INLINE std::unique_ptr<nproperty>
    make_property(const ntype* parent_type, std::string_view name, T(ClassT::* member));

    template <typename T, typename ClassT>
    static NTR_INLINE std::unique_ptr<nproperty>
    make_property(const ntype* parent_type, std::string_view name,
                  const T& (ClassT::*getter_fun)() const,
                  void (ClassT::*setter_fun)(const T&));

    template <typename Ret, typename... Args>
    static NTR_INLINE std::unique_ptr<nfunction>
    make_function(const ntype* parent_type, std::string_view name, Ret (*fun)(Args...));

    template <typename Ret, typename ClassT, typename... Args>
    static NTR_INLINE std::unique_ptr<nfunction>
    make_function(const ntype* parent_type, std::string_view name,
                  Ret (ClassT::*fun)(Args...));

    template <typename Ret, typename ClassT, typename... Args>
    static NTR_INLINE std::unique_ptr<nfunction>
    make_function(const ntype* parent_type, std::string_view name,
                  Ret (ClassT::*fun)(Args...) const);

private:
    template <typename... Args>
    static NTR_INLINE nvector<const ntype*> make_function_args();

    template <typename Ret, typename... Args, typename OP>
    static NTR_INLINE nobject function_call(OP op, nvector<nwrapper>::iterator it);
};

} // namespace ntr