#include <gtest/gtest.h>
#include "../include/fixed_stack.h"
#include "../include/complex_type.h"
#include <vector>

class StackTest : public ::testing::Test {
protected:
    void SetUp() override {
        memory_pool = new fixed_memory_pool(2048);
    }
    
    void TearDown() override {
        delete memory_pool;
    }
    
    fixed_memory_pool* memory_pool;
};

TEST_F(StackTest, BasicIntegerOperations) {
    Stack<int> test_stack(memory_pool);
    
    EXPECT_TRUE(test_stack.empty());
    
    test_stack.push(100);
    test_stack.push(200);
    
    EXPECT_FALSE(test_stack.empty());
    EXPECT_EQ(test_stack.size(), 2);
    EXPECT_EQ(test_stack.top(), 200);
    
    test_stack.pop();
    EXPECT_EQ(test_stack.top(), 100);
}

TEST_F(StackTest, ComplexTypeTest) {
    Stack<DataStruct> test_stack(memory_pool);
    
    test_stack.push(DataStruct(1, "Тест1", 5.5));
    test_stack.emplace(2, "Тест2", 6.6);
    
    EXPECT_EQ(test_stack.size(), 2);
    EXPECT_EQ(test_stack.top().identifier, 2);
    EXPECT_EQ(test_stack.top().title, "Тест2");
}

TEST_F(StackTest, IteratorFunctionality) {
    Stack<int> test_stack(memory_pool);
    
    test_stack.push(1);
    test_stack.push(2);
    test_stack.push(3);
    
    std::vector<int> collected;
    for (auto it = test_stack.begin(); it != test_stack.end(); ++it) {
        collected.push_back(*it);
    }
    
    std::vector<int> expected = {3, 2, 1};
    EXPECT_EQ(collected, expected);
}

TEST_F(StackTest, MemoryReuseCheck) {
    Stack<int> test_stack(memory_pool);
    
    for (int i = 0; i < 10; i++) {
        test_stack.push(i);
    }
    
    size_t original_size = test_stack.size();
    test_stack.pop();
    test_stack.pop();
    
    test_stack.push(999);
    test_stack.push(888);
    
    EXPECT_EQ(test_stack.size(), original_size);
    EXPECT_EQ(test_stack.top(), 888);
}

TEST_F(StackTest, ClearStack) {
    Stack<std::string> test_stack(memory_pool);
    
    test_stack.push("abc");
    test_stack.push("def");
    
    EXPECT_FALSE(test_stack.empty());
    test_stack.clear();
    EXPECT_TRUE(test_stack.empty());
}