#include <iostream>
#include "fixed_stack.h"
#include "complex_type.h"

void demonstrate_int_stack() {
    std::cout << "=== Demonstrating int stack ===\n";
    
    fixed_memory_resource mr(512);
    fixed_stack<int> stack(&mr);
    
    for (int i = 1; i <= 5; ++i) {
        stack.push(i * 10);
        std::cout << "Pushed: " << i * 10 << std::endl;
    }
    
    std::cout << "Stack contents (using iterator): ";
    for (auto it = stack.begin(); it != stack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Stack contents (range-based for): ";
    for (const auto& item : stack) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    while (!stack.empty()) {
        std::cout << "Popped: " << stack.top() << std::endl;
        stack.pop();
    }
}

void demonstrate_complex_type_stack() {
    std::cout << "\n=== Demonstrating ComplexType stack ===\n";
    
    fixed_memory_resource mr(1024);
    fixed_stack<ComplexType> stack(&mr);
    
    stack.push(ComplexType(1, "Alice", 95.5));
    stack.emplace(2, "Bob", 88.3);
    stack.emplace(3, "Charlie", 91.7);
    
    std::cout << "Stack contents:\n";
    for (const auto& item : stack) {
        std::cout << "  " << item << std::endl;
    }
    
    std::cout << "Top element: " << stack.top() << std::endl;
    stack.pop();
    std::cout << "After pop, top element: " << stack.top() << std::endl;
}

int main() {
    try {
        demonstrate_int_stack();
        demonstrate_complex_type_stack();
        
        std::cout << "\n=== All demonstrations completed successfully ===\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}