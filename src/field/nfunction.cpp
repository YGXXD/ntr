#include "field/nfunction.hpp"
#include "implement.hpp"

namespace ntr
{

nfunction::nfunction(const ntype* parent_type, std::string_view name)
    : nfield(parent_type, efield::eproperty, name)
{
    if (parent_type->kind() != ntype::etype::eclass)
        throw std::invalid_argument(
            "nfunction::nfunction : parent type is not class type");
}

nobject nfunction::invoke(const std::vector<nwrapper>& args) const
{
    if (args.size() != _argument_types.size())
        throw std::invalid_argument("nfunction::invoke : argument size is wrong, need " +
                                    std::to_string(_argument_types.size()) +
                                    " arguments, but got " + std::to_string(args.size()));
    return _function(args);
}

const nclass* nfunction::class_type() const
{
    return static_cast<const nclass*>(parent_type());
}

} // namespace ntr
