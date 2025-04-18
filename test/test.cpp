#include "../inc/nephren.hpp"
#include <iostream>

class MoveObj
{
public:
    MoveObj(int value, int value2) : _value(new int(value)), _value2(value2) {}
    MoveObj(const MoveObj& other) : _value(new int(*other._value)), _value2(other._value2)
    {
    }
    MoveObj(MoveObj&& other) : _value(other._value), _value2(other._value2)
    {
        other._value = nullptr;
    };
    ~MoveObj()
    {
        if (_value != nullptr)
            delete _value;
    }

    int* _value;
    int _value2;
};

void test_inref(const ntr::nwrapper& a)
{
    std::cout << a.ref<float>() << std::endl;
    std::cout << a.cref<float>() << std::endl;
    std::cout << a.rref<float>() << std::endl;
    std::cout << a.data() << std::endl;
}

void test_ref()
{
    const ntr::nwrapper a = 1.f;
    std::cout << a.ref<float>() << std::endl;
    std::cout << a.cref<float>() << std::endl;
    std::cout << a.rref<float>() << std::endl;
    std::cout << a.data() << std::endl;

    const ntr::nwrapper b = 2.f;
    std::cout << b.ref<float>() << std::endl;
    std::cout << b.cref<float>() << std::endl;
    std::cout << b.rref<float>() << std::endl;
    std::cout << b.data() << std::endl;

    const ntr::nwrapper c = 3.f;
    std::cout << c.ref<float>() << std::endl;
    std::cout << c.cref<float>() << std::endl;
    std::cout << c.rref<float>() << std::endl;
    std::cout << c.data() << std::endl;
    test_inref(a);
}

void test_object()
{
    ntr::nobject b = MoveObj(1, 2);
    std::cout << b.data() << std::endl;
    std::cout << b.as<MoveObj>()._value << std::endl;
    std::cout << *b.as<MoveObj>()._value << std::endl;
    ntr::nobject c = b;
    std::cout << c.data() << std::endl;
    std::cout << c.as<MoveObj>()._value << std::endl;
    std::cout << *c.as<MoveObj>()._value << std::endl;
    ntr::nobject d = std::move(b);
    std::cout << d.data() << std::endl;
    std::cout << d.as<MoveObj>()._value << std::endl;
    std::cout << *d.as<MoveObj>()._value << std::endl;

    std::cout << b.data() << std::endl;
    std::cout << b.as<MoveObj>()._value << std::endl;

    ntr::nobject e = 100;
    std::cout << e.data() << std::endl;
    std::cout << e.as<int>() << std::endl;
}