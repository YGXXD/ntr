//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "ntr_test.hpp"

using namespace ntr;

class kutori
{
public:
    kutori() : _value(new double(666.0)) {}
    kutori(const kutori& other) : _value(new double(*other._value)) {}
    kutori(kutori&& other) : _value(other._value) { other._value = nullptr; }
    ~kutori()
    {
        if (_value)
            delete _value;
    }
    const double* get_value() const { return _value; }

private:
    double* _value;
};

int main()
{
    try
    {
        // test object
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
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return 1;
    }
}
