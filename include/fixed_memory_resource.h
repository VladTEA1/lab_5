#ifndef FIXED_MEMORY_RESOURCE_H
#define FIXED_MEMORY_RESOURCE_H

#include <memory_resource>
#include <list>
#include <cstddef>
#include <utility>

class fixed_memory_resource : public std::pmr::memory_resource {
private:
    void* storage_area;
    std::size_t total_capacity;
    std::size_t current_usage;
    std::list<std::pair<void*, std::size_t>> active_allocations;
    
    struct available_region {
        void* start_position;
        std::size_t region_size;
    };
    std::list<available_region> available_regions;

public:
    explicit fixed_memory_resource(std::size_t capacity);
    ~fixed_memory_resource() override;

    fixed_memory_resource(const fixed_memory_resource&) = delete;
    fixed_memory_resource& operator=(const fixed_memory_resource&) = delete;

protected:
    void* do_allocate(std::size_t requested_size, std::size_t alignment_requirement) override;
    void do_deallocate(void* target_address, std::size_t block_size, std::size_t alignment_requirement) override;
    bool do_is_equal(const std::pmr::memory_resource& other_instance) const noexcept override;
};

#endif
