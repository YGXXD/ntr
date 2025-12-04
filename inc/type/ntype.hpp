//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#pragma once

#include "../setup.hpp"
#include "../core/nobject.hpp"
#include "../core/nwrapper.hpp"

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
        epointer,
    };

    struct operations
    {
        void (*default_construct)(void*);
        void (*copy_construct)(void*, const void* const);
        void (*move_construct)(void*, void*);
        void (*destruct)(void*);
    };

    ntype(etype kind, uint32_t size, uint32_t align, operations* ops,
          std::string_view name);
    NTR_DELETE_COPY_MOVE_CONSTRUCTORS(ntype)
    ~ntype();

    NTR_INLINE etype kind() const { return _kind; }
    NTR_INLINE bool is_registered() const { return _is_registered; }
    NTR_INLINE uint32_t align() const { return _align; }
    NTR_INLINE uint32_t size() const { return _size; }
    NTR_INLINE const operations* ops() const { return _ops; }
    NTR_INLINE std::string_view name() const { return { _name, _name_size }; }

    NTR_INLINE bool is_unknown() const { return _kind == etype::eunknown; }
    NTR_INLINE bool is_numeric() const { return _kind == etype::enumeric; }
    NTR_INLINE bool is_enum() const { return _kind == etype::eenum; }
    NTR_INLINE bool is_class() const { return _kind == etype::eclass; }
    NTR_INLINE bool is_pointer() const { return _kind == etype::epointer; }

    const class nnumeric* as_numeric() const;
    const class nenum* as_enum() const;
    const class nclass* as_class() const;
    const class npointer* as_pointer() const;

    nobject new_instance() const;
    nobject new_instance(const nwrapper& wrapper) const;
    nobject new_instance_rv(const nwrapper& wrapper) const;
    nobject new_reference(const nwrapper& wrapper) const;

private:
    friend class nregistrar;
    void regist(std::string_view name);

    etype _kind;
    bool _is_registered;
    uint16_t _size;
    uint16_t _align;
    uint16_t _name_size;
    char* _name;
    operations* _ops;
};

} // namespace ntr