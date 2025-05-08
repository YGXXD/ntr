#include "nephren.hpp"
#include <iostream>

using namespace ntr;

class kutori
{
public:
    void update_info(float in_height, float in_weight)
    {
        height = in_height;
        weight = in_weight;
    }

    const int& age() const { return _age; }
    void set_age(const int& age) { _age = age; }

    float height;
    float weight;

private:
    int _age;
};

int main()
{
    // 注册珂朵莉类型
    nephren::type<kutori>("kutori")
        .property("age", &kutori::age, &kutori::set_age)
        .property("height", &kutori::height)
        .property("weight", &kutori::weight)
        .function("update_info", &kutori::update_info);

    // 获取珂朵莉类型
    const nclass* kutori_type = nephren::get<kutori>();
    // 可以通过注册名动态获取
    const nclass* kutori_type_by_name = nephren::get("kutori")->as_class();

    // 调用珂朵莉实例的成员函数
    nobject kutori_obj = kutori_type->new_instance();
    kutori_type->call("update_info", { kutori_obj.wrapper(), 160.0f, 45.0f });

    // 设置珂朵莉实例的成员变量
    kutori_type->set("age", kutori_obj.wrapper(), 15);

    // 获取珂朵莉实例的成员变量
    nobject height = kutori_type->get("height", kutori_obj.wrapper());
    nobject weight = kutori_type->get("weight", kutori_obj.wrapper());
    nobject age = kutori_type->get("age", kutori_obj.wrapper());
    std::cout << "珂朵莉的身高是: " << height.as<float>() << "cm" << std::endl;
    std::cout << "珂朵莉的体重是: " << weight.as<float>() << "kg" << std::endl;
    std::cout << "珂朵莉的年龄是: " << age.as<int>() << "岁" << std::endl;

    return 0;
}
