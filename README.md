# Json511

## 项目介绍 / Project Introduction
json511是一个适用于C++11的小型JSON5库，支持JSON5的解析与序列化，基于dropbox json11库。
json511 is a lightweight JSON5 library for C++11, providing JSON5 parsing and serialization capabilities, based on the dropbox json11 library.

## 项目功能 / Project Features
- 支持JSON5语法特性，包括对象键名可以不加引号、字符串可以用单引号、数字支持多种格式、字符串支持换行、尾随逗号等
- 提供简洁易用的API接口
- 支持C++11及以上版本
- 无外部依赖，纯C++实现

- Supports JSON5 syntax features, including unquoted object keys, single-quoted strings, multiple number formats, multiline strings, trailing commas, etc.
- Provides a clean and easy-to-use API
- Supports C++11 and above
- No external dependencies, pure C++ implementation

## 项目使用 / Project Usage
```cpp
#include "json511.hpp"
#include <iostream>

using namespace json11;

int main() {
    // 解析JSON5字符串
    std::string json_str = R"({
        name: "John",
        age: 30,
        active: true,
        hobbies: ['reading', 'coding'],
        address: {
            street: '123 Main St',
            city: 'New York'
        }
    })";
    
    std::string err;
    Json json = Json::parse(json_str, err);
    
    if (!err.empty()) {
        std::cerr << "解析错误: " << err << std::endl;
        return 1;
    }
    
    // 访问JSON数据
    std::cout << "Name: " << json["name"].string_value() << std::endl;
    std::cout << "Age: " << json["age"].int_value() << std::endl;
    std::cout << "Active: " << (json["active"].bool_value() ? "true" : "false") << std::endl;
    
    // 序列化JSON对象
    Json obj = Json::object({
        {"name", "John"},
        {"age", 30},
        {"active", true}
    });
    
    std::cout << "Serialized JSON: " << obj.dump() << std::endl;
    
    return 0;
}
```

## 项目测试 / Project Testing
项目提供了完整的单元测试，测试文件为`test.cpp`，包含了对所有JSON5特性的测试。
The project provides comprehensive unit tests in `test.cpp`, covering all JSON5 features.

## 项目进展 / Project Progress
- [x] 对象键名可以不加引号 / Unquoted object keys
- [x] 字符串可以用单引号 / Single-quoted strings
- [x] 数字支持多种格式 / Multiple number formats (decimal, hex, float, scientific notation)
- [x] 字符串支持换行 / Multiline strings
- [x] 尾随逗号 / Trailing commas

## 许可证 / License
本项目基于MIT许可证开源。
This project is open source under the MIT License.
