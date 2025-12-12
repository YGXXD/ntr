//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "type/ncontainer.hpp"
#include "type/npointer.hpp"
#include "type/nclass.hpp"

namespace ntr
{

ncontainer::ncontainer(const ntype* iterator_type, const ntype* element_type,
                       operations* container_ops, uint32_t size, uint32_t align,
                       ntype::operations* ops)
    : ntype(ntype::etype::econtainer, size, align, ops), _iterator_type(iterator_type),
      _element_type(element_type), _container_ops(container_ops)
{
}

ncontainer::~ncontainer() = default;

void ncontainer::puts(const nwrapper& container, const nvector<nwrapper>& elements) const
{
    if (container.type() != this)
        throw std::invalid_argument(
            "nncontainer::put : container's type is not this container type");
    for (auto& element : elements)
    {
        if (element.type() == _element_type)
        {
            _container_ops->put(container.data(), element.data());
            continue;
        }
        const npointer* put_element_type_as_pointer = element.type()->as_pointer();
        const npointer* element_type_as_pointer = _element_type->as_pointer();
        if (put_element_type_as_pointer && element_type_as_pointer &&
            put_element_type_as_pointer->is_class() &&
            element_type_as_pointer->is_class())
        {
            void* put_element = *static_cast<void**>(element.data());
            put_element = put_element_type_as_pointer->as_class()->cast_to(
                element_type_as_pointer->as_class(), put_element);
            if (put_element)
            {
                _container_ops->put(container.data(), &put_element);
                continue;
            }
        }
        throw std::invalid_argument(
            "nncontainer::put : element's type is not this element type");
    }
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

nobject ncontainer::begin(const nwrapper& container) const
{
    if (container.type() != this)
        throw std::invalid_argument(
            "ncontainer::begin : container's type is not this container type");
    return _container_ops->begin(container.data());
}

void ncontainer::next(const nwrapper& iterator) const
{
    if (iterator.type() != _iterator_type)
        throw std::invalid_argument(
            "nncontainer::next : iterator's type is not this iterator type");
    return _container_ops->next(iterator.data());
}

nobject ncontainer::end(const nwrapper& container) const
{
    if (container.type() != this)
        throw std::invalid_argument(
            "ncontainer::end : container's type is not this container type");
    return _container_ops->end(container.data());
}

bool ncontainer::equal(const nwrapper& iterator1, const nwrapper& iterator2) const
{
    if (iterator1.type() != _iterator_type || iterator2.type() != _iterator_type)
        throw std::invalid_argument(
            "nncontainer::equal : iterator's type is not this iterator type");
    return _container_ops->equal(iterator1.data(), iterator2.data());
}

nobject ncontainer::get(const nwrapper& iterator) const
{
    if (iterator.type() != _iterator_type)
        throw std::invalid_argument(
            "nncontainer::get : iterator's type is not this iterator type");
    return _container_ops->get(iterator.data());
}

} // namespace ntr
