#include "../../inc/core/nwrapper.hpp"

namespace ntr
{

nwrapper::nwrapper(const ntype* type, void* data) : _type(type), _pdata(data)
{
    if (type == nullptr)
        throw std::runtime_error("nwrapper::nwrapper : type is nullptr");
    if (data == nullptr)
        throw std::runtime_error("nwrapper::nwrapper : data is nullptr");
}

} // namespace ntr
