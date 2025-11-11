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
    kutori(const kutori& other) : _name(other._name) { ++kutori_construct; }
    kutori(kutori&& other) : _name(std::move(other._name)) { ++kutori_construct; }
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
        // test object
        nhash_map<std::string, kutori> kutori_map;
        // operator[]
        kutori_map["chen"] = kutori("duqiu");
        kutori_map["chen"] = kutori("qiudu");
        NTR_TEST_ASSERT(kutori_map.at("chen").get_name() == "qiudu");
        // insert key value
        kutori_map.insert("du", kutori("qiuchen"));
        NTR_TEST_ASSERT(kutori_map.at("du").get_name() == "qiuchen");
        kutori_map.insert("du", kutori("qiudu"));
        NTR_TEST_ASSERT(kutori_map.at("du").get_name() == "qiuchen");
        // insert pair
        kutori_map.insert({ "chen", kutori("chenchen") });
        NTR_TEST_ASSERT(kutori_map.at("chen").get_name() == "qiudu");
        // size
        NTR_TEST_ASSERT(kutori_map.size() == 2);
        // remove
        kutori_map.remove("du");
        kutori_map.remove("chen");
        NTR_TEST_ASSERT(kutori_map.empty());
        NTR_TEST_ASSERT(kutori_construct + kutori_copy_construct +
                            kutori_move_construct ==
                        kutori_destroy);
        // clear
        int curr_copy_construct = kutori_copy_construct;
        kutori_map["nota"] = kutori("nota");
        kutori_map["123"] = kutori("123");
        kutori_map.insert({ "kfs", kutori("kfs") });
        kutori_map.insert({ "ssp", kutori("ssp") });
        kutori_map.clear();
        NTR_TEST_ASSERT(curr_copy_construct == kutori_copy_construct);
        NTR_TEST_ASSERT(kutori_construct + kutori_copy_construct +
                            kutori_move_construct ==
                        kutori_destroy);

        // hash conflict
        nhash_map<int, kutori> kutori_imap;
        kutori_imap[1] = kutori("1");
        kutori_imap[2] = kutori("2");
        kutori_imap[3] = kutori("3");
        kutori_imap[33] = kutori("33");
        kutori_imap[65] = kutori("65");
        // reserve
        kutori_imap.reserve(65);
        NTR_TEST_ASSERT(kutori_imap.size() == 5);
        kutori_imap.clear();
        NTR_TEST_ASSERT(kutori_construct + kutori_copy_construct +
                            kutori_move_construct ==
                        kutori_destroy);
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return 1;
    }
}
