#pragma once

#include "../config.h"
#include "singleton.h"

namespace ntr
{

class nobject
{
public:
    template <typename T>
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

private:
    struct nobject_data_operations
    {
        std::function<void*(const void*)> copy;
        std::function<void*(void*)> move;
        std::function<void(void*)> release;
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
                ops.copy = [](void* other_data) -> void*
                {
                    return new T(*static_cast<const T*>(other_data));
                };
            }
            if constexpr (std::is_move_constructible_v<T>)
            {
                ops.move = [](void* other_data) -> void*
                {
                    return new T(std::move(*static_cast<T*>(other_data)));
                };
            }
            if constexpr (std::is_destructible_v<T>)
            {
                ops.release = [](void* self_data) -> void
                {
                    delete static_cast<T*>(self_data);
                };
            }
        }
    };

    const ntype* _type;
    const nobject_data_operations* _data_ops;
    union
    {
        char _small_data[8];
        void* _large_data;
    };
};

} // namespace ntr