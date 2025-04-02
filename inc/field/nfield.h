#pragma once

#include "../config.h"

namespace ntr
{

class nfield
{
public:
    enum class efield
    {
        eeitem,
        eproperty,
        efunction
    };

    nfield(const class ntype* parent_type, efield kind, std::string_view name);

    inline const ntype* parent_type() const { return _parent_type; }
    inline efield kind() const { return _kind; }
    inline std::string_view name() const { return _name; }

private:
    const ntype* _parent_type;
    efield _kind;
    std::string _name;
};

} // namespace ntr
