#include "nephren.hpp"
#include <iostream>

static int nephren_register_numeric = []() -> int
{
    ntr::nephren::type<int8_t>("int8");
    ntr::nephren::type<int16_t>("int16");
    ntr::nephren::type<int32_t>("int32");
    ntr::nephren::type<int64_t>("int64");
    ntr::nephren::type<uint8_t>("uint8");
    ntr::nephren::type<uint16_t>("uint16");
    ntr::nephren::type<uint32_t>("uint32");
    ntr::nephren::type<uint64_t>("uint64");
    ntr::nephren::type<float>("float");
    ntr::nephren::type<double>("double");

    ntr::nephren::type<int8_t*>("int8*");
    ntr::nephren::type<int16_t*>("int16*");
    ntr::nephren::type<int32_t*>("int32*");
    ntr::nephren::type<int64_t*>("int64*");
    ntr::nephren::type<uint8_t*>("uint8*");
    ntr::nephren::type<uint16_t*>("uint16*");
    ntr::nephren::type<uint32_t*>("uint32*");
    ntr::nephren::type<uint64_t*>("uint64*");
    ntr::nephren::type<float*>("float*");
    ntr::nephren::type<double*>("double*");
    return 0;
}();

enum class MyEnum
{
    MyEnum1 = 1,
    MyEnum2 = 2,
    MyEnum3 = 3
};

class MyFather
{
public:
    int father_value = 6;
};

class MyChild : public MyFather
{
public:
    int child_value = 2;
};

class MyClass
{
public:
    const int& value() const { return _value; }
    void value(const int& value) { _value = value; }

    static void print(MyFather& x)
    {
        std::cout << "MyClass" << x.father_value << std::endl;
    }

    double& print_member(double& x)
    {
        x -= 2.5;
        std::cout << "MyClass" << x << std::endl;
        return x;
    }

    double float_value;

private:
    int _value;
};

static void xxxxx(MyChild& x)
{
    std::cout << "MyClass" << x.father_value << std::endl;
}

int main(int argc, char* argv[])
{
    ntr::nephren::type<MyEnum>("MyEnum")
        .item("MyEnum1", MyEnum::MyEnum1)
        .item("MyEnum2", MyEnum::MyEnum2)
        .item("MyEnum3", MyEnum::MyEnum3);

    ntr::nephren::type<MyClass>("MyClass")
        .function("print", &MyClass::print)
        .property("float_value", &MyClass::float_value)
        .property("value", &MyClass::value, &MyClass::value)
        .function("print_member", &MyClass::print_member);

    std::cout << ntr::nephren::get<uint64_t>()->name() << std::endl;
    std::cout << static_cast<int>(ntr::nephren::get("int8")->as_numeric()->numeric_kind())
              << std::endl;

    const ntr::nenum* enum_type = ntr::nephren::get("MyEnum")->as_enum();
    std::cout << enum_type->get_eitem(static_cast<long>(MyEnum::MyEnum3))->value()
              << std::endl;

    const ntr::nclass* class_type = ntr::nephren::get<MyClass>()->as_class();
    std::cout << class_type->get_property("float_value")->property_type()->name()
              << std::endl;
    std::cout << class_type->get_function("print")->name() << std::endl;

    MyClass my_class;
    my_class.value(10);
    my_class.float_value = 0;

    const ntr::nproperty* property = class_type->get_property("value");
    std::cout << property->property_type()->name() << std::endl;
    std::cout << property->get(my_class).as<int>() << std::endl;
    property->set(my_class, 20);
    std::cout << property->get(my_class).as<int>() << std::endl;

    property = class_type->get_property("float_value");
    std::cout << property->property_type()->name() << std::endl;
    std::cout << property->get(my_class).as<double>() << std::endl;
    property->set(my_class, double(20));
    std::cout << property->get(my_class).as<double>() << std::endl;

    const ntr::nfunction* function = class_type->get_function("print");
    std::cout << function->name() << std::endl;
    std::cout << function->return_type()->name() << std::endl;
    std::cout << function->argument_types().size() << std::endl;

    std::cout << function->invoke({ static_cast<MyFather&&>(MyChild()) }).type()->name()
              << std::endl;

    function = class_type->get_function("print_member");
    std::cout << function->name() << std::endl;
    std::cout << function->return_type()->name() << std::endl;
    std::cout << function->argument_types().size() << std::endl;
    double x = 19.9;
    std::vector<ntr::nwrapper> args { my_class, x };
    function->invoke(args);
    auto result = function->invoke(args);
    result.as<double>() = 10;
    std::cout << result.as<double>() << std::endl;
    std::cout << x << std::endl;

    ntr::nwrapper ref = ntr::nwrapper(100);
    std::cout << ref.cref<int>() << std::endl;
    std::unique_ptr<int> a = std::make_unique<int>(100);
    a = std::make_unique<int>(200);

    ntr::nobject obj = ntr::nobject::make_obtain<int>(100);

    ntr::nnumeric::set_value(obj, 205.2);
    std::cout << ntr::nnumeric::get_value(obj) << std::endl;

    // long lll = 100;
    // MyEnum eee = static_cast<MyEnum>(lll);
    // std::cout << sizeof(ntr::nobject) << std::endl;
    // ntr::nobject obj = ntr::nobject(MyChild());
    // ntr::nobject obj2 = obj.clone();
    // ntr::nobject obj3 = obj.steal();

    std::cout << ntr::nephren::get<int8_t*>()->name() << std::endl;
    std::cout << ntr::nephren::get<int16_t*>()->name() << std::endl;

    uint16_t u16 = 100;
    ntr::nobject obj2 = ntr::nephren::get<uint16_t*>()->new_object();
    ntr::npointer::set_value(obj2, &u16);
    std::cout << ntr::npointer::get_target(obj2).as<uint16_t>() << std::endl;

    std::cout << std::is_copy_constructible_v<int[10]> << std::endl;

    return 0;
}