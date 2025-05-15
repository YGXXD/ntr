# ntr

> **n**ephren **t**ype **r**eflection，奈芙莲类型反射库

✨**如果你喜欢奈芙莲，请献上你宝贵的star**✨

<img align='right' src='img/nephren.png' width="192"></img>

[![code-size](https://img.shields.io/github/languages/code-size/YGXXD/ntr?style=flat)](https://github.com/YGXXD/ntr/archive/main.zip) [![license](https://img.shields.io/github/license/YGXXD/ntr)](LICENSE) [![tag](https://img.shields.io/github/v/tag/YGXXD/ntr)](https://github.com/YGXXD/ntr/tags)

### 环境

- 编译器：cl，clang，gcc；
- c++版本：c++17及以上；

### 特性 

- 支持任意类型的注册和查询，自动生成类型元数据；
- 提供类类型反射，支持类中属性和函数注册查询机制；
- 提供枚举类型反射，支持枚举项的注册查询机制；
- 提供类型擦除容器，支持运行时创建任意类型实例；

### 构建和安装 

```shell
# unix
mkdir build && cd build
cmake ..
sudo make install

# windows
cmake -S . -B ./build
cmake --install ./build --config Release
```

### 项目中使用 

```cmake
# CMakeLists.txt
add_executable(exemple main.cpp)

find_package(ntr REQUIRED)
target_link_libraries(exemple PUBLIC ntr::ntr)
```

### 示例 

```c++
#include "<ntr/nephren.hpp>"
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
```

### 许可证

&emsp;&emsp;ntr使用MIT许可证，详细信息请参见[LICENSE](LICENSE)文件。