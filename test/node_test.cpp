#include "gtest/gtest.h"

extern "C"
{
    #include "node.h"
}

class NodeTest : public ::testing::Test {
    protected: 
        void SetUp() override {
            n = node_create(sizeof(int), NULL);
            newn = node_create(sizeof(int), n);
            a = 10;
            b = -15;
        }
        void TearDown() override {
            node_destroy(n);
            node_destroy(newn);
        }
        int a, b;
        Node* n;
        Node* newn;
};

TEST_F(NodeTest, create)
{
    ASSERT_NE(n, nullptr);
    ASSERT_NE(newn, nullptr);
    EXPECT_EQ(newn->next, n);
    EXPECT_EQ(n->next, nullptr);
}

TEST_F(NodeTest, WRITE_READ)
{
    NODE_WRITE(n, a);
    EXPECT_EQ(*NODE_READ(n, int), 10);
       
    NODE_WRITE(n, b);
    EXPECT_EQ(*NODE_READ(n, int), -15);

    NODE_WRITE(newn, a);
    EXPECT_EQ(*NODE_READ(newn, int), 10);
    EXPECT_EQ(*NODE_READ(newn->next, int), -15);
}


TEST_F(NodeTest, READCOPY)
{
    int data;

    NODE_WRITE(n, a);
    NODE_READCOPY(n, data);
    EXPECT_EQ(data, 10);

    data = 27;
    NODE_WRITE(n, b);
    NODE_READCOPY(n, data);
    EXPECT_EQ(data, -15);
}

TEST_F(NodeTest, EMPLACE1)
{
    int v = 15;
    NODE_EMPLACE(n, v, NULL);

    EXPECT_EQ(n->next, nullptr);
    EXPECT_EQ(*NODE_READ(n, int), v);
}

TEST_F(NodeTest, EMPLACE2)
{
    char v = 'c';
    Node *nextnode = node_create(sizeof(char), NULL);

    NODE_EMPLACE(n, v, nextnode);

    EXPECT_EQ(n->next, nextnode);
    EXPECT_EQ(*NODE_READ(n, char), v);

    node_destroy(nextnode);
}
