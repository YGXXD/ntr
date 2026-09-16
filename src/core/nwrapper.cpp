//  MIT License
//
//  Copyright (c) 2025-2026 有个小小杜
//
//  Created by 有个小小杜
//

#include "core/nwrapper.hpp"
#include "type/nclass.hpp"

namespace ntr
{

nwrapper::nwrapper(const ntype* type, const void* data)
    : _type(type), _pdata(const_cast<void*>(data))
{
    NTR_ASSERT(type != nullptr, "nwrapper::nwrapper : type is nullptr");
    NTR_ASSERT(data != nullptr, "nwrapper::nwrapper : data is nullptr");
}

nwrapper::nwrapper(const nwrapper& other) = default;
nwrapper::nwrapper(nwrapper&& other) = default;
nwrapper& nwrapper::operator=(const nwrapper& other) = default;
nwrapper& nwrapper::operator=(nwrapper&& other) = default;
nwrapper::~nwrapper() = default;

nwrapper nwrapper::cast_to(const ntype* to_type) const
{
    if (_type == to_type)
        return nwrapper(_type, _pdata);
    if (const nclass* class_type = _type->as_class())
    {
        if (void* cast_ptr = class_type->cast_to(to_type->as_class(), _pdata))
            return nwrapper(to_type, cast_ptr);
    }
    NTR_ASSERT(false, "nwrapper::cast_to : type cast failed");
}

} // namespace ntr
