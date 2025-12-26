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
static void vector_put(void* container, void* value)
{
    static_cast<T*>(container)->push_back(*static_cast<typename T::value_type*>(value));
}

template <typename T>
static void set_put(void* container, void* value)
{
    static_cast<T*>(container)->insert(*static_cast<typename T::value_type*>(value));
}

template <typename T>
static void map_put(void* container, void* key_value)
{
    std::pair<void*, void*> pair = *static_cast<std::pair<void*, void*>*>(key_value);
    static_cast<T*>(container)->insert_or_assign(
        *static_cast<typename T::key_type*>(pair.first),
        *static_cast<typename T::mapped_type*>(pair.second));
}

template <typename T>
static void list_for_each(void* container, void* callback)
{
    for (auto& value : *static_cast<T*>(container))
    {
        (*static_cast<std::function<void(nobject&&)>*>(callback))(
            nregistrar::get_type<typename T::value_type>()->ref_instance(value));
    }
}

template <typename T>
static void map_for_each(void* container, void* callback)
{
    for (auto& [key, value] : *static_cast<T*>(container))
    {
        (*static_cast<std::function<void(nobject&&, nobject&&)>*>(callback))(
            nregistrar::get_type<typename T::key_type>()->ref_instance(key),
            nregistrar::get_type<typename T::mapped_type>()->ref_instance(value));
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
          &ncontainer_ops_function::map_put<nhash_map<Args...>>,
          &ncontainer_ops_function::map_for_each<nhash_map<Args...>>,
          &ncontainer_ops_function::clear<nhash_map<Args...>>,
          &ncontainer_ops_function::size<nhash_map<Args...>>,
      }
{
}

template <typename... Args>
ncontainer_ops_factory<nhash_set<Args...>>::ncontainer_ops_factory()
    : ops {
          &ncontainer_ops_function::set_put<nhash_set<Args...>>,
          &ncontainer_ops_function::list_for_each<nhash_set<Args...>>,
          &ncontainer_ops_function::clear<nhash_set<Args...>>,
          &ncontainer_ops_function::size<nhash_set<Args...>>,
      }
{
}

template <typename... Args>
ncontainer_ops_factory<std::vector<Args...>>::ncontainer_ops_factory()
    : ops {
          &ncontainer_ops_function::vector_put<std::vector<Args...>>,
          &ncontainer_ops_function::list_for_each<std::vector<Args...>>,
          &ncontainer_ops_function::clear<std::vector<Args...>>,
          &ncontainer_ops_function::size<std::vector<Args...>>,
      }
{
}

template <typename... Args>
ncontainer_ops_factory<std::map<Args...>>::ncontainer_ops_factory()
    : ops { &ncontainer_ops_function::map_put<std::map<Args...>>,
            &ncontainer_ops_function::map_for_each<std::map<Args...>>,
            &ncontainer_ops_function::clear<std::map<Args...>>,
            &ncontainer_ops_function::size<std::map<Args...>> }
{
}

template <typename... Args>
ncontainer_ops_factory<std::unordered_map<Args...>>::ncontainer_ops_factory()
    : ops { &ncontainer_ops_function::map_put<std::unordered_map<Args...>>,
            &ncontainer_ops_function::map_for_each<std::unordered_map<Args...>>,
            &ncontainer_ops_function::clear<std::unordered_map<Args...>>,
            &ncontainer_ops_function::size<std::unordered_map<Args...>> }
{
}

template <typename... Args>
ncontainer_ops_factory<std::set<Args...>>::ncontainer_ops_factory()
    : ops {
          &ncontainer_ops_function::set_put<std::set<Args...>>,
          &ncontainer_ops_function::list_for_each<std::set<Args...>>,
          &ncontainer_ops_function::clear<std::set<Args...>>,
          &ncontainer_ops_function::size<std::set<Args...>>,
      }
{
}

template <typename... Args>
ncontainer_ops_factory<std::unordered_set<Args...>>::ncontainer_ops_factory()
    : ops {
          &ncontainer_ops_function::set_put<std::unordered_set<Args...>>,
          &ncontainer_ops_function::list_for_each<std::unordered_set<Args...>>,
          &ncontainer_ops_function::clear<std::unordered_set<Args...>>,
          &ncontainer_ops_function::size<std::unordered_set<Args...>>,
      }
{
}

} // namespace ntr