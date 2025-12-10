//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "ntr_test.hpp"

using namespace ntr;

class sword
{
public:
    sword() {}
    virtual ~sword() {}

    virtual void print_sword() { std::cout << "sword name: " << "sword" << std::endl; }
};

class fairy
{
public:
    fairy() : _name("fairy") {}
    ~fairy() {}

    void print_fairy() { std::cout << "fairy name: " << _name << std::endl; }

private:
    std::string _name;
};

class seniorious : public sword
{
public:
    seniorious() : _name("seniorious") {}
    virtual ~seniorious() override {}

    virtual void print_sword() override
    {
        std::cout << "sword name: " << _name << std::endl;
    }

private:
    std::string _name;
};

class kutori : public fairy, public seniorious
{
public:
    kutori() : height(0.0f), weight(0.0f), _age(0), _value(new double(666.0)) {}
    kutori(const kutori& other)
        : height(other.height), weight(other.weight), _age(other._age),
          _value(new double(*other._value))
    {
    }
    kutori(kutori&& other)
        : height(0.0f), weight(0.0f), _age(other._age), _value(other._value)
    {
        other._value = nullptr;
    }
    virtual ~kutori()
    {
        if (_value)
            delete _value;
    }

    void update_info(float in_height, float in_weight)
    {
        height = in_height;
        weight = in_weight;
    }
    const int& age() const { return _age; }
    void set_age(const int& age) { _age = age; }
    const double* get_value() const { return _value; }

    float height;
    float weight;

private:
    int _age;
    double* _value;
};

int main()
{
    try
    {
        // test type
        NTR_TEST_ASSERT(nephren::get<const kutori>() == nephren::get<kutori>());
        NTR_TEST_ASSERT(nephren::get<volatile kutori>() == nephren::get<kutori>());
        NTR_TEST_ASSERT(nephren::get<volatile const kutori>() == nephren::get<kutori>());
        NTR_TEST_ASSERT(nephren::get<const kutori*>() == nephren::get<kutori*>());
        NTR_TEST_ASSERT(nephren::get<volatile kutori*>() == nephren::get<kutori*>());
        NTR_TEST_ASSERT(nephren::get<volatile const kutori*>() ==
                        nephren::get<kutori*>());
        NTR_TEST_ASSERT(nephren::get<kutori* const>() == nephren::get<kutori*>());
        NTR_TEST_ASSERT(nephren::get<kutori* volatile>() == nephren::get<kutori*>());
        NTR_TEST_ASSERT(nephren::get<kutori* const volatile>() ==
                        nephren::get<kutori*>());
        NTR_TEST_ASSERT(nephren::get<const volatile kutori* volatile const>() ==
                        nephren::get<kutori*>());

        // test type reflection
        nephren::type<sword>("sword").function("print_sword", &sword::print_sword);
        nephren::type<fairy>("fairy").function("print_fairy", &fairy::print_fairy);
        nephren::type<seniorious>("seniorious").base_type<sword>();

        nephren::type<kutori>("kutori")
            .base_type<fairy>()
            .base_type<seniorious>()
            .property("age", &kutori::age, &kutori::set_age)
            .property("height", &kutori::height)
            .property("weight", &kutori::weight)
            .function("update_info", &kutori::update_info)
            .function("get_value", &kutori::get_value);

        const nclass* kutori_type = nephren::get<kutori>();
        const nclass* kutori_type_by_name = nephren::get("kutori")->as_class();
        NTR_TEST_ASSERT(kutori_type == kutori_type_by_name);

        const nfunction* kutori_print_fairy = kutori_type->get_function("print_fairy");
        NTR_TEST_ASSERT(kutori_print_fairy->return_type() ==
                        nregistrar::get_type<void>());
        const nfunction* kutori_print_sword = kutori_type->get_function("print_sword");
        NTR_TEST_ASSERT(kutori_print_sword->return_type() ==
                        nregistrar::get_type<void>());

        const nfunction* kutori_update_info = kutori_type->get_function("update_info");
        NTR_TEST_ASSERT(kutori_update_info->return_type() ==
                        nregistrar::get_type<void>());
        NTR_TEST_ASSERT(kutori_update_info->argument_types().size() == 3);
        NTR_TEST_ASSERT(kutori_update_info->argument_types()[0] ==
                        nregistrar::get_type<kutori>());
        NTR_TEST_ASSERT(kutori_update_info->argument_types()[1] ==
                        nregistrar::get_type<float>());
        NTR_TEST_ASSERT(kutori_update_info->argument_types()[2] ==
                        nregistrar::get_type<float>());

        const nfunction* kutori_get_value = kutori_type->get_function("get_value");
        auto okoko = nregistrar::get_type<double*>();
        NTR_TEST_ASSERT(kutori_get_value->return_type() ==
                        nregistrar::get_type<const double*>());
        NTR_TEST_ASSERT(kutori_get_value->argument_types().size() == 1);
        NTR_TEST_ASSERT(kutori_get_value->argument_types()[0] ==
                        nregistrar::get_type<kutori>());

        const nproperty* kutori_age = kutori_type->get_property("age");
        NTR_TEST_ASSERT(kutori_age->parent_type() == nregistrar::get_type<kutori>());
        NTR_TEST_ASSERT(kutori_age->property_type() == nregistrar::get_type<int>());

        const nproperty* kutori_height = kutori_type->get_property("height");
        NTR_TEST_ASSERT(kutori_height->parent_type() == nregistrar::get_type<kutori>());
        NTR_TEST_ASSERT(kutori_height->property_type() == nregistrar::get_type<float>());

        const nproperty* kutori_weight = kutori_type->get_property("weight");
        NTR_TEST_ASSERT(kutori_weight->parent_type() == nregistrar::get_type<kutori>());
        NTR_TEST_ASSERT(kutori_weight->property_type() == nregistrar::get_type<float>());

        nobject kutori_obj = kutori_type->new_instance();
        nwrapper kutori_wrapper = kutori_obj.wrapper();
        nwrapper fairy_wrapper =
            kutori_wrapper.cast_to(kutori_print_fairy->argument_types()[0]);
        nwrapper sword_wrapper =
            kutori_wrapper.cast_to(kutori_print_sword->argument_types()[0]);
        kutori_type->call("print_fairy", { fairy_wrapper });
        kutori_type->call("print_sword", { sword_wrapper });
        kutori_type->call("update_info", { kutori_wrapper, 160.0f, 45.0f });
        kutori_type->set("age", kutori_wrapper, 15);

        nobject height = kutori_type_by_name->get("height", kutori_wrapper);
        NTR_TEST_ASSERT(height.type()->is_numeric());
        nobject weight = kutori_type_by_name->get("weight", kutori_wrapper);
        NTR_TEST_ASSERT(weight.type()->is_numeric());
        nobject age = kutori_type_by_name->get("age", kutori_wrapper);
        NTR_TEST_ASSERT(age.type()->is_numeric());
        nobject value = kutori_type_by_name->call("get_value", { kutori_wrapper });
        NTR_TEST_ASSERT(value.type()->is_pointer());
        std::cout << "kutori's height is: " << nnumeric::get_value(height) << "cm"
                  << std::endl;
        std::cout << "kutori's weight is: " << nnumeric::get_value(weight) << "kg"
                  << std::endl;
        std::cout << "kutori's age is: " << nnumeric::get_value(age) << " years old"
                  << std::endl;
        std::cout << "kutori's value dereference is: "
                  << value.type()->as_pointer()->dereference(value.wrapper()).as<double>()
                  << std::endl;
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return 1;
    }
}
