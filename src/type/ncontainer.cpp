//  MIT License
//
//  Copyright (c) 2025-2026 有个小小杜
//
//  Created by 有个小小杜
//

#include "type/ncontainer.hpp"

namespace ntr
{

ncontainer::ncontainer(const ntype* key_type, const ntype* value_type,
                       operations* container_ops, uint16_t size, uint16_t align,
                       ntype::operations* ops)
    : ntype(ntype::etype::econtainer, size, align, ops), _key_type(key_type),
      _value_type(value_type), _container_ops(container_ops)
{
}

ncontainer::~ncontainer() = default;

void ncontainer::put(const nwrapper& container, const nwrapper& value) const
{
    NTR_ASSERT(is_list(), "nncontainer::put : container's type is not a list type");
    NTR_ASSERT(container.type() == this,
               "nncontainer::put : container's type is not this container type");
    NTR_ASSERT(value.type() == _value_type,
               "nncontainer::put : value's type is not this value type");
    _container_ops->put(container.data(), value.data());
}

void ncontainer::for_each(const nwrapper& container,
                          const std::function<void(nobject&&)>& callback) const
{
    NTR_ASSERT(is_list(), "nncontainer::put : container's type is not a list type");
    NTR_ASSERT(container.type() == this,
               "nncontainer::for_each : container's type is not this container type");
    _container_ops->for_each(container.data(),
                             const_cast<std::function<void(nobject&&)>*>(&callback));
}

void ncontainer::put(const nwrapper& container, const nwrapper& key,
                     const nwrapper& value) const
{
    NTR_ASSERT(is_map(), "nncontainer::put : container's type is not a map type");
    NTR_ASSERT(container.type() == this,
               "nncontainer::put : container's type is not this container type");
    NTR_ASSERT(key.type() == _key_type,
               "nncontainer::put : key's type is not this key type");
    NTR_ASSERT(value.type() == _value_type,
               "nncontainer::put : value's type is not this value type");
    std::pair<void*, void*> pair(key.data(), value.data());
    _container_ops->put(container.data(), &pair);
}

void ncontainer::for_each(const nwrapper& container,
                          const std::function<void(nobject&&, nobject&&)>& callback) const
{
    NTR_ASSERT(is_map(), "nncontainer::put : container's type is not a map type");
    NTR_ASSERT(container.type() == this,
               "nncontainer::for_each : container's type is not this container type");
    _container_ops->for_each(
        container.data(),
        const_cast<std::function<void(nobject&&, nobject&&)>*>(&callback));
}

void ncontainer::clear(const nwrapper& container) const
{
    NTR_ASSERT(container.type() == this,
               "nncontainer::clear : container's type is not this container type");
    _container_ops->clear(container.data());
}

uint32_t ncontainer::size(const nwrapper& container) const
{
    NTR_ASSERT(container.type() == this,
               "nncontainer::size : container's type is not this container type");
    return _container_ops->size(container.data());
}

} // namespace ntr
