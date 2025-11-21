#ifndef MEMORY_RESOURCE_H
#define MEMORY_RESOURCE_H

#include <memory_resource>
#include <list>

class fixed_memory_pool : public std::pmr::memory_resource {
    char* pool;
    size_t total_size;
    size_t used;
    std::list<std::pair<void*, size_t>> active_blocks;
    
    struct free_chunk {
        char* start;
        size_t length;
    };
    std::list<free_chunk> free_list;

public:
    fixed_memory_pool(size_t pool_size);
    ~fixed_memory_pool();
    
    fixed_memory_pool(const fixed_memory_pool&) = delete;
    fixed_memory_pool& operator=(const fixed_memory_pool&) = delete;

private:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* ptr, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};

#endif