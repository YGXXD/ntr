#include "nephren.hpp"
#include <iostream>

#define NTR_TEST_ASSERT(condition)                                    \
    if (!(condition))                                                 \
    {                                                                 \
        std::cerr << "Test failed at line " << __LINE__ << std::endl; \
        return 1;                                                     \
    }

using namespace ntr;

int main()
{
    try
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
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
