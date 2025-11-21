cmake_minimum_required(VERSION 3.10)
project(StackLab)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)


add_executable(stack_demo 
    src/main.cpp 
    src/fixed_memory_resource.cpp
)
target_include_directories(stack_demo PRIVATE include)


add_executable(stack_test 
    tests/test_main.cpp 
    src/fixed_memory_resource.cpp
)
target_include_directories(stack_test PRIVATE include)
target_link_libraries(stack_test gtest_main)

enable_testing()
add_test(NAME stack_test COMMAND stack_test)