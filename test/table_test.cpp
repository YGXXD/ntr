//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "ntr_test.hpp"
#include "util/nhash_set.hpp"
#include <chrono>

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
        // test hash set
        nhash_set<int> number_set;
        number_set.insert(1);
        number_set.insert(2);
        number_set.insert(3);
        number_set.insert(1);
        NTR_TEST_ASSERT(number_set.size() == 3);
        NTR_TEST_ASSERT(number_set.find(1) != number_set.end());
        NTR_TEST_ASSERT(number_set.find(4) == number_set.end());
        number_set.remove(1);
        NTR_TEST_ASSERT(number_set.size() == 2);
        NTR_TEST_ASSERT(number_set.remove(3));
        number_set.insert(1);
        number_set.insert(2);
        number_set.insert(3);
        number_set.insert(33);
        number_set.insert(65);
        for (auto& value : number_set)
            NTR_TEST_ASSERT(number_set.find(value) != number_set.end());

        // test hash map
        nhash_map<std::string, kutori> kutori_map;
        // operator[]
        kutori_map["chen"] = kutori("duqiu");
        kutori_map["chen"] = kutori("qiudu");
        NTR_TEST_ASSERT(kutori_map.at("chen").get_name() == "qiudu");
        // insert key value
        kutori_map.insert_or_assign("du", kutori("qiuchen"));
        NTR_TEST_ASSERT(kutori_map.at("du").get_name() == "qiuchen");
        kutori_map.insert_or_assign("du", kutori("qiudu"));
        NTR_TEST_ASSERT(kutori_map.at("du").get_name() == "qiudu");
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

        // performance test hash_set
        {
            auto t1 = std::chrono::high_resolution_clock::now();
            nhash_set<int> test1;
            test1.reserve(10000);
            for (int i = 0; i < 1000000; ++i)
            {
                test1.insert(i);
            }
            for (int i = 200000; i < 800000; ++i)
            {
                test1.remove(i);
            }
            int v1 = 0;
            for (auto& key : test1)
            {
                v1 += key;
            }
            std::cout << "Time: "
                      << std::chrono::duration_cast<std::chrono::milliseconds>(
                             std::chrono::high_resolution_clock::now() - t1)
                             .count()
                      << "ms\n";
            std::cout << test1.size() << v1 << "\n";

            auto t2 = std::chrono::high_resolution_clock::now();
            std::unordered_set<int> test2;
            test2.reserve(10000);
            for (int i = 0; i < 1000000; ++i)
            {
                test2.insert(i);
            }
            for (int i = 200000; i < 800000; ++i)
            {
                test2.erase(i);
            }
            int v2 = 0;
            for (auto& key : test2)
            {
                v2 += key;
            }
            std::cout << "Time: "
                      << std::chrono::duration_cast<std::chrono::milliseconds>(
                             std::chrono::high_resolution_clock::now() - t2)
                             .count()
                      << "ms\n";
            std::cout << test2.size() << v2 << "\n";
        }
        std::vector<int> a;
        a.push_back(1);
        // performance test hash_map
        {
            auto t1 = std::chrono::high_resolution_clock::now();
            nhash_map<int, kutori> test1;
            test1.reserve(10000);
            for (int i = 0; i < 1000000; ++i)
            {
                std::string key = std::to_string(i);
                test1.insert({ i, kutori(key) });
            }
            for (int i = 200000; i < 800000; ++i)
            {
                std::string key = std::to_string(i);
                test1.remove(i);
            }
            int v1 = 0;
            for (auto& [key, value] : test1)
            {
                v1 += key;
            }
            std::cout << "Time: "
                      << std::chrono::duration_cast<std::chrono::milliseconds>(
                             std::chrono::high_resolution_clock::now() - t1)
                             .count()
                      << "ms\n";
            std::cout << test1.size() << v1 << "\n";

            auto t2 = std::chrono::high_resolution_clock::now();
            std::unordered_map<int, kutori> test2;
            test2.reserve(10000);
            for (int i = 0; i < 1000000; ++i)
            {
                std::string key = std::to_string(i);
                test2.insert({ i, kutori(key) });
            }
            for (int i = 200000; i < 800000; ++i)
            {
                std::string key = std::to_string(i);
                test2.erase(i);
            }
            int v2 = 0;
            for (auto& [key, value] : test2)
            {
                v2 += key;
            }
            std::cout << "Time: "
                      << std::chrono::duration_cast<std::chrono::milliseconds>(
                             std::chrono::high_resolution_clock::now() - t2)
                             .count()
                      << "ms\n";
            std::cout << test2.size() << v2 << "\n";
        }
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return 1;
    }
}
