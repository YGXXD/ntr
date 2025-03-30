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
    ntr::nefuren::regist<bool>("bool");
    ntr::nefuren::regist<char>("char");
    ntr::nefuren::regist<wchar_t>("wchar");
    ntr::nefuren::regist<int8_t>("int8");
    ntr::nefuren::regist<int16_t>("int16");
    ntr::nefuren::regist<int32_t>("int32");
    ntr::nefuren::regist<int64_t>("int64");
    ntr::nefuren::regist<uint8_t>("uint8");
    ntr::nefuren::regist<uint16_t>("uint16");
    ntr::nefuren::regist<uint32_t>("uint32");
    ntr::nefuren::regist<uint64_t>("uint64");
    ntr::nefuren::regist<float>("float");
    ntr::nefuren::regist<double>("double");
    ntr::nefuren::regist<long double>("longdouble");
    ntr::nefuren::regist<MyEnum>("MyEnum")
        .add("MyEnum1", MyEnum1)
        .add("MyEnum2", MyEnum2)
        .add("MyEnum3", MyEnum3);

    std::cout << ntr::nefuren::get_type<bool>()->name() << std::endl;
    std::cout << ntr::nefuren::get_type("int8")->name() << std::endl;

    const ntr::nenum* enum_type = ntr::nefuren::get_type<MyEnum>()->as_enum();
    std::cout << enum_type->get_eitem(MyEnum::MyEnum1).value() << std::endl;

    return 0;
}