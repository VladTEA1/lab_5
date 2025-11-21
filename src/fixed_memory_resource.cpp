#include "fixed_memory_resource.h"
#include <algorithm>

fixed_memory_pool::fixed_memory_pool(size_t pool_size) 
    : total_size(pool_size), used(0) {
    pool = static_cast<char*>(::operator new(pool_size));
}

fixed_memory_pool::~fixed_memory_pool() {
    for (const auto& block : active_blocks) {
        ::operator delete(block.first, block.second);
    }
    active_blocks.clear();
    ::operator delete(pool);
}

void* fixed_memory_pool::do_allocate(size_t bytes, size_t alignment) {
    auto it = std::find_if(free_list.begin(), free_list.end(),
        [bytes](const free_chunk& chunk) { return chunk.length >= bytes; });
    
    if (it != free_list.end()) {
        void* block_ptr = it->start;
        if (it->length > bytes) {
            free_list.push_back({it->start + bytes, it->length - bytes});
        }
        free_list.erase(it);
        active_blocks.emplace_back(block_ptr, bytes);
        return block_ptr;
    }
    
    if (used + bytes > total_size) {
        throw std::bad_alloc();
    }
    
    void* block_ptr = pool + used;
    used += bytes;
    active_blocks.emplace_back(block_ptr, bytes);
    return block_ptr;
}

void fixed_memory_pool::do_deallocate(void* ptr, size_t bytes, size_t alignment) {
    auto it = std::find_if(active_blocks.begin(), active_blocks.end(),
        [ptr](const auto& block) { return block.first == ptr; });
    
    if (it != active_blocks.end()) {
        active_blocks.erase(it);
        free_list.push_back({static_cast<char*>(ptr), bytes});
    }
}

bool fixed_memory_pool::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}