#include "core/nwrapper.hpp"
#include "implement.hpp"

namespace ntr
{

nwrapper::nwrapper(const ntype* type, const void* data)
    : _type(type), _pdata(const_cast<void*>(data))
{
    if (type == nullptr)
        throw std::invalid_argument("nwrapper::nwrapper : type is nullptr");
    if (data == nullptr)
        throw std::invalid_argument("nwrapper::nwrapper : data is nullptr");
}

} // namespace ntr
