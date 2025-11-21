#include <gtest/gtest.h>
#include "../include/fixed_stack.h"
#include "../include/complex_type.h"
#include <vector>
#include <algorithm>

class FixedStackTest : public ::testing::Test {
protected:
    void SetUp() override {
        mr = new fixed_memory_resource(1024);
    }
    
    void TearDown() override {
        delete mr;
    }
    
    fixed_memory_resource* mr;
};

TEST_F(FixedStackTest, IntStackBasicOperations) {
    fixed_stack<int> stack(mr);
    
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
    
    stack.push(1);
    stack.push(2);
    stack.push(3);
    
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.top(), 3);
    
    stack.pop();
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 2);
    
    stack.pop();
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST_F(FixedStackTest, ComplexTypeStack) {
    fixed_stack<ComplexType> stack(mr);
    
    stack.push(ComplexType(1, "first", 1.1));
    stack.emplace(2, "second", 2.2);
    stack.emplace(3, "third", 3.3);
    
    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.top().id, 3);
    EXPECT_EQ(stack.top().name, "third");
    
    stack.pop();
    EXPECT_EQ(stack.top().id, 2);
}

TEST_F(FixedStackTest, IteratorTest) {
    fixed_stack<int> stack(mr);
    std::vector<int> expected = {3, 2, 1};
    
    stack.push(1);
    stack.push(2);
    stack.push(3);
    
    std::vector<int> result;
    for (auto it = stack.begin(); it != stack.end(); ++it) {
        result.push_back(*it);
    }
    
    EXPECT_EQ(result, expected);
}

TEST_F(FixedStackTest, RangeBasedForLoop) {
    fixed_stack<int> stack(mr);
    
    stack.push(10);
    stack.push(20);
    stack.push(30);
    
    int sum = 0;
    for (const auto& item : stack) {
        sum += item;
    }
    
    EXPECT_EQ(sum, 60);
}

TEST_F(FixedStackTest, MemoryReuse) {
    fixed_stack<int> stack(mr);
    
    for (int i = 0; i < 5; ++i) {
        stack.push(i);
    }
    
    size_t initial_size = stack.size();
    stack.pop();
    stack.pop();
    
    stack.push(100);
    stack.push(200);
    
    EXPECT_EQ(stack.size(), initial_size - 2 + 2);
    EXPECT_EQ(stack.top(), 200);
}

TEST_F(FixedStackTest, ClearTest) {
    fixed_stack<std::string> stack(mr);
    
    stack.push("hello");
    stack.push("world");
    stack.push("test");
    
    EXPECT_FALSE(stack.empty());
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

TEST_F(FixedStackTest, STLAlgorithms) {
    fixed_stack<int> stack(mr);
    
    stack.push(1);
    stack.push(3);
    stack.push(2);
    stack.push(5);
    stack.push(4);
    
    auto it = std::find(stack.begin(), stack.end(), 3);
    EXPECT_NE(it, stack.end());
    EXPECT_EQ(*it, 3);
    
    int count = std::count_if(stack.begin(), stack.end(), 
                             [](int x) { return x % 2 == 0; });
    EXPECT_EQ(count, 2);
}










