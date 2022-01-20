#include "gtest/gtest.h"

extern "C" 
{
    #include "dnode.h"
}

class DnodeTest : public ::testing::Test {
    protected:
        void SetUp() override {
            n = dnode_create(sizeof(int), NULL, NULL);
            newn = dnode_create(sizeof(int), n, NULL);
            n->prev = newn;
            a = 10;
            b = -15; 
        }
        void TearDown() override {
            dnode_destroy(n);
            dnode_destroy(newn);
        }
        int a, b;
        Dnode* n;
        Dnode* newn;
};

TEST_F(DnodeTest, create)
{
    ASSERT_NE(n, nullptr);
    ASSERT_NE(newn, nullptr);
    EXPECT_EQ(newn->next, n);
    EXPECT_EQ(n->next, nullptr);
    EXPECT_EQ(n->prev, newn);
    EXPECT_EQ(newn->prev, nullptr);
}

TEST_F(DnodeTest, WRITE_READ)
{
    DNODE_WRITE(n, a);
    EXPECT_EQ(*DNODE_READ(n, int), 10);
       
    DNODE_WRITE(n, b);
    EXPECT_EQ(*DNODE_READ(n, int), -15);

    DNODE_WRITE(newn, a);
    EXPECT_EQ(*DNODE_READ(newn, int), 10);
    EXPECT_EQ(*DNODE_READ(newn->next, int), -15);

    EXPECT_EQ(*DNODE_READ(n->prev, int), 10);
}


TEST_F(DnodeTest, READCOPY)
{
    int data;

    DNODE_WRITE(n, a);
    DNODE_READCOPY(n, data);
    EXPECT_EQ(data, 10);

    data = 27;
    DNODE_WRITE(n, b);
    DNODE_READCOPY(n, data);
    EXPECT_EQ(data, -15);
}

TEST_F(DnodeTest, EMPLACE1)
{
    int v = 15;
    DNODE_EMPLACE(n, v, NULL, NULL);

    ASSERT_NE(n, nullptr);
    EXPECT_EQ(n->next, nullptr);
    EXPECT_EQ(n->prev, nullptr);
    EXPECT_EQ(*DNODE_READ(n, int), v);
}

TEST_F(DnodeTest, EMPLACE2)
{
    char v = 'c';
    Dnode *nextnode = dnode_create(sizeof(char), NULL, NULL);

    DNODE_EMPLACE(n, v, nextnode, NULL);
    nextnode->prev = n;

    EXPECT_EQ(n->next, nextnode);
    EXPECT_EQ(nextnode->prev, n);
    EXPECT_EQ(*DNODE_READ(n, char), v);

    dnode_destroy(nextnode);
}

TEST_F(DnodeTest, insert)
{
    Dnode *newnode = dnode_create(sizeof(int), NULL, NULL);
    Dnode *headnode = dnode_create(sizeof(int), NULL, NULL);

    dnode_insert(newnode, newn, n);

    EXPECT_EQ(newnode->prev, newn);
    EXPECT_EQ(newn->next, newnode);
    EXPECT_EQ(newnode->next, n);
    EXPECT_EQ(n->prev, newnode);

    dnode_insert(headnode, NULL, newn);

    EXPECT_EQ(headnode->prev, nullptr);
    EXPECT_EQ(headnode->next, newn);
    EXPECT_EQ(newn->prev, headnode);
    EXPECT_EQ(newn->next, newnode);

    dnode_destroy(newnode);
    dnode_destroy(headnode);
}

TEST_F(DnodeTest, remove)
{
    Dnode *head = dnode_create(sizeof(int), NULL, NULL);
    Dnode *tail = dnode_create(sizeof(int), NULL, NULL);

    dnode_insert(head, newn->prev, newn);
    dnode_insert(tail, n, n->next);
    
    Dnode *temp = dnode_remove(n);

    EXPECT_EQ(temp, n);
    EXPECT_EQ(tail->prev, newn);
    EXPECT_EQ(newn->next, tail);
    EXPECT_EQ(tail->next, nullptr);
    EXPECT_EQ(newn->prev, head);

    temp = dnode_remove(head);

    EXPECT_EQ(temp, head);
    EXPECT_EQ(newn->prev, nullptr);
    EXPECT_EQ(newn->next, tail);
}

