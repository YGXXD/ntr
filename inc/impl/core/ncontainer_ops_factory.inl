//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../../core/ncontainer_ops_factory.hpp"
#include "../../core/nregistrar.hpp"

namespace ntr
{

namespace ncontainer_ops_function
{

template <typename T>
static void vector_put(void* container, void* element)
{
    static_cast<T*>(container)->push_back(
        *static_cast<typename T::element_type*>(element));
}

template <typename T>
static void hash_set_put(void* container, void* element)
{
    static_cast<T*>(container)->insert(*static_cast<typename T::element_type*>(element));
}

template <typename T>
static void hash_map_put(void* container, void* element)
{
    std::pair<void*, void*> pair = *static_cast<std::pair<void*, void*>*>(element);
    static_cast<T*>(container)->insert(
        *static_cast<typename T::key_type*>(pair.first),
        *static_cast<typename T::value_type*>(pair.second));
}

template <typename T>
static void list_for_each(void* container, void* callback)
{
    for (auto& element : *static_cast<T*>(container))
    {
        (*static_cast<std::function<void(nobject&&)>*>(callback))(
            nregistrar::get_type<typename T::element_type>()->ref_instance(element));
    }
}

template <typename T>
static void map_for_each(void* container, void* callback)
{
    for (auto& [key, value] : *static_cast<T*>(container))
    {
        (*static_cast<std::function<void(nobject&&, nobject&&)>*>(callback))(
            nregistrar::get_type<typename T::key_type>()->ref_instance(key),
            nregistrar::get_type<typename T::value_type>()->ref_instance(value));
    }
}

template <typename T>
static void clear(void* container)
{
    static_cast<T*>(container)->clear();
}

template <typename T>
static uint32_t size(void* container)
{
    return static_cast<T*>(container)->size();
}

}; // namespace ncontainer_ops_function

template <typename... Args>
ncontainer_ops_factory<nvector<Args...>>::ncontainer_ops_factory()
    : ops {
          &ncontainer_ops_function::vector_put<nvector<Args...>>,
          &ncontainer_ops_function::list_for_each<nvector<Args...>>,
          &ncontainer_ops_function::clear<nvector<Args...>>,
          &ncontainer_ops_function::size<nvector<Args...>>,
      }
{
}

template <typename... Args>
ncontainer_ops_factory<nhash_map<Args...>>::ncontainer_ops_factory()
    : ops {
          &ncontainer_ops_function::hash_map_put<nhash_map<Args...>>,
          &ncontainer_ops_function::map_for_each<nhash_map<Args...>>,
          &ncontainer_ops_function::clear<nhash_map<Args...>>,
          &ncontainer_ops_function::size<nhash_map<Args...>>,
      }
{
}

template <typename... Args>
ncontainer_ops_factory<nhash_set<Args...>>::ncontainer_ops_factory()
    : ops {
          &ncontainer_ops_function::hash_set_put<nhash_set<Args...>>,
          &ncontainer_ops_function::list_for_each<nhash_set<Args...>>,
          &ncontainer_ops_function::clear<nhash_set<Args...>>,
          &ncontainer_ops_function::size<nhash_set<Args...>>,
      }
{
}

} // namespace ntr