#include "../inc/nregister.h"
#include <iostream>

enum MyEnum
{
    MyEnum1 = 1,
    MyEnum2 = 2,
    MyEnum3 = 3
};

int main(int argc, char* argv[])
{
    ntr::nregister::regist<bool>("bool");
    ntr::nregister::regist<char>("char");
    ntr::nregister::regist<wchar_t>("wchar");
    ntr::nregister::regist<int8_t>("int8");
    ntr::nregister::regist<int16_t>("int16");
    ntr::nregister::regist<int32_t>("int32");
    ntr::nregister::regist<int64_t>("int64");
    ntr::nregister::regist<uint8_t>("uint8");
    ntr::nregister::regist<uint16_t>("uint16");
    ntr::nregister::regist<uint32_t>("uint32");
    ntr::nregister::regist<uint64_t>("uint64");
    ntr::nregister::regist<float>("float");
    ntr::nregister::regist<double>("double");
    ntr::nregister::regist<long double>("longdouble");
    ntr::nregister::regist<MyEnum>("MyEnum")
        .add("MyEnum1", MyEnum1)
        .add("MyEnum2", MyEnum2)
        .add("MyEnum3", MyEnum3);

    std::cout << ntr::nregister::get_type<MyEnum>()->name() << std::endl;
    std::cout << ntr::nregister::get_type("MyEnum")->name() << std::endl;
    std::cout << ntr::nregister::get_type<bool>()->name() << std::endl;
    std::cout << ntr::nregister::get_type("bool")->name() << std::endl;
    
    return 0;
}