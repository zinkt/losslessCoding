#include <iostream>
#include <map>
#include <string>

int main() {
    // 创建一个 map 容器，存储员工的姓名和年龄
    std::map<std::string, int> employees;

    // 插入员工信息
    employees.insert(std::pair<std::string, int>("Alice", 30));
    employees["Bob"] = 25;
    employees["Charlie"] = 35;

    employees["Alice"]++;

    // 遍历 map 并打印员工信息
    for (std::map<std::string, int>::iterator it = employees.begin(); it != employees.end(); ++it) {
        std::cout << it->first << " is " << it->second << " years old." << std::endl;
    }

    return 0;
}