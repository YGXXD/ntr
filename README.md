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
# CMakeLists
add_executable(exemple main.cpp)

find_package(ntr REQUIRED)
target_link_libraries(exemple PUBLIC ntr::ntr)
```