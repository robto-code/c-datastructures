#include "gtest/gtest.h"

extern "C" 
{
    #include "stack.h"
}

class StackTest : public ::testing::Test { 
    protected:
        void SetUp() override {
            mystack = stack_create();
            temp = node_create(sizeof(int), NULL);
            int vvals[] = {-3, -2, -1, 0, 1, 2, 3};
            for (int i = 0; i < 7; i++)
            {
                v[i] = vvals[i];
            }
        }
        void TearDown() override {
            stack_destroy(mystack);
        }
        Stack* mystack;
        Node* temp;
        int v[7];
};

TEST_F(StackTest, create)
{
    EXPECT_EQ(mystack->head, nullptr);
    EXPECT_EQ(mystack->length, 0);
}

TEST_F(StackTest, push)
{
    for (int i = 0; i < 3; i++)
    {
        NODE_EMPLACE(temp, v[i], NULL);
        stack_push(mystack, temp);
    }

    EXPECT_EQ(mystack->head, temp);
    EXPECT_EQ(mystack->length, 3);
}

TEST_F(StackTest, pop) 
{
    for (int i = 0; i < 3; i++)
    {
        NODE_EMPLACE(temp, v[i], NULL);
        stack_push(mystack, temp);
    }
    temp = stack_pop(mystack);
    EXPECT_EQ(*NODE_READ(temp, int), -1);
    for (int i = 3; i < 7; i++)
    {
        NODE_EMPLACE(temp, v[i], NULL);
        stack_push(mystack, temp);
        EXPECT_EQ(*NODE_READ((mystack->head), int), v[i]);
    }
    int newv[] = {-3, -2, 0, 1, 2, 3};
    for (int i = 5; i >= 4; i--)
    {
        temp = stack_pop(mystack);
        EXPECT_EQ(*NODE_READ(temp, int), newv[i]);
        EXPECT_EQ(mystack->length, i);
    }
}


TEST_F(StackTest, isempty)
{
    EXPECT_NE(stack_isempty(mystack), 0);
    NODE_EMPLACE(temp, v[0], NULL);
    stack_push(mystack, temp);
    EXPECT_EQ(stack_isempty(mystack), 0);
    temp = stack_pop(mystack);
    EXPECT_NE(stack_isempty(mystack), 0);
}

TEST_F(StackTest, size)
{
    EXPECT_EQ(stack_size(mystack), 0);
    NODE_EMPLACE(temp, v[0], NULL);
    stack_push(mystack, temp);
    EXPECT_EQ(stack_size(mystack), 1);
    for(int i = 1; i < 4; i++)
    {
        NODE_EMPLACE(temp, v[i], NULL);
        stack_push(mystack, temp);
        EXPECT_EQ(stack_size(mystack), i+1);
    }
    for(int i = 3; i >= 0; i--)
    {
        temp = stack_pop(mystack);
        EXPECT_EQ(stack_size(mystack), i);
    }
}

TEST_F(StackTest, peek)
{
    struct Node* prev;
    EXPECT_EQ(stack_peek(mystack), nullptr);
    for(int i = 0; i < 7; i++)
    {
        NODE_EMPLACE(temp, v[i], NULL);
        stack_push(mystack, temp);
        EXPECT_EQ(stack_peek(mystack), temp);
    }

    for(int i = 6; i >= 0; i--)
    {
        prev = (stack_peek(mystack))->next;
        temp = stack_pop(mystack);
        EXPECT_EQ(stack_peek(mystack), prev);
    }
}

