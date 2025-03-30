#pragma once

#include "nfunction.h"
#include "../function_traits.h"
#include "../nefuren.h"

namespace ntr
{

// construct
inline nfunction::nfunction(ntype* parent_type, std::string_view name)
    : nfield(parent_type, efield::eproperty, name)
{
}

template <typename F>
inline nfunction::nfunction(ntype* parent_type, std::string_view name, F fun)
    : nfunction(parent_type, name)
{
    static_assert(std::is_function_v<std::remove_pointer_t<F>> ||
                      std::is_member_function_pointer_v<F>,
                  "nfunction construct param \"fun\" must use function, function "
                  "pointer and member function pointer");
    using Traits = member_function_traits<F>;
    if constexpr (std::is_member_function_pointer_v<F>)
    {
        assert(parent_type != nefuren::get_type<Traits::return_type>());
    }
    _return_type = nefuren::get_type<Traits::return_type>();
    assert(_return_type != nullptr);
    init_argument_types(fun, std::make_index_sequence<Traits::param_count>());
}

// logic
template <typename F, size_t... Is>
inline void nfunction::init_argument_types(F fun, std::index_sequence<Is...>)
{
    using Traits = member_function_traits<F>;
    _argument_types.reserve(sizeof...(Is));
    ((_argument_types.push_back(nefuren::get_type<Traits::template param_type<Is>>()),
      assert(_argument_types[Is] != nullptr)),
     ...);
}

// get
inline const ntype* nfunction::return_type() const
{
    return _return_type;
}

inline const std::vector<ntype*>& nfunction::argument_types() const
{
    return _argument_types;
}

} // namespace ntr