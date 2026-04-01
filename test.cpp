#include "json511.hpp"
#include <iostream>
#include <string>

using namespace json11;

// 测试结果结构体
struct TestResult {
    std::string test_name;
    bool passed;
    std::string error_message;
    int line_number;
    std::string test_case;
};

// 测试函数模板
template<typename T>
TestResult test(const std::string& test_name, const std::string& json_str, T expected, int line = __LINE__, const std::string& test_case = "") {
    std::string err;
    Json json = Json::parse(json_str, err);
    
    if (!err.empty()) {
        return {test_name, false, "解析错误: " + err, line, test_case};
    }
    
    if (json != Json(expected)) {
        return {test_name, false, "值不匹配: 期望 " + Json(expected).dump() + ", 实际 " + json.dump(), line, test_case};
    }
    
    return {test_name, true, "", line, test_case};
}

// 辅助宏，用于记录行号和测试用例
#define TEST_CASE(name, json_str, expected) test(name, json_str, expected, __LINE__, #json_str)
#define ASSERT_TRUE(condition, name, message) (condition) ? TestResult{name, true, "", __LINE__, #condition} : TestResult{name, false, message, __LINE__, #condition}
#define ASSERT_EQ(actual, expected, name, message) ((actual) == (expected)) ? TestResult{name, true, "", __LINE__, #actual " == " #expected} : TestResult{name, false, message, __LINE__, #actual " == " #expected}

// 测试对象键名可以不加引号
TestResult test_unquoted_keys() {
    std::string json_str = R"({
        name: "John",
        age: 30,
        active: true
    })";
    
    std::string err;
    Json json = Json::parse(json_str, err);
    
    if (!err.empty()) {
        return {"对象键名可以不加引号", false, "解析错误: " + err, __LINE__, json_str};
    }
    
    auto result1 = ASSERT_EQ(json["name"].string_value(), "John", "对象键名可以不加引号", "name字段值不匹配");
    if (!result1.passed) return result1;
    
    auto result2 = ASSERT_EQ(json["age"].int_value(), 30, "对象键名可以不加引号", "age字段值不匹配");
    if (!result2.passed) return result2;
    
    auto result3 = ASSERT_EQ(json["active"].bool_value(), true, "对象键名可以不加引号", "active字段值不匹配");
    if (!result3.passed) return result3;
    
    return {"对象键名可以不加引号", true, "", __LINE__, "所有字段验证通过"};
}

// 测试字符串可以用单引号
TestResult test_single_quoted_strings() {
    std::string json_str = R"({
        'name': 'John',
        "age": 30,
        'active': true
    })";
    
    std::string err;
    Json json = Json::parse(json_str, err);
    
    if (!err.empty()) {
        return {"字符串可以用单引号", false, "解析错误: " + err, __LINE__, json_str};
    }
    
    auto result1 = ASSERT_EQ(json["name"].string_value(), "John", "字符串可以用单引号", "name字段值不匹配");
    if (!result1.passed) return result1;
    
    auto result2 = ASSERT_EQ(json["age"].int_value(), 30, "字符串可以用单引号", "age字段值不匹配");
    if (!result2.passed) return result2;
    
    auto result3 = ASSERT_EQ(json["active"].bool_value(), true, "字符串可以用单引号", "active字段值不匹配");
    if (!result3.passed) return result3;
    
    return {"字符串可以用单引号", true, "", __LINE__, "所有字段验证通过"};
}

// 测试数字支持多种格式
TestResult test_number_formats() {
    std::string json_str = R"({
        decimal: 123,
        hex: 0x1A,
        float: 123.45,
        scientific: 1.23e2,
        negative: -456,
        pointEnd: 100.,
        pointStart: .100,
    })";
    
    std::string err;
    Json json = Json::parse(json_str, err);
    
    if (!err.empty()) {
        return {"数字支持多种格式", false, "解析错误: " + err, __LINE__, json_str};
    }
    
    auto result1 = ASSERT_EQ(json["decimal"].int_value(), 123, "数字支持多种格式", "decimal字段值不匹配");
    if (!result1.passed) return result1;
    
    auto result2 = ASSERT_EQ(json["hex"].int_value(), 26, "数字支持多种格式", "hex字段值不匹配");
    if (!result2.passed) return result2;
    
    auto result3 = ASSERT_EQ(json["float"].number_value(), 123.45, "数字支持多种格式", "float字段值不匹配");
    if (!result3.passed) return result3;
    
    auto result4 = ASSERT_EQ(json["scientific"].number_value(), 123, "数字支持多种格式", "scientific字段值不匹配");
    if (!result4.passed) return result4;
    
    auto result5 = ASSERT_EQ(json["negative"].int_value(), -456, "数字支持多种格式", "negative字段值不匹配");
    if (!result5.passed) return result5;

    auto result6 = ASSERT_EQ(json["pointEnd"].number_value(), 100, "数字支持多种格式", "pointEnd字段值不匹配");
    if (!result6.passed) return result6;

    auto result7 = ASSERT_EQ(json["pointStart"].number_value(), 0.1, "数字支持多种格式", "pointEnd字段值不匹配");
    if (!result7.passed) return result7;

    return {"数字支持多种格式", true, "", __LINE__, "所有字段验证通过"};
}

