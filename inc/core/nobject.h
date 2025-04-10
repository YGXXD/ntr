#pragma once

#include "../config.h"
#include "singleton.h"

namespace ntr
{

class nobject
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
    T& as();
    template <typename T>
    const T& as() const;

    inline const class ntype* type() const { return _type; }
    inline void* data() const { return _large_data; }

private:
    constexpr static size_t small_data_size = 8;

    struct nobject_data_operations
    {
        std::function<void(void*&, void* const&)> copy;
        std::function<void(void*&, void*&)> move;
        std::function<void(void*&)> release;
    };

    template <typename T>
    struct nobject_data_ops_traits : singleton<nobject_data_ops_traits<T>>
    {
        template <typename U>
        friend class singleton;

        nobject_data_operations ops;

    private:
        nobject_data_ops_traits()
        {
            if constexpr (std::is_copy_constructible_v<T>)
            {
                ops.copy = [](void*& self_data, void* const& other_data) -> void
                {
                    if constexpr (sizeof(T) <= small_data_size)
                        new (&self_data) T(*reinterpret_cast<const T*>(&other_data));
                    else
                        self_data = new T(*reinterpret_cast<const T*>(other_data));
                };
            }
            if constexpr (std::is_move_constructible_v<T>)
            {
                ops.move = [](void*& self_data, void*& other_data) -> void
                {
                    if constexpr (sizeof(T) <= small_data_size)
                        new (&self_data) T(std::move(*reinterpret_cast<T*>(&other_data)));
                    else
                        self_data = new T(std::move(*reinterpret_cast<T*>(other_data)));
                };
            }
            if constexpr (std::is_destructible_v<T>)
            {
                ops.release = [](void*& self_data) -> void
                {
                    if constexpr (sizeof(T) <= small_data_size)
                        reinterpret_cast<T*>(&self_data)->~T();
                    else
                        delete reinterpret_cast<T*>(self_data);
                };
            }
        }
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