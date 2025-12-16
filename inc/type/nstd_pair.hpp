//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "ntype.hpp"

namespace ntr
{

class NTR_API nstd_pair : public ntype
{
public:
    static std::pair<nobject, nobject> unpack(const nwrapper& std_pair);

    nstd_pair(const ntype* first_type, const ntype* second_type, uint16_t size,
              uint16_t align, operations* ops);
    NTR_DELETE_COPY_MOVE_CONSTRUCTORS(nstd_pair)
    ~nstd_pair();

    NTR_INLINE const ntype* first_type() const { return _first_type; }
    NTR_INLINE const ntype* second_type() const { return _second_type; }

private:
    const ntype* _first_type;
    const ntype* _second_type;
};

} // namespace ntr