// 测试字符串支持换行
TestResult test_multiline_strings() {
    std::string json_str = R"({
        text: 'Line 1
Line 2
Line 3'
    })";
    
    std::string err;
    Json json = Json::parse(json_str, err);
    
    if (!err.empty()) {
        return {"字符串支持换行", false, "解析错误: " + err, __LINE__, json_str};
    }
    
    auto result = ASSERT_EQ(json["text"].string_value(), "Line 1\nLine 2\nLine 3", "字符串支持换行", "text字段值不匹配");
    if (!result.passed) return result;
    
    return {"字符串支持换行", true, "", __LINE__, "所有字段验证通过"};
}

// 测试尾随逗号
TestResult test_trailing_commas() {
    std::string json_str = R"({
        name: "John",
        age: 30,
        active: true,
    })";
    
    std::string err;
    Json json = Json::parse(json_str, err);
    
    if (!err.empty()) {
        return {"尾随逗号", false, "解析错误: " + err, __LINE__, json_str};
    }
    
    auto result1 = ASSERT_EQ(json["name"].string_value(), "John", "尾随逗号", "name字段值不匹配");
    if (!result1.passed) return result1;
    
    auto result2 = ASSERT_EQ(json["age"].int_value(), 30, "尾随逗号", "age字段值不匹配");
    if (!result2.passed) return result2;
    
    auto result3 = ASSERT_EQ(json["active"].bool_value(), true, "尾随逗号", "active字段值不匹配");
    if (!result3.passed) return result3;
    
    // 测试数组中的尾随逗号
    std::string array_str = R"([1, 2, 3,])";
    Json array = Json::parse(array_str, err);
    
    if (!err.empty()) {
        return {"尾随逗号", false, "数组解析错误: " + err, __LINE__, array_str};
    }
    
    auto result4 = ASSERT_EQ(array.array_items().size(), 3u, "尾随逗号", "数组长度不匹配");
    if (!result4.passed) return result4;
    
    auto result5 = ASSERT_EQ(array[0].int_value(), 1, "尾随逗号", "数组第一个元素值不匹配");
    if (!result5.passed) return result5;
    
    auto result6 = ASSERT_EQ(array[1].int_value(), 2, "尾随逗号", "数组第二个元素值不匹配");
    if (!result6.passed) return result6;
    
    auto result7 = ASSERT_EQ(array[2].int_value(), 3, "尾随逗号", "数组第三个元素值不匹配");
    if (!result7.passed) return result7;
    
    return {"尾随逗号", true, "", __LINE__, "所有字段验证通过"};
}

int main() {
    std::vector<TestResult> results;
    
    // 运行所有测试
    results.push_back(test_unquoted_keys());
    results.push_back(test_single_quoted_strings());
    results.push_back(test_number_formats());
    results.push_back(test_multiline_strings());
    results.push_back(test_trailing_commas());
    
    // 输出测试结果
    std::cout << "===== Json511 单元测试结果 =====" << std::endl;
    int passed_count = 0;
    
    for (const auto& result : results) {
        if (result.passed) {
            std::cout << "✅ " << result.test_name << " - 通过" << std::endl;
            passed_count++;
        } else {
            std::cout << "❌ " << result.test_name << " - 失败" << std::endl;
            std::cout << "   错误信息: " << result.error_message << std::endl;
            std::cout << "   行号: " << result.line_number << std::endl;
            std::cout << "   测试用例: " << result.test_case << std::endl;
        }
    }
    
    std::cout << "\n测试总结: " << passed_count << "/" << results.size() << " 个测试通过" << std::endl;
    
    return passed_count == results.size() ? 0 : 1;
}
