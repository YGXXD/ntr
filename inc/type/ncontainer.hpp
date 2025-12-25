//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "ntype.hpp"
#include "../util/ntemplate_list.hpp"
#include "../util/nvector.hpp"
#include "../util/nhash_map.hpp"
#include "../util/nhash_set.hpp"

#include <functional>

namespace ntr
{

class NTR_API ncontainer : public ntype
{
public:
    struct operations
    {
        void (*put)(void*, void*);
        void (*for_each)(void*, void*);
        void (*clear)(void*);
        uint32_t (*size)(void*);
    };

    using list_templates = ntemplate_list<nvector, nhash_set>;
    using map_templates = ntemplate_list<nhash_map>;

    ncontainer(const ntype* key_type, const ntype* value_type, operations* container_ops,
               uint16_t size, uint16_t align, ntype::operations* ops);
    NTR_DELETE_COPY_MOVE_CONSTRUCTORS(ncontainer)
    ~ncontainer();

    // list container
    void put(const nwrapper& container, const nwrapper& value) const;
    void for_each(const nwrapper& container,
                  const std::function<void(nobject&&)>& callback) const;
    // map container
    void put(const nwrapper& container, const nwrapper& key, const nwrapper& value) const;
    void for_each(const nwrapper& container,
                  const std::function<void(nobject&&, nobject&&)>& callback) const;
    // common
    void clear(const nwrapper& container) const;
    uint32_t size(const nwrapper& container) const;
    NTR_INLINE bool is_list() const { return !is_map(); }
    NTR_INLINE bool is_map() const { return _key_type; }
    NTR_INLINE const ntype* key_type() const { return _key_type; }
    NTR_INLINE const ntype* value_type() const { return _value_type; }

private:
    const ntype* _key_type;
    const ntype* _value_type;
    operations* _container_ops;
};

} // namespace ntr
