#pragma once

#include "../setup.hpp"

namespace ntr
{

class NTR_API nobject
{
public:
    template <typename T,
              typename = std::enable_if_t<!std::is_same_v<std::decay_t<T>, nobject>>>
    nobject(T&& other);
    nobject(const nobject& other);
    nobject(nobject&& other);
    nobject& operator=(const nobject& other);
    nobject& operator=(nobject&& other);
    ~nobject();

    template <typename T>
    NTR_INLINE T& as();
    template <typename T>
    NTR_INLINE const T& as() const;

    NTR_INLINE const class ntype* type() const { return _type; }
    NTR_INLINE void* data() const { return _large_data; }

private:
    constexpr static size_t small_data_size = 16;

    struct nobject_data_operations
    {
        std::function<void(void*&, void* const&)> copy;
        std::function<void(void*&, void*&)> move;
        std::function<void(void*&)> release;
    };

    template <typename T>
    struct nobject_data_ops_traits
    {
    private:
        nobject_data_ops_traits();

    public:
        NTR_SINGLETON_IMPL(nobject_data_ops_traits<T>)
        nobject_data_operations ops;
    };

    const ntype* _type;
    const nobject_data_operations* _data_ops;
    union
    {
        char _small_data[small_data_size];
        void* _large_data;
    };
};

} // namespace ntr