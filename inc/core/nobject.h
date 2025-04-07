#pragma once

#include "../config.h"
#include "singleton.h"

namespace ntr
{

class nobject
{
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
    struct nobject_operations
    {
        std::function<nobject(nobject&, const nobject&)> copy;
        std::function<nobject(nobject&, nobject&&)> move;
        std::function<void(nobject&)> release;
    };

    template <typename T>
    struct nobject_ops_traits : singleton<nobject_ops_traits<T>>
    {
        template <typename U>
        friend class nobject_ops_traits;

        nobject_operations ops;

    private:
        nobject_ops_traits()
        {
            if constexpr (std::is_copy_constructible_v<T>)
            {
                ops.copy = [](nobject& self, const nobject& other) -> nobject
                {
                    self._type = other._type;
                    self._pdata = new T(*static_cast<const T*>(other._pdata));
                    self._ops = other._ops;
                };
            }
            if constexpr (std::is_move_constructible_v<T>)
            {
                ops.move = [](nobject& self, nobject&& other) -> nobject
                {
                    self._type = other._type;
                    self._pdata = new T(std::move(*static_cast<T*>(other._pdata)));
                    self._ops = other._ops;
                };
            }
            if constexpr (std::is_destructible_v<T>)
            {
                ops.release = [](nobject& other)
                {
                    delete static_cast<T*>(other._pdata);
                };
            }
        }
    };

    const ntype* _type;
    const nobject_operations* _ops;
    union
    {
        char _data[8];
        void* _pdata;
    };
};

} // namespace ntr