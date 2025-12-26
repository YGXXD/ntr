//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include "ntr_test.hpp"
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
        // test object
        nvector<kutori> kutori_vector;
        // operator[]
        kutori qiudu(std::string(100, 'c'));
        kutori_vector.push_back(qiudu);
        kutori_vector.push_back(qiudu);
        kutori_vector.push_back(kutori("chen"));
        kutori_vector.insert(1, kutori("duqiu"));
        kutori_vector.insert(2, kutori("cqd cqd"));
        NTR_TEST_ASSERT(kutori_vector[1].get_name() == "duqiu");
        NTR_TEST_ASSERT(kutori_vector[4].get_name() == "chen");
        // reserve
        kutori_vector.reserve(20);
        NTR_TEST_ASSERT(kutori_vector.size() == 5);
        int curr_copy_construct = kutori_copy_construct;
        for (int i = 0; i < 20; i++)
            kutori_vector.insert(0, kutori("kutori"));
        NTR_TEST_ASSERT(curr_copy_construct == kutori_copy_construct);
        NTR_TEST_ASSERT(kutori_vector.size() == 25);
        NTR_TEST_ASSERT(kutori_vector[0].get_name() == "kutori");
        NTR_TEST_ASSERT(kutori_vector[10].get_name() == "kutori");
        NTR_TEST_ASSERT(kutori_vector[19].get_name() == "kutori");
        NTR_TEST_ASSERT(kutori_vector[20].get_name() == qiudu.get_name());
        // pop clear
        for (int i = 0; i < 10; i++)
            kutori_vector.pop_back();
        NTR_TEST_ASSERT(kutori_vector.size() == 15);
        kutori_vector.clear();
        NTR_TEST_ASSERT(kutori_vector.empty());
        NTR_TEST_ASSERT(kutori_construct + kutori_copy_construct +
                            kutori_move_construct ==
                        kutori_destroy + 1);
        // copy construct
        kutori instance("copy kutori");
        kutori_vector.push_back(instance);
        kutori_vector.insert(0, instance);
        NTR_TEST_ASSERT(kutori_copy_construct == 4);
        kutori_vector.clear();
        NTR_TEST_ASSERT(kutori_construct + kutori_copy_construct +
                            kutori_move_construct ==
                        kutori_destroy + 2);

        // performance test
        auto t1 = std::chrono::high_resolution_clock::now();
        nvector<kutori> test1;
        test1.reserve(100);
        for (int i = 0; i < 9000; ++i)
        {
            std::string key = std::to_string(i);
            test1.insert(0, kutori(key));
        }
        for (int i = 0; i < 10000; ++i)
        {
            std::string key = std::to_string(i);
            test1.push_back(kutori(key));
        }
        for (int i = 2000; i < 8000; ++i)
        {
            test1.remove(2000);
        }
        int v1 = 0;
        for (auto& value : test1)
        {
            v1 += 1;
        }
        std::cout << "Time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(
                         std::chrono::high_resolution_clock::now() - t1)
                         .count()
                  << "ms\n";
        std::cout << test1.size() << v1 << "\n";

        auto t2 = std::chrono::high_resolution_clock::now();
        std::vector<kutori> test2;
        test2.reserve(100);
        for (int i = 0; i < 9000; ++i)
        {
            std::string key = std::to_string(i);
            test2.insert(test2.begin(), kutori(key));
        }
        for (int i = 0; i < 10000; ++i)
        {
            std::string key = std::to_string(i);
            test2.push_back(kutori(key));
        }
        for (int i = 2000; i < 8000; ++i)
        {
            test2.erase(test2.begin() + 2000);
        }
        int v2 = 0;
        for (auto& value : test2)
        {
            v2 += 1;
        }
        std::cout << "Time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(
                         std::chrono::high_resolution_clock::now() - t2)
                         .count()
                  << "ms\n";
        std::cout << test2.size() << v2 << "\n";
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return 1;
    }
}
