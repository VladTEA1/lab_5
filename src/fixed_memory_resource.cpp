#include "fixed_memory_resource.h"
#include <iostream>
#include <algorithm>
#include <cstring>

fixed_memory_resource::fixed_memory_resource(size_t size) 
    : pool_size(size), used_memory(0) {
    memory_pool = ::operator new(size);
}

fixed_memory_resource::~fixed_memory_resource() {
    for (const auto& block : allocated_blocks) {
        ::operator delete(block.first, block.second);
    }
    allocated_blocks.clear();
    ::operator delete(memory_pool);
}

void* fixed_memory_resource::do_allocate(size_t bytes, size_t alignment) {
    auto it = std::find_if(free_blocks.begin(), free_blocks.end(),
        [bytes](const free_block& fb) { return fb.size >= bytes; });
    
    if (it != free_blocks.end()) {
        void* ptr = it->ptr;
        if (it->size > bytes) {
            free_blocks.push_back({static_cast<char*>(ptr) + bytes, it->size - bytes});
        }
        free_blocks.erase(it);
        allocated_blocks.emplace_back(ptr, bytes);
        return ptr;
    }
    
    if (used_memory + bytes > pool_size) {
        throw std::bad_alloc();
    }
    
    void* ptr = static_cast<char*>(memory_pool) + used_memory;
    used_memory += bytes;
    allocated_blocks.emplace_back(ptr, bytes);
    return ptr;
}

void fixed_memory_resource::do_deallocate(void* p, size_t bytes, size_t alignment) {
    auto it = std::find_if(allocated_blocks.begin(), allocated_blocks.end(),
        [p](const auto& block) { return block.first == p; });
    
    if (it != allocated_blocks.end()) {
        allocated_blocks.erase(it);
        free_blocks.push_back({p, bytes});
    }
}

bool fixed_memory_resource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}