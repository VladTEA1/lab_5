#ifndef FIXED_STACK_H
#define FIXED_STACK_H

#include "fixed_memory_resource.h"
#include <memory_resource>

template<typename T>
class Stack {
    struct Node {
        T value;
        Node* next;
        
        template<typename... Args>
        Node(Args&&... args) : value(std::forward<Args>(args)...), next(nullptr) {}
    };
    
    Node* top_element;
    size_t count;
    std::pmr::polymorphic_allocator<Node> alloc;

public:
    class Iterator {
        Node* current;
    
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
    
        Iterator(Node* node = nullptr) : current(node) {}
        
        reference operator*() const { return current->value; }
        pointer operator->() const { return &current->value; }
        
        Iterator& operator++() {
            current = current->next;
            return *this;
        }
        
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };
    
    Stack(std::pmr::memory_resource* mr = std::pmr::get_default_resource()) 
        : top_element(nullptr), count(0), alloc(mr) {}
    
    ~Stack() { clear(); }
    
    void push(const T& val) {
        Node* new_node = alloc.allocate(1);
        try {
            std::allocator_traits<decltype(alloc)>::construct(alloc, new_node, val);
        } catch (...) {
            alloc.deallocate(new_node, 1);
            throw;
        }
        new_node->next = top_element;
        top_element = new_node;
        count++;
    }
    
    template<typename... Args>
    void emplace(Args&&... args) {
        Node* new_node = alloc.allocate(1);
        try {
            std::allocator_traits<decltype(alloc)>::construct(alloc, new_node, std::forward<Args>(args)...);
        } catch (...) {
            alloc.deallocate(new_node, 1);
            throw;
        }
        new_node->next = top_element;
        top_element = new_node;
        count++;
    }
    
    void pop() {
        if (!top_element) return;
        
        Node* old_top = top_element;
        top_element = top_element->next;
        std::allocator_traits<decltype(alloc)>::destroy(alloc, old_top);
        alloc.deallocate(old_top, 1);
        count--;
    }
    
    T& top() { return top_element->value; }
    const T& top() const { return top_element->value; }
    
    bool empty() const { return top_element == nullptr; }
    size_t size() const { return count; }
    
    void clear() {
        while (!empty()) {
            pop();
        }
    }
    
    Iterator begin() { return Iterator(top_element); }
    Iterator end() { return Iterator(nullptr); }
};

#endif