#include "../inc/nephren.hpp"
#include <iostream>
#include <any>

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
    int value() const { return _value; }
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
        .item("MyEnum1", MyEnum::MyEnum1)
        .item("MyEnum2", MyEnum::MyEnum2)
        .item("MyEnum3", MyEnum::MyEnum3);

    ntr::nephren::class_<MyClass>("MyClass")
        .function("print", &MyClass::print)
        .property("float_value", &MyClass::float_value)
        .property("value", &MyClass::value, &MyClass::value)
        .function("print_member", &MyClass::print_member);

    std::cout << ntr::nephren::get_type<uint64_t>()->name() << std::endl;
    std::cout << ntr::nephren::get_type("int8")->name() << std::endl;

    const ntr::nenum* enum_type = ntr::nephren::get_type("MyEnum")->as_enum();
    std::cout << enum_type->get_eitem(static_cast<long>(MyEnum::MyEnum3))->value()
              << std::endl;

    const ntr::nclass* class_type = ntr::nephren::get_type<MyClass>()->as_class();
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

    function->invoke({ static_cast<MyFather&&>(MyChild()) });

    function = class_type->get_function("print_member");
    std::cout << function->name() << std::endl;
    std::cout << function->return_type() << std::endl;
    std::cout << function->argument_types().size() << std::endl;
    double x = 19.9;
    std::vector<ntr::nreference> args { my_class, x };
    function->invoke(args);
    auto result = function->invoke(args);
    result.as<ntr::nreference>().ref<double>() = 10;
    std::cout << result.as<ntr::nreference>().cref<double>() << std::endl;
    std::cout << x << std::endl;

    ntr::nreference ref = ntr::nreference(100);
    std::cout << ref.cref<int>() << std::endl;

    long lll = 100;
    MyEnum eee = static_cast<MyEnum>(lll);
    // std::cout << sizeof(void) << std::endl;

    // MyChild lll = MyChild();
    // std::any a = &lll;
    // std::cout << std::any_cast<MyChild*>(a) << std::endl;
    // std::shared_ptr<MyChild> ppp = std::make_shared<MyChild>();
    // MyChild* lllp = &lll;
    // const MyChild& fffp = lll;

    return 0;
}