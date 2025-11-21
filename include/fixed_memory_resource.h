#ifndef FIXED_MEMORY_RESOURCE_H
#define FIXED_MEMORY_RESOURCE_H

#include <memory_resource>
#include <list>
#include <cstddef>
#include <utility>

class fixed_memory_resource : public std::pmr::memory_resource {
private:
    void* memory_pool;
    size_t pool_size;
    size_t used_memory;
    std::list<std::pair<void*, size_t>> allocated_blocks;
    
    struct free_block {
        void* ptr;
        size_t size;
    };
    std::list<free_block> free_blocks;

public:
    fixed_memory_resource(size_t size);
    ~fixed_memory_resource() override;

    fixed_memory_resource(const fixed_memory_resource&) = delete;
    fixed_memory_resource& operator=(const fixed_memory_resource&) = delete;

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};

#endif