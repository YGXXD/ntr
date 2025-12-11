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
        vector_kutori_type->puts(kutori_vector, { kutori("kutori2"), kutori("kutori3") });
        NTR_TEST_ASSERT(kutori_vector.size() == 4);
        NTR_TEST_ASSERT(vector_kutori_type->size(kutori_vector) == 4);
        nobject kutori_vector_it = vector_kutori_type->begin(kutori_vector);
        for (auto& value : kutori_vector)
        {
            NTR_TEST_ASSERT(vector_kutori_type->get(kutori_vector_it.wrapper())
                                .as<kutori>()
                                .get_name() == value.get_name());
            NTR_TEST_ASSERT(
                &vector_kutori_type->get(kutori_vector_it.wrapper()).as<kutori>() ==
                &value);
            NTR_TEST_ASSERT(vector_kutori_type->get(kutori_vector_it.wrapper()).data() ==
                            &value);
            vector_kutori_type->next(kutori_vector_it.wrapper());
        }
        nobject kutori_vector_begin = vector_kutori_type->begin(kutori_vector);
        nobject kutori_vector_end = vector_kutori_type->end(kutori_vector);
        int i = 0;
        for (nobject it = std::move(kutori_vector_begin);
             !vector_kutori_type->equal(it.wrapper(), kutori_vector_end.wrapper());
             vector_kutori_type->next(it.wrapper()))
        {
            NTR_TEST_ASSERT(
                vector_kutori_type->get(it.wrapper()).as<kutori>().get_name() ==
                kutori_vector[i].get_name());
            ++i;
        }
        vector_kutori_type->clear(kutori_vector);
        NTR_TEST_ASSERT(kutori_construct + kutori_copy_construct +
                            kutori_move_construct ==
                        kutori_destroy);
        NTR_TEST_ASSERT(kutori_vector.size() == 0);

        const ncontainer* map_string_kutori_type =
            nephren::get<nhash_map<std::string, kutori>>();
        nhash_map<std::string, kutori> kutori_map;
        kutori_map.insert("kutori0", kutori("kutori0"));
        kutori_map.insert("kutori1", kutori("kutori1"));
        map_string_kutori_type->puts(
            kutori_map, { std::pair<std::string, kutori>("kutori2", kutori("kutori2")),
                          std::pair<std::string, kutori>("kutori3", kutori("kutori3")) });
        nobject kutori_map_it = map_string_kutori_type->begin(kutori_map);
        for (auto& [key, value] : kutori_map)
        {
            using element_type = std::pair<std::string, kutori>;
            NTR_TEST_ASSERT(map_string_kutori_type->get(kutori_map_it.wrapper())
                                .as<element_type>()
                                .first == key);
            NTR_TEST_ASSERT(map_string_kutori_type->get(kutori_map_it.wrapper())
                                .as<element_type>()
                                .second.get_name() == value.get_name());
            NTR_TEST_ASSERT(&map_string_kutori_type->get(kutori_map_it.wrapper())
                                 .as<element_type>()
                                 .first == &key);
            NTR_TEST_ASSERT(&map_string_kutori_type->get(kutori_map_it.wrapper())
                                 .as<element_type>()
                                 .second == &value);
            map_string_kutori_type->next(kutori_map_it.wrapper());
        }
        NTR_TEST_ASSERT(kutori_map.size() == 4);
        NTR_TEST_ASSERT(map_string_kutori_type->size(kutori_map) == 4);
        map_string_kutori_type->clear(kutori_map);
        NTR_TEST_ASSERT(kutori_construct + kutori_copy_construct +
                            kutori_move_construct ==
                        kutori_destroy);
        NTR_TEST_ASSERT(kutori_map.size() == 0);

        const ncontainer* set_float_type = nephren::get<nhash_set<float>>();
        nhash_set<float> float_set;
        float_set.insert(1.0f);
        float_set.insert(2.0f);
        set_float_type->puts(float_set, { 1.0f, 2.0f, 3.0f, 4.0f });
        NTR_TEST_ASSERT(float_set.size() == 4);
        NTR_TEST_ASSERT(set_float_type->size(float_set) == 4);
        nobject float_set_begin = set_float_type->begin(float_set);
        nobject float_set_end = set_float_type->end(float_set);
        for (nobject it = std::move(float_set_begin);
             !set_float_type->equal(it.wrapper(), float_set_end.wrapper());
             set_float_type->next(it.wrapper()))
        {
            std::cout << set_float_type->get(it.wrapper()).as<float>() << std::endl;
        }
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
