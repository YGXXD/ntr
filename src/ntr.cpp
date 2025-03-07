#include "../ntr/ntr.h"
#include <iostream>

class MyClass
{
public:
    MyClass(int i, float f, MyClass* p) : m_int(i), m_float(f), m_point(p) {}

    void print() const
    {
        std::cout << "m_int: " << m_int << ", m_float: " << m_float << ", m_point: " << m_point << std::endl;
    }

    void multiply(float factor)
    {
        m_int *= factor;
        m_float *= factor;
    }

    using ptr = MyClass*;

    void set_point(const ptr& p) noexcept { m_point = p; }

    ptr get_point() const noexcept { return m_point; }

    int m_int;
    float m_float;

private:
    MyClass* m_point;
};

namespace ntr
{

template <>
struct nclass<MyClass>
{
    static inline constexpr auto functions =
        std::make_tuple(nfunction { &MyClass::print }, nfunction { &MyClass::multiply });

    static inline auto propertys = std::make_tuple(nproperty(&MyClass::m_int), nproperty(&MyClass::m_float),
                                                   nproperty(&MyClass::get_point, &MyClass::set_point));
};

} // namespace ntr

int main(int argc, char* argv[])
{
    MyClass obj(1, 2.0f, nullptr);

    auto functions = ntr::nclass<MyClass>::functions;
    auto propertys = ntr::nclass<MyClass>::propertys;

    std::get<0>(functions)(&obj);
    std::get<1>(functions)(&obj, 2.0f);
    std::get<0>(functions)(&obj);

    std::get<2>(propertys).set(&obj, &obj);
    std::cout << std::get<2>(propertys).get(&obj) << std::endl;

    return 0;
}