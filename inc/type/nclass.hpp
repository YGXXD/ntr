//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "ntype.hpp"
#include "../core/nobject.hpp"
#include "../field/nfunction.hpp"
#include "../field/nproperty.hpp"

namespace ntr
{

class NTR_API nclass : public ntype
{
public:
    nclass(std::string_view name, uint32_t size, uint32_t align, operations* ops);
    nclass(const nclass&) = delete;
    nclass(nclass&&) = delete;
    nclass& operator=(const nclass&) = delete;
    nclass& operator=(nclass&&) = delete;

    void add_function(std::unique_ptr<nfunction>&& function);
    void add_property(std::unique_ptr<nproperty>&& property);

    void remove(std::string_view name);

    NTR_INLINE auto function_begin() const { return _functions.begin(); }
    NTR_INLINE auto function_end() const { return _functions.end(); }
    NTR_INLINE auto property_begin() const { return _properties.begin(); }
    NTR_INLINE auto property_end() const { return _properties.end(); }
    const nfunction* get_function(std::string_view name) const;
    const nproperty* get_property(std::string_view name) const;
    bool has_function(std::string_view name) const;
    bool has_property(std::string_view name) const;

    nobject call(std::string_view name, const std::vector<nwrapper>& args) const;
    nobject get(std::string_view name, const nwrapper& instance) const;
    void set(std::string_view name, const nwrapper& instance,
             const nwrapper& value) const;

private:
    std::list<std::unique_ptr<nfunction>> _functions;
    std::list<std::unique_ptr<nproperty>> _properties;

    std::unordered_map<std::string_view,
                       std::pair<std::list<std::unique_ptr<nfunction>>::const_iterator,
                                 std::list<std::unique_ptr<nproperty>>::const_iterator>>
        _field_map;
};

} // namespace ntr