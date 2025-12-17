//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "ntr_test.hpp"

using namespace ntr;

struct weapon
{
    std::string left;
    std::string right;
};

struct kutori
{
    int age;
    int height;
    int weight;
    std::string name;
    nvector<std::string> data_list;
    nhash_map<std::string, float> data_map;
    nhash_set<int> data_set;
    nhash_map<std::string, weapon> weapons;
    kutori* friend_kutori;
};

int print_ntr_instance(std::string_view name, const nwrapper& instance, int depth)
{
    const nclass* type = instance.type()->as_class();
    for (int i = 0; i < depth; i++)
        std::cout << "  ";
    if (name.size())
        std::cout << name << ": ";
    switch (instance.type()->kind())
    {
    case ntr::ntype::etype::eunknown:
        break;
    case ntr::ntype::etype::epointer:
    {
        std::cout << npointer::get_value(instance);
    }
    break;
    case ntr::ntype::etype::enumeric:
    {
        std::cout << nnumeric::get_value(instance);
    }
    break;
    case ntr::ntype::etype::eenum:
    {
        std::cout << nenum::get_value(instance);
    }
    break;
    case ntr::ntype::etype::eclass:
    {
        if (instance.type() == nephren::get<std::string>())
        {
            std::cout << instance.unwrap<std::string>();
        }
        else
        {
            std::cout << "{" << std::endl;
            for (auto& property : instance.type()->as_class()->propertys())
            {
                nobject value = property->get(instance);
                NTR_TEST_ASSERT(value.is_valid());
                NTR_TEST_ASSERT(value.kind() == nobject::eobject::ereference);
                print_ntr_instance(property->name(), value.wrapper(), depth + 1);
            }
            for (int i = 0; i < depth; i++)
                std::cout << "  ";
            std::cout << "}";
        }
    }
    break;
    case ntr::ntype::etype::estd_pair:
    {
        std::pair<nobject, nobject> unpacked = nstd_pair::unpack(instance);
        std::cout << "(" << std::endl;
        NTR_TEST_ASSERT(unpacked.first.is_valid());
        NTR_TEST_ASSERT(unpacked.first.kind() == nobject::eobject::ereference);
        print_ntr_instance("first", unpacked.first.wrapper(), depth + 1);
        NTR_TEST_ASSERT(unpacked.second.is_valid());
        NTR_TEST_ASSERT(unpacked.second.kind() == nobject::eobject::ereference);
        print_ntr_instance("second", unpacked.second.wrapper(), depth + 1);
        for (int i = 0; i < depth; i++)
            std::cout << "  ";
        std::cout << ")";
    }
    break;
    case ntr::ntype::etype::econtainer:
    {
        const ncontainer* container = instance.type()->as_container();
        nobject end = container->end(instance);
        std::cout << "[" << std::endl;
        for (nobject it = container->begin(instance);
             !container->equal(it.wrapper(), end.wrapper());
             instance.type()->as_container()->next(it.wrapper()))
        {
            nobject value = instance.type()->as_container()->get(it.wrapper());
            NTR_TEST_ASSERT(value.is_valid());
            NTR_TEST_ASSERT(value.kind() == nobject::eobject::ereference);
            print_ntr_instance("", value.wrapper(), depth + 1);
        }
        for (int i = 0; i < depth; i++)
            std::cout << "  ";
        std::cout << "]";
    }
    break;
    }
    std::cout << std::endl;
    return 0;
}

int main()
{
    try
    {
        nephren::type<weapon>("weapon")
            .property("left", &weapon::left)
            .property("right", &weapon::right);
        nephren::type<kutori>("kutori")
            .property("age", &kutori::age)
            .property("height", &kutori::height)
            .property("weight", &kutori::weight)
            .property("name", &kutori::name)
            .property("data_list", &kutori::data_list)
            .property("data_map", &kutori::data_map)
            .property("data_set", &kutori::data_set)
            .property("weapons", &kutori::weapons)
            .property("friend_kutori", &kutori::friend_kutori);

        kutori friend_kutori {};
        kutori test_kutori {};
        test_kutori.age = 18;
        test_kutori.height = 170;
        test_kutori.weight = 60;
        test_kutori.name = "qiudu";
        test_kutori.data_list = {
            "123",
            "987",
        };
        test_kutori.data_map = {
            { "123", 123.1f },
            { "456", 456.2f },
        };
        test_kutori.data_set = {
            985,
            211,
        };
        test_kutori.weapons = {
            { "weapon0", { "sword", "axe" } },
            { "weapon1", { "bow", "arrow" } },
        };
        test_kutori.friend_kutori = &friend_kutori;
        nobject test_kutori_ref = nephren::get<kutori>()->ref_instance(test_kutori);
        return print_ntr_instance("kutori", test_kutori_ref.wrapper(), 0);
    }
    catch (const std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return 1;
    }
}
