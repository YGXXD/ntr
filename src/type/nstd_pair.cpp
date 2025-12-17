//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "type/nstd_pair.hpp"

namespace ntr
{

std::pair<nobject, nobject> nstd_pair::unpack(const nwrapper& std_pair)
{
    if (!std_pair.type()->is_std_pair())
        throw std::invalid_argument(
            "nstd_pair::unpack : std_pair's type is not std_pair type");
    const nstd_pair* std_pair_type = std_pair.type()->as_std_pair();
    uint32_t first_size = std_pair_type->_first_type->size();
    uint32_t second_align = std_pair_type->_second_type->align();
    uint32_t second_offset = (first_size + second_align - 1) & ~(second_align - 1);
    nobject first = std_pair_type->_first_type->ref_instance(
        nwrapper(std_pair_type->_first_type, std_pair.data()));
    nobject second = std_pair_type->_second_type->ref_instance(
        nwrapper(std_pair_type->_second_type,
                 static_cast<char*>(std_pair.data()) + second_offset));
    return { std::move(first), std::move(second) };
}

nstd_pair::nstd_pair(const ntype* first_type, const ntype* second_type, uint16_t size,
                     uint16_t align, operations* ops)
    : ntype(ntype::etype::estd_pair, size, align, ops), _first_type(first_type),
      _second_type(second_type)
{
}

nstd_pair::~nstd_pair() = default;

} // namespace ntr
