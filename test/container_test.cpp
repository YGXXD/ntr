//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "ntr_test.hpp"

using namespace ntr;

int kutori_construct = 0;
int kutori_copy_construct = 0;
int kutori_move_construct = 0;
int kutori_destroy = 0;

class kutori
{
public:
    kutori() : _name() { ++kutori_construct; };
    kutori(const std::string& name) : _name(name) { ++kutori_construct; }
    kutori(const kutori& other) : _name(other._name) { ++kutori_copy_construct; }
    kutori(kutori&& other) : _name(std::move(other._name)) { ++kutori_move_construct; }
    ~kutori() { ++kutori_destroy; }

    kutori& operator=(const kutori& other) = default;
    kutori& operator=(kutori&& other) = default;

    const std::string& get_name() const { return _name; }

private:
    std::string _name;
};

int main()
{
    try
    {
        const ncontainer* vector_kutori_type = nephren::get<nvector<kutori>>();
        nvector<kutori> kutori_vector = { kutori("kutori0"), kutori("kutori1") };
        vector_kutori_type->put(kutori_vector, kutori("kutori2"));
        vector_kutori_type->put(kutori_vector, kutori("kutori3"));
        NTR_TEST_ASSERT(kutori_vector.size() == 4);
        NTR_TEST_ASSERT(vector_kutori_type->size(kutori_vector) == 4);
        auto kutori_vector_it = kutori_vector.begin();
        vector_kutori_type->for_each(kutori_vector,
                                     [&kutori_vector, &kutori_vector_it](nobject&& value)
        {
            NTR_TEST_THROW(value.as<kutori>().get_name() ==
                           (*kutori_vector_it).get_name());
            NTR_TEST_THROW(&value.as<kutori>() == &(*kutori_vector_it));
            NTR_TEST_THROW(value.data() == &(*kutori_vector_it));
            ++kutori_vector_it;
        });
        vector_kutori_type->clear(kutori_vector);
        NTR_TEST_ASSERT(kutori_construct + kutori_copy_construct +
                            kutori_move_construct ==
                        kutori_destroy);
        NTR_TEST_ASSERT(kutori_vector.size() == 0);

        const ncontainer* map_string_kutori_type =
            nephren::get<nhash_map<std::string, kutori>>();
        nhash_map<std::string, kutori> kutori_map;
        kutori_map.insert_or_assign("kutori0", kutori("kutori0"));
        kutori_map.insert_or_assign("kutori1", kutori("kutori1"));
        map_string_kutori_type->put(kutori_map, std::string("kutori2"),
                                    kutori("kutori2"));
        map_string_kutori_type->put(kutori_map, std::string("kutori3"),
                                    kutori("kutori3"));
        map_string_kutori_type->put(kutori_map, std::string("kutori0"),
                                    kutori("kutori4"));
        NTR_TEST_ASSERT(kutori_map.size() == 4);
        NTR_TEST_ASSERT(map_string_kutori_type->size(kutori_map) == 4);
        auto kutori_map_it = kutori_map.begin();
        map_string_kutori_type->for_each(
            kutori_map, [&kutori_map, &kutori_map_it](nobject&& key, nobject&& value)
        {
            NTR_TEST_THROW(key.as<std::string>() == kutori_map_it->first);
            NTR_TEST_THROW(&key.as<std::string>() == &kutori_map_it->first);
            NTR_TEST_THROW(value.as<kutori>().get_name() ==
                           kutori_map_it->second.get_name());
            NTR_TEST_THROW(&value.as<kutori>() == &kutori_map_it->second);
            ++kutori_map_it;
        });
        map_string_kutori_type->clear(kutori_map);
        NTR_TEST_ASSERT(kutori_construct + kutori_copy_construct +
                            kutori_move_construct ==
                        kutori_destroy);
        NTR_TEST_ASSERT(kutori_map.size() == 0);

        const ncontainer* set_float_type = nephren::get<nhash_set<float>>();
        nhash_set<float> float_set;
        float_set.insert(1.0f);
        float_set.insert(2.0f);
        set_float_type->put(float_set, 1.0f);
        set_float_type->put(float_set, 2.0f);
        set_float_type->put(float_set, 3.0f);
        set_float_type->put(float_set, 4.0f);
        NTR_TEST_ASSERT(float_set.size() == 4);
        NTR_TEST_ASSERT(set_float_type->size(float_set) == 4);
        auto float_set_it = float_set.begin();
        set_float_type->for_each(float_set, [&float_set, &float_set_it](nobject&& value)
        {
            NTR_TEST_THROW(value.as<float>() == *float_set_it);
            NTR_TEST_THROW(&value.as<float>() == &(*float_set_it));
            ++float_set_it;
        });
        set_float_type->clear(float_set);
        NTR_TEST_ASSERT(set_float_type->size(float_set) == 0);
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return 1;
    }
}
