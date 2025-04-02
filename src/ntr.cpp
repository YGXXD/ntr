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
public:
    int value() const { return _value; }
    void value(const int& value) { _value = value; }

    void print() const { std::cout << "MyClass" << std::endl; }

    double float_value;

private:
    int _value;
};

int main(int argc, char* argv[])
{
    ntr::nephren::numeric_<int8_t>("int8");
    ntr::nephren::numeric_<int16_t>("int16");
    ntr::nephren::numeric_<int32_t>("int32");
    ntr::nephren::numeric_<int64_t>("int64");
    ntr::nephren::numeric_<uint8_t>("uint8");
    ntr::nephren::numeric_<uint16_t>("uint16");
    ntr::nephren::numeric_<uint32_t>("uint32");
    ntr::nephren::numeric_<uint64_t>("uint64");
    ntr::nephren::numeric_<float>("float");
    ntr::nephren::numeric_<double>("double");

    ntr::nephren::enum_<MyEnum>("MyEnum")
        .item("MyEnum1", MyEnum1)
        .item("MyEnum2", MyEnum2)
        .item("MyEnum3", MyEnum3);

    ntr::nephren::class_<MyClass>("MyClass")
        .function("print", &MyClass::print)
        .property("float_value", &MyClass::float_value)
        .property("value", &MyClass::value, &MyClass::value);

    std::cout << ntr::nephren::get_type<uint64_t>()->name() << std::endl;
    std::cout << ntr::nephren::get_type("int8")->name() << std::endl;

    const ntr::nenum* enum_type = ntr::nephren::get_type("MyEnum")->as_enum();
    std::cout << enum_type->get_eitem(MyEnum::MyEnum3)->value() << std::endl;

    const ntr::nclass* class_type = ntr::nephren::get_type<MyClass>()->as_class();
    std::cout << class_type->get_property("float_value")->property_type()->name()
              << std::endl;
    std::cout << class_type->get_function("print")->name() << std::endl;

    return 0;
}