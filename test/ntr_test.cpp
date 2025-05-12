#include "nephren.hpp"
#include <iostream>

#define NTR_TEST_ASSERT(condition)                                    \
    if (!(condition))                                                 \
    {                                                                 \
        std::cerr << "Test failed at line " << __LINE__ << std::endl; \
        return 1;                                                     \
    }

using namespace ntr;

class kutori
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
    ~kutori()
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
        // test nobject
        {
            int integer = 2048;
            nobject obj = nobject::make_obtain(integer);
            obj.as<int>() = 1024;
            NTR_TEST_ASSERT(obj.type() == nregistrar::get_type<int>());
            NTR_TEST_ASSERT(obj.kind() == nobject::eobject::eobtain);
            NTR_TEST_ASSERT(obj.is_valid());
            NTR_TEST_ASSERT(obj.as<int>() != integer);

            nobject obj_new = std::move(obj);
            obj_new.as<int>() = 2048;
            NTR_TEST_ASSERT(!obj.is_valid());
            NTR_TEST_ASSERT(obj_new.is_valid());
            NTR_TEST_ASSERT(obj_new.kind() == nobject::eobject::eobtain);
            NTR_TEST_ASSERT(obj_new.as<int>() == integer);

            obj = nobject::make_ref(integer);
            obj.as<int>() = 1024;
            NTR_TEST_ASSERT(obj.type() == nregistrar::get_type<int>());
            NTR_TEST_ASSERT(obj.kind() == nobject::eobject::eref);
            NTR_TEST_ASSERT(obj.is_valid());
            NTR_TEST_ASSERT(obj.as<int>() == integer);

            obj_new = std::move(obj);
            obj_new.as<int>() = 2048;
            NTR_TEST_ASSERT(obj.is_valid());
            NTR_TEST_ASSERT(obj_new.is_valid());
            NTR_TEST_ASSERT(obj_new.as<int>() == obj.as<int>());
            NTR_TEST_ASSERT(obj.as<int>() == integer);

            kutori s_kutori {};
            nobject kutori_obj = nobject::make_obtain(std::move(s_kutori));
            NTR_TEST_ASSERT(s_kutori.get_value() == nullptr);
            NTR_TEST_ASSERT(kutori_obj.type() == nregistrar::get_type<kutori>());
            NTR_TEST_ASSERT(kutori_obj.kind() == nobject::eobject::eobtain);
            NTR_TEST_ASSERT(kutori_obj.is_valid());
            NTR_TEST_ASSERT(kutori_obj.as<kutori>().get_value() != nullptr);

            nobject kutori_obj_clone = kutori_obj.clone();
            NTR_TEST_ASSERT(kutori_obj_clone.type() == nregistrar::get_type<kutori>());
            NTR_TEST_ASSERT(kutori_obj_clone.kind() == nobject::eobject::eobtain);
            NTR_TEST_ASSERT(kutori_obj_clone.is_valid());
            NTR_TEST_ASSERT(kutori_obj_clone.as<kutori>().get_value() != nullptr);
            // check data is not moved
            NTR_TEST_ASSERT(kutori_obj.type() == nregistrar::get_type<kutori>());
            NTR_TEST_ASSERT(kutori_obj.kind() == nobject::eobject::eobtain);
            NTR_TEST_ASSERT(kutori_obj.is_valid());
            NTR_TEST_ASSERT(kutori_obj.as<kutori>().get_value() != nullptr);

            nobject kutori_obj_steal = kutori_obj.steal();
            NTR_TEST_ASSERT(kutori_obj_steal.type() == nregistrar::get_type<kutori>());
            NTR_TEST_ASSERT(kutori_obj_steal.kind() == nobject::eobject::eobtain);
            NTR_TEST_ASSERT(kutori_obj_steal.is_valid());
            NTR_TEST_ASSERT(kutori_obj_steal.as<kutori>().get_value() != nullptr);
            // check data is moved
            NTR_TEST_ASSERT(kutori_obj.type() == nregistrar::get_type<kutori>());
            NTR_TEST_ASSERT(kutori_obj.kind() == nobject::eobject::eobtain);
            NTR_TEST_ASSERT(kutori_obj.is_valid());
            NTR_TEST_ASSERT(kutori_obj.as<kutori>().get_value() == nullptr);
        }

        // test kutori type
        {
            nephren::type<kutori>("kutori")
                .property("age", &kutori::age, &kutori::set_age)
                .property("height", &kutori::height)
                .property("weight", &kutori::weight)
                .function("update_info", &kutori::update_info)
                .function("get_value", &kutori::get_value);

            const nclass* kutori_type = nephren::get<kutori>();
            const nclass* kutori_type_by_name = nephren::get("kutori")->as_class();
            NTR_TEST_ASSERT(kutori_type == kutori_type_by_name);

            const nfunction* kutori_update_info =
                kutori_type->get_function("update_info");
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
            NTR_TEST_ASSERT(kutori_height->parent_type() ==
                            nregistrar::get_type<kutori>());
            NTR_TEST_ASSERT(kutori_height->property_type() ==
                            nregistrar::get_type<float>());

            const nproperty* kutori_weight = kutori_type->get_property("weight");
            NTR_TEST_ASSERT(kutori_weight->parent_type() ==
                            nregistrar::get_type<kutori>());
            NTR_TEST_ASSERT(kutori_weight->property_type() ==
                            nregistrar::get_type<float>());

            nobject kutori_obj = kutori_type->new_instance();
            kutori_type->call("update_info", { kutori_obj.wrapper(), 160.0f, 45.0f });
            kutori_type->set("age", kutori_obj.wrapper(), 15);

            nobject height = kutori_type_by_name->get("height", kutori_obj.wrapper());
            NTR_TEST_ASSERT(height.type()->is_numeric());
            nobject weight = kutori_type_by_name->get("weight", kutori_obj.wrapper());
            NTR_TEST_ASSERT(weight.type()->is_numeric());
            nobject age = kutori_type_by_name->get("age", kutori_obj.wrapper());
            NTR_TEST_ASSERT(age.type()->is_numeric());
            nobject value =
                kutori_type_by_name->call("get_value", { kutori_obj.wrapper() });
            NTR_TEST_ASSERT(value.type()->is_pointer());
            std::cout << "kutori's height is: " << nnumeric::get_value(height) << "cm"
                      << std::endl;
            std::cout << "kutori's weight is: " << nnumeric::get_value(weight) << "kg"
                      << std::endl;
            std::cout << "kutori's age is: " << nnumeric::get_value(age) << "years old"
                      << std::endl;
            std::cout << "kutori's value target is: "
                      << npointer::get_target(value).as<double>() << std::endl;
        }

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return 1;
    }
}
