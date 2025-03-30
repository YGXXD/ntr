#include "../inc/ntr.h"
#include <iostream>

enum MyEnum
{
    MyEnum1 = 1,
    MyEnum2 = 2,
    MyEnum3 = 3
};

class MyClass
{
    int _value;

    int value() const { return _value; }
    void value(int value) { _value = value; }
};

int main(int argc, char* argv[])
{
    ntr::nephren::regist<bool>("bool");
    ntr::nephren::regist<char>("char");
    ntr::nephren::regist<wchar_t>("wchar");
    ntr::nephren::regist<int8_t>("int8");
    ntr::nephren::regist<int16_t>("int16");
    ntr::nephren::regist<int32_t>("int32");
    ntr::nephren::regist<int64_t>("int64");
    ntr::nephren::regist<uint8_t>("uint8");
    ntr::nephren::regist<uint16_t>("uint16");
    ntr::nephren::regist<uint32_t>("uint32");
    ntr::nephren::regist<uint64_t>("uint64");
    ntr::nephren::regist<float>("float");
    ntr::nephren::regist<double>("double");
    ntr::nephren::regist<long double>("longdouble");
    ntr::nephren::regist<MyEnum>("MyEnum")
        .add("MyEnum1", MyEnum1)
        .add("MyEnum2", MyEnum2)
        .add("MyEnum3", MyEnum3);

    std::cout << ntr::nephren::get_type<bool>()->name() << std::endl;
    std::cout << ntr::nephren::get_type("int8")->name() << std::endl;

    const ntr::nenum* enum_type = ntr::nephren::get_type<MyEnum>()->as_enum();
    std::cout << enum_type->get_eitem(MyEnum::MyEnum1).value() << std::endl;

    return 0;
}