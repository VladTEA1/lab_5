#ifndef FIXED_STACK_H
#define FIXED_STACK_H

#include <memory_resource>
#include <iterator>
#include "fixed_memory_resource.h"

template<typename T>
class fixed_stack {
private:
    struct Node {
        T data;
        Node* next;
        
        template<typename... Args>
        Node(Args&&... args) : data(std::forward<Args>(args)...), next(nullptr) {}
    };
    
    Node* top_node;
    size_t stack_size;
    std::pmr::polymorphic_allocator<Node> allocator;

public:
    using value_type = T;
    
    class iterator {
    private:
        Node* current;
    
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
    
        iterator(Node* node = nullptr) : current(node) {}
    
        reference operator*() const { return current->data; }
        pointer operator->() const { return &current->data; }
    
        iterator& operator++() {
            current = current->next;
            return *this;
        }
    
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
    
        bool operator==(const iterator& other) const { return current == other.current; }
        bool operator!=(const iterator& other) const { return current != other.current; }
    };
    
    fixed_stack(std::pmr::memory_resource* mr = std::pmr::get_default_resource()) 
        : top_node(nullptr), stack_size(0), allocator(mr) {}
    
    ~fixed_stack() { clear(); }
    
    void push(const T& value) {
        Node* new_node = allocator.allocate(1);
        try {
            std::allocator_traits<decltype(allocator)>::construct(allocator, new_node, value);
        } catch (...) {
            allocator.deallocate(new_node, 1);
            throw;
        }
        new_node->next = top_node;
        top_node = new_node;
        ++stack_size;
    }
    
    template<typename... Args>
    void emplace(Args&&... args) {
        Node* new_node = allocator.allocate(1);
        try {
            std::allocator_traits<decltype(allocator)>::construct(allocator, new_node, std::forward<Args>(args)...);
        } catch (...) {
            allocator.deallocate(new_node, 1);
            throw;
        }
        new_node->next = top_node;
        top_node = new_node;
        ++stack_size;
    }
    
    void pop() {
        if (!top_node) return;
        
        Node* to_delete = top_node;
        top_node = top_node->next;
        std::allocator_traits<decltype(allocator)>::destroy(allocator, to_delete);
        allocator.deallocate(to_delete, 1);
        --stack_size;
    }
    
    T& top() { return top_node->data; }
    const T& top() const { return top_node->data; }
    
    bool empty() const { return top_node == nullptr; }
    size_t size() const { return stack_size; }
    
    void clear() {
        while (!empty()) {
            pop();
        }
    }
    
    iterator begin() { return iterator(top_node); }
    iterator end() { return iterator(nullptr); }
};

#endif