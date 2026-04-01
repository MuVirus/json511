#include <iostream>
#include <string>
#include <vector>
#include "json511.hpp"

using namespace json11;
using namespace std;

int main() {

    std::cout << "Json标准测试" << std::endl;
    // --- 标准JSON 解析 ---
    string json_str = R"({
        "name": "Alice",
        "age": 30,
        "is_active": true,
        "skills": ["C++", "Python"]
    })";

    string err;
    // 解析 JSON 字符串
    Json json = Json::parse(json_str, err);

    if (!err.empty()) {
        cerr << "解析错误: " << err << endl;
        return 1;
    }

    // 获取值
    string name = json["name"].string_value();
    int age = json["age"].int_value();
    bool is_active = json["is_active"].bool_value();
    
    cout << "--- 解析结果 ---" << endl;
    cout << "姓名: " << name << endl;
    cout << "年龄: " << age << endl;
    cout << "状态: " << (is_active ? "激活" : "未激活") << endl;
    
    // 获取数组
    cout << "技能: ";
    for (const auto &skill : json["skills"].array_items()) {
        cout << skill.string_value() << " ";
    }
    cout << endl << endl;

    // json生成
    Json json_to_dump = Json::object {
        { "id", 101 },
        { "project", "Json11Test" },
        { "completed", true },
        { "tags", Json::array { "json", "cpp", "test" } }
    };

    // 将对象转回字符串 (dump())
    string output_str = json_to_dump.dump();
    
    cout << "--- 生成结果 ---" << endl;
    cout << output_str << endl;

    std::cout << std::endl;
    std::cout << "Json5测试" << std::endl;
    // --- JSON5 解析 ---
    string json5_str = R"({
        name: 'Ali
        ce', /* hello */
        "age": NaN, // hello
        "is_active": true,
        /* skills:
        *  - C++
        *  - Python
        */
        'skills': ['C++',   'Python', ],
        "height": .175e1,   
    })";
    // string json5_str = "{\n\
    //     name: `Al\n\
    //     ice`, /* hello */\n\
    //     \"age\": NaN, // hello\n\
    //     \"is_active\": true,\n\
    //     /* skills:\n\
    //     *  - C++\n\
    //     *  - Python\n\
    //     */\n\
    //     'skills': ['C++', 'Python'],\n\
    //     \"height\": .175e1\n\
    // }";

    string err5;
    // 解析 JSON 字符串
    Json json5 = Json::parse(json5_str, err5);

    if (!err5.empty()) {
        cerr << "解析错误: " << err5 << endl;
        return 1;
    }

    // 获取值
    string name5 = json5["name"].string_value();
    int age5 = json5["age"].int_value();
    bool is_active5 = json5["is_active"].bool_value();
    
    cout << "--- 解析结果 ---" << endl;
    cout << "姓名: " << name5 << endl;
    cout << "年龄: " << age5 << endl;
    cout << "状态: " << (is_active5 ? "激活" : "未激活") << endl;
    cout << "身高: " << json5["height"].number_value() << endl;
    
    // 获取数组
    cout << "技能: ";
    for (const auto &skill : json5["skills"].array_items()) {
        cout << skill.string_value() << " ";
    }
    cout << endl << endl;

    // json生成
    Json json_to_dump5 = Json::object {
        { "id", 101 },
        { "project", "Json11Test" },
        { "completed", true },
        { "tags", Json::array { "json", "cpp", "test" } }
    };

    // 将对象转回字符串 (dump())
    string output_str5 = json_to_dump5.dump();
    
    cout << "--- 生成结果 ---" << endl;
    cout << output_str5 << endl;


    return 0;
} 