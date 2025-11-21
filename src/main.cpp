#include <iostream>
#include "fixed_stack.h"
#include "complex_type.h"

void test_integer_stack() {
    std::cout << "Тестирование стека с целыми числами\n";
    
    fixed_memory_pool pool(512);
    Stack<int> numbers(&pool);
    
    for (int i = 1; i <= 5; i++) {
        numbers.push(i * 10);
        std::cout << "Добавлено: " << i * 10 << "\n";
    }
    
    std::cout << "Содержимое через итератор: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    std::cout << "Содержимое через for: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";
    
    while (!numbers.empty()) {
        std::cout << "Удалено: " << numbers.top() << "\n";
        numbers.pop();
    }
}

void test_complex_stack() {
    std::cout << "\nТестирование стека со структурой\n";
    
    fixed_memory_pool pool(1024);
    Stack<DataStruct> items(&pool);
    
    items.push(DataStruct(1, "Первый", 10.5));
    items.emplace(2, "Второй", 20.8);
    items.emplace(3, "Третий", 30.2);
    
    std::cout << "Содержимое стека:\n";
    for (const auto& item : items) {
        std::cout << "  ID: " << item.identifier << ", Название: " << item.title 
                  << ", Значение: " << item.numerical_value << "\n";
    }
    
    std::cout << "Верхний элемент: " << items.top().title << "\n";
    items.pop();
    std::cout << "После удаления: " << items.top().title << "\n";
}

int main() {
    try {
        test_integer_stack();
        test_complex_stack();
        
        std::cout << "\nВсе тесты завершены успешно\n";
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}