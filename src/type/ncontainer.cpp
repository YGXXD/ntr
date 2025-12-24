//  MIT License
//
//  Copyright (c) 2025 有个小小杜
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

void ncontainer::put(const nwrapper& container, const nwrapper& element) const
{
    if (container.type() != this)
        throw std::invalid_argument(
            "nncontainer::put : container's type is not this container type");
    if (element.type() != _element_type)
        throw std::invalid_argument(
            "nncontainer::put : element's type is not this element type");
    _container_ops->put(container.data(), element.data());
}

void ncontainer::put(const nwrapper& container, const nwrapper& key,
                     const nwrapper& value) const
{
    if (container.type() != this)
        throw std::invalid_argument(
            "nncontainer::put : container's type is not this container type");
    if (key.type() != _key_type)
        throw std::invalid_argument("nncontainer::put : key's type is not this key type");
    if (value.type() != _value_type)
        throw std::invalid_argument(
            "nncontainer::put : value's type is not this value type");
    std::pair<void*, void*> pair(key.data(), value.data());
    _container_ops->put(container.data(), &pair);
}

void ncontainer::for_each(const nwrapper& container,
                          const std::function<void(nobject&&)>& callback) const
{
    if (container.type() != this)
        throw std::invalid_argument(
            "nncontainer::for_each : container's type is not this container type");
    _container_ops->for_each(container.data(),
                             const_cast<std::function<void(nobject&&)>*>(&callback));
}

void ncontainer::for_each(const nwrapper& container,
                          const std::function<void(nobject&&, nobject&&)>& callback) const
{
    if (container.type() != this)
        throw std::invalid_argument(
            "nncontainer::for_each : container's type is not this container type");
    _container_ops->for_each(
        container.data(),
        const_cast<std::function<void(nobject&&, nobject&&)>*>(&callback));
}

void ncontainer::clear(const nwrapper& container) const
{
    if (container.type() != this)
        throw std::invalid_argument(
            "nncontainer::clear : container's type is not this container type");
    _container_ops->clear(container.data());
}

uint32_t ncontainer::size(const nwrapper& container) const
{
    if (container.type() != this)
        throw std::invalid_argument(
            "nncontainer::size : container's type is not this container type");
    return _container_ops->size(container.data());
}

} // namespace ntr
