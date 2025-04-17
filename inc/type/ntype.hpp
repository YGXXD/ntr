#pragma once

#include "../setup.hpp"

namespace ntr
{

class NTR_API ntype
{
public:
    enum class etype : uint8_t
    {
        eunknown,
        enumeric,
        eenum,
        eclass,
    };

    ntype(etype kind, std::string_view name);

    NTR_INLINE etype kind() const { return _kind; }
    NTR_INLINE std::string_view name() const { return _name; }
    NTR_INLINE void set_name(std::string_view name) { _name = name; }
    NTR_INLINE bool is_unknown() const { return _kind == etype::eunknown; }
    NTR_INLINE bool is_numeric() const { return _kind == etype::enumeric; }
    NTR_INLINE bool is_enum() const { return _kind == etype::eenum; }
    NTR_INLINE bool is_class() const { return _kind == etype::eclass; }

    const class nnumeric* as_numeric() const;
    const class nenum* as_enum() const;
    const class nclass* as_class() const;

private:
    etype _kind;
    std::string _name;
};

} // namespace ntr