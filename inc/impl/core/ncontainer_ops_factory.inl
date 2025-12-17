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
static void hash_table_put(void* container, void* element)
{
    static_cast<T*>(container)->insert(*static_cast<typename T::element_type*>(element));
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

template <typename T>
static nobject begin(void* container)
{
    typename T::iterator it = static_cast<T*>(container)->begin();
    return nregistrar::get_type<typename T::iterator>()->move_instance(it);
}

template <typename T>
static void next(void* iterator)
{
    ++(*static_cast<typename T::iterator*>(iterator));
}

template <typename T>
static nobject end(void* container)
{
    typename T::iterator it = static_cast<T*>(container)->end();
    return nregistrar::get_type<typename T::iterator>()->move_instance(it);
}

template <typename T>
static bool equal(void* iterator1, void* iterator2)
{
    return *static_cast<typename T::iterator*>(iterator1) ==
           *static_cast<typename T::iterator*>(iterator2);
}

template <typename T>
static nobject get(void* iterator)
{
    return nregistrar::get_type<typename T::element_type>()->ref_instance(
        **static_cast<typename T::iterator*>(iterator));
}

}; // namespace ncontainer_ops_function

template <typename... Args>
ncontainer_ops_factory<nvector<Args...>>::ncontainer_ops_factory()
    : ops {
          &ncontainer_ops_function::vector_put<nvector<Args...>>,
          &ncontainer_ops_function::clear<nvector<Args...>>,
          &ncontainer_ops_function::size<nvector<Args...>>,
          &ncontainer_ops_function::begin<nvector<Args...>>,
          &ncontainer_ops_function::next<nvector<Args...>>,
          &ncontainer_ops_function::end<nvector<Args...>>,
          &ncontainer_ops_function::equal<nvector<Args...>>,
          &ncontainer_ops_function::get<nvector<Args...>>,
      }
{
}

template <typename... Args>
ncontainer_ops_factory<nhash_map<Args...>>::ncontainer_ops_factory()
    : ops {
          &ncontainer_ops_function::hash_table_put<nhash_map<Args...>>,
          &ncontainer_ops_function::clear<nhash_map<Args...>>,
          &ncontainer_ops_function::size<nhash_map<Args...>>,
          &ncontainer_ops_function::begin<nhash_map<Args...>>,
          &ncontainer_ops_function::next<nhash_map<Args...>>,
          &ncontainer_ops_function::end<nhash_map<Args...>>,
          &ncontainer_ops_function::equal<nhash_map<Args...>>,
          &ncontainer_ops_function::get<nhash_map<Args...>>,
      }
{
}

template <typename... Args>
ncontainer_ops_factory<nhash_set<Args...>>::ncontainer_ops_factory()
    : ops {
          &ncontainer_ops_function::hash_table_put<nhash_set<Args...>>,
          &ncontainer_ops_function::clear<nhash_set<Args...>>,
          &ncontainer_ops_function::size<nhash_set<Args...>>,
          &ncontainer_ops_function::begin<nhash_set<Args...>>,
          &ncontainer_ops_function::next<nhash_set<Args...>>,
          &ncontainer_ops_function::end<nhash_set<Args...>>,
          &ncontainer_ops_function::equal<nhash_set<Args...>>,
          &ncontainer_ops_function::get<nhash_set<Args...>>,
      }
{
}

} // namespace ntr