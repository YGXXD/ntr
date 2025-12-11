//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "ntype.hpp"
#include "../util/nvector.hpp"

namespace ntr
{

class NTR_API ncontainer : public ntype
{
public:
    struct operations
    {
        void (*put)(void*, void*);
        void (*clear)(void*);
        uint32_t (*size)(void*);
        nobject (*begin)(void*);
        void (*next)(void*);
        nobject (*end)(void*);
        bool (*equal)(void*, void*);
        nobject (*get)(void*);
    };

    ncontainer(const ntype* iterator_type, const ntype* element_type,
               operations* container_ops, uint32_t size, uint32_t align,
               ntype::operations* ops, std::string_view name);
    NTR_DELETE_COPY_MOVE_CONSTRUCTORS(ncontainer)
    ~ncontainer();

    void puts(const nwrapper& container, const nvector<nwrapper>& elements) const;
    void clear(const nwrapper& container) const;
    uint32_t size(const nwrapper& container) const;
    nobject begin(const nwrapper& container) const;
    void next(const nwrapper& iterator) const;
    nobject end(const nwrapper& container) const;
    bool equal(const nwrapper& iterator1, const nwrapper& iterator2) const;
    nobject get(const nwrapper& iterator) const;
    NTR_INLINE const ntype* iterator_type() const { return _iterator_type; }
    NTR_INLINE const ntype* element_type() const { return _element_type; }

private:
    const ntype* _iterator_type;
    const ntype* _element_type;
    operations* _container_ops;
};

} // namespace ntr
