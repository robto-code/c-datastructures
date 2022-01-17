#include "gtest/gtest.h"

extern "C"
{
    #include "node.h"
}

TEST(NODE_CREATE, next)
{
    Node *n = Node_create(sizeof(int), NULL);

    Node *newn = Node_create(sizeof(int), n);

    EXPECT_EQ(newn->next, n);
}

TEST(NODE_WRITEREAD, Overwrite)
{
    Node* n = Node_create(sizeof(int), NULL);

    int a = 10;
    int b = -15;

    NODE_WRITE(n, a);
    EXPECT_EQ(*NODE_READ(n, int), 10);
    
    NODE_WRITE(n, b);
    EXPECT_EQ(*NODE_READ(n, int), -15);

    Node_destroy(n);
}


TEST(NODE_READCOPY, Overwrite)
{
    Node* n = Node_create(sizeof(int), NULL);
    int data;

    int a = 10;
    int b = -15;

    NODE_WRITE(n, a);
    NODE_READCOPY(n, data);
    EXPECT_EQ(data, 10);

    data = 27;
    NODE_WRITE(n, b);
    NODE_READCOPY(n, data);
    EXPECT_EQ(data, -15);

    Node_destroy(n);
}

TEST(NODE_EMPLACE, nonext)
{
    int v = 15;
    Node* n;

    NODE_EMPLACE(n, v, NULL);

    EXPECT_EQ(n->next, nullptr);
    EXPECT_EQ(*NODE_READ(n, int), v);

    Node_destroy(n);
}

TEST(NODE_EMPLACE, next)
{
    char v = 'c';
    Node *n;
    Node *nextnode = Node_create(sizeof(char), NULL);

    NODE_EMPLACE(n, v, nextnode);

    EXPECT_EQ(n->next, nextnode);
    EXPECT_EQ(*NODE_READ(n, char), v);

    Node_destroy(n);
    Node_destroy(nextnode);
}
