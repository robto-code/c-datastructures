#include "gtest/gtest.h"

extern "C" 
{
    #include "stack.h"
    #include "node.h"
}

class StackTest : public ::testing::Test { 
    protected:
        void SetUp() override {
            mystack = Stack_create();
            int vvals[] = {-3, -2, -1, 0, 1, 2, 3};
            for (int i = 0; i < 7; i++)
            {
                v[i] = vvals[i];
            }
        }
        /*
        void TearDown() override {
            STACK_DESTROY(mystack, Node_destroy);
        }
        */
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
        STACK_PUSH(mystack, temp);
    }

    EXPECT_EQ(mystack->head, temp);
    EXPECT_EQ(mystack->length, 3);
}

TEST_F(StackTest, pop) 
{
    for (int i = 0; i < 3; i++)
    {
        NODE_EMPLACE(temp, v[i], NULL);
        STACK_PUSH(mystack, temp);
    }
    STACK_POP(mystack, temp);
    EXPECT_EQ(*NODE_READ(temp, int), -1);
    for (int i = 3; i < 7; i++)
    {
        NODE_EMPLACE(temp, v[i], NULL);
        STACK_PUSH(mystack, temp);
    }
    int newv[] = {-3, -2, 0, 1, 2, 3};
    for (int i = 0; i < 6; i++)
    {
        STACK_POP(mystack, temp);
        EXPECT_EQ(*NODE_READ(temp, int), newv[5 - i]);
        EXPECT_EQ(mystack->length, 5 - i);
    }
}


TEST_F(StackTest, isempty)
{
    EXPECT_NE(Stack_isempty(mystack), 0);
    NODE_EMPLACE(temp, v[0], NULL);
    STACK_PUSH(mystack, temp);
    EXPECT_EQ(Stack_isempty(mystack), 0);
    STACK_POP(mystack, temp);
    EXPECT_NE(Stack_isempty(mystack), 0);
}

TEST_F(StackTest, size)
{
    EXPECT_EQ(Stack_size(mystack), 0);
    NODE_EMPLACE(temp, v[0], NULL);
    STACK_PUSH(mystack, temp);
    EXPECT_EQ(Stack_size(mystack), 1);
    for(int i = 1; i < 4; i++)
    {
        NODE_WRITE(temp, v[i]);
        STACK_PUSH(mystack, temp);
        EXPECT_EQ(Stack_size(mystack), i+1);
    }
    for(int i = 3; i >= 0; i--)
    {
        STACK_POP(mystack, temp);
        EXPECT_EQ(Stack_size(mystack), i);
    }
}

TEST_F(StackTest, peek)
{
    EXPECT_EQ(STACK_PEEK(mystack), nullptr);
    temp = Node_create(sizeof(int), NULL);
    for(int i = 0; i < 7; i++)
    {
        NODE_WRITE(temp, v[i]);
        STACK_PUSH(mystack, temp);
        EXPECT_EQ(STACK_PEEK(mystack), temp);
    }

    for(int i = 6; i >= 0; i--)
    {
        STACK_POP(mystack, temp);
        EXPECT_EQ(STACK_PEEK(mystack), temp->next);
    }
}

