//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "nfield.hpp"
#include "../util/nvector.hpp"
#include "../core/nobject.hpp"

namespace ntr
{

class NTR_API nfunction : public nfield
{
public:
    nfunction(const ntype* parent_type, std::string_view name, bool is_static,
              const ntype* return_type, nvector<const ntype*>&& argument_types,
              std::function<nobject(const nvector<nwrapper>&)>&& function);
    NTR_DELETE_COPY_MOVE_CONSTRUCTORS(nfunction)
    ~nfunction();

    nobject call(const nvector<nwrapper>& arg_arr) const;

    const class nclass* class_type() const;
    NTR_INLINE bool is_static() const { return _is_static; }
    NTR_INLINE const ntype* return_type() const { return _return_type; }
    NTR_INLINE const auto& argument_types() const { return _argument_types; }

private:
    bool _is_static;
    const ntype* _return_type;
    nvector<const ntype*> _argument_types;
    std::function<nobject(const nvector<nwrapper>&)> _function;
};

} // namespace ntr