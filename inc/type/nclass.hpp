//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "ntype.hpp"
#include "../tool/ntable.hpp"
#include "../core/nobject.hpp"

namespace ntr
{

class NTR_API nclass : public ntype
{
public:
    nclass(uint32_t size, uint32_t align, operations* ops, std::string_view name);
    NTR_DELETE_COPY_MOVE_CONSTRUCTORS(nclass)
    ~nclass();

    void add_function(std::unique_ptr<class nfunction>&& function);
    void add_property(std::unique_ptr<class nproperty>&& property);
    void add_base_type(const nclass* _base_type, ptrdiff_t offset);
    void remove_field(std::string_view name);

    NTR_INLINE const auto& functions() const { return _functions; }
    NTR_INLINE const auto& propertys() const { return _properties; }
    const nfunction* get_function(std::string_view name) const;
    const nproperty* get_property(std::string_view name) const;
    void* cast_to(const nclass* type, void* pointer) const;
    bool has_base_type(const nclass* type) const;
    bool has_function(std::string_view name) const;
    bool has_property(std::string_view name) const;

    nobject call(std::string_view name, const std::vector<nwrapper>& args) const;
    nobject get(std::string_view name, const nwrapper& instance) const;
    void set(std::string_view name, const nwrapper& instance,
             const nwrapper& value) const;

private:
    bool check_base_type(const nclass* type, ptrdiff_t* out_offset) const;

    std::vector<std::pair<const nclass*, ptrdiff_t>> _base_type_pairs;
    std::vector<std::unique_ptr<nfunction>> _functions;
    std::vector<std::unique_ptr<nproperty>> _properties;
    nhash_map<std::string_view, std::pair<nfunction*, nproperty*>> _field_map;
};

} // namespace ntr