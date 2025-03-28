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
    ntr::nregister::regist<MyEnum>("MyEnum")
        .add("MyEnum1", MyEnum1)
        .add("MyEnum2", MyEnum2)
        .add("MyEnum3", MyEnum3);
    const ntr::ntype* type = ntr::nregister::get_type<MyEnum>();
    std::cout << type->as_enum()->get_name(MyEnum::MyEnum2) << std::endl;
    
    return 0;
}