#pragma once

#include "../config.h"

namespace ntr
{

class ntype
{
public:
    enum class etype : uint8_t
    {
        eunknown,
        enumeric,
        eenum,
        eclass,
    };

    template <typename T>
    static constexpr bool is_numeric();

    template <typename T>
    static constexpr bool is_enum();

    template <typename T>
    static constexpr bool is_class();

    template <typename T>
    static constexpr etype to_etype();

    ntype(etype kind, std::string_view name);

    inline etype kind() const { return _kind; }
    inline std::string_view name() const { return _name; }
    inline void set_name(std::string_view name) { _name = name; }
    inline bool is_unknown() const { return _kind == etype::eunknown; }
    inline bool is_numeric() const { return _kind == etype::enumeric; }
    inline bool is_enum() const { return _kind == etype::eenum; }
    inline bool is_class() const { return _kind == etype::eclass; }

    const class nnumeric* as_numeric() const;
    const class nenum* as_enum() const;
    const class nclass* as_class() const;

private:
    etype _kind;
    std::string _name;
};

} // namespace ntr