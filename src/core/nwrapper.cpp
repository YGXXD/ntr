#include "../../inc/core/nwrapper.hpp"

namespace ntr
{

nwrapper::nwrapper(const ntype* type, void* data) : _type(type), _pdata(data)
{
    if (type == nullptr)
        throw std::invalid_argument("nwrapper::nwrapper : type is nullptr");
    if (data == nullptr)
        throw std::invalid_argument("nwrapper::nwrapper : data is nullptr");
}

} // namespace ntr
