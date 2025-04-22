#pragma once

#include "ntype.hpp"

namespace ntr
{

class NTR_API ncontainer : public ntype
{
public:
    enum class econtainer : uint8_t
    {
        earray,
        emap,
    };

    ncontainer(std::string_view name, uint32_t size, operations* ops);

    
};

} // namespace ntr