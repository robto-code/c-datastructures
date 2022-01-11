#include "gtest/gtest.h"
#include <experimental/random>

extern "C"
{ 
    #include "ringbuffer.h" 
}

TEST(RBCreate, nocapchange)
{
    RingBuffer *ring = RB_create(sizeof(int), 16u);
    ASSERT_NE(ring, nullptr);
    EXPECT_EQ(ring->capacity, 16u);
    EXPECT_EQ(ring->esize, sizeof(int));
    EXPECT_EQ(ring->start, 0u);
    EXPECT_EQ(ring->end, 0u);
    RB_destroy(ring);
}

TEST(RBCreate, capchange)
{
    RingBuffer *ring = RB_create(sizeof(int), 28u);
    ASSERT_NE(ring, nullptr);
    EXPECT_EQ(ring->capacity, 32u);
    EXPECT_EQ(ring->esize, sizeof(int));
    EXPECT_EQ(ring->start, 0u);
    EXPECT_EQ(ring->end, 0u);
    RB_destroy(ring);
}

TEST(RBNoOverwrite, basic)
{
    RingBuffer *ring = RB_create(sizeof(int), 14);
    DataRead *reader = (DataRead*) malloc(sizeof(DataRead));
    reader->index = 0u;
    ASSERT_NE(ring, nullptr);
    int values[] = {1, 2, 3};
    RB_WRITE(ring, values[0]);
    RB_WRITE(ring, values[1]);
    RB_WRITE(ring, values[2]);
    EXPECT_EQ(RB_writeSpace(ring), 13u);
    EXPECT_EQ(RB_readSpace(ring, reader), 3u);
    auto a = RB_READ(ring, reader, int);
    auto b = RB_READ(ring, reader, int);
    auto c = RB_READ(ring, reader, int);
    EXPECT_EQ(*a, 1);
    EXPECT_EQ(*b, 2);
    EXPECT_EQ(*c, 3);
    RB_postInc(ring, 3);
    EXPECT_EQ(RB_writeSpace(ring), 16u);
    EXPECT_EQ(RB_readSpace(ring, reader), 0u);
    RB_destroy(ring);
    free(reader);
}

TEST(RBNoOverwrite, full)
{
    RingBuffer *ring = RB_create(sizeof(int), 16);
    DataRead *reader = (DataRead*) malloc(sizeof(DataRead));
    reader->index = 0u; 
    ASSERT_NE(ring, nullptr);

    int vals[] = {-7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
    for (int i = 0; i < 16; i++)
    {
        RB_WRITE(ring, vals[i]);
    }
    EXPECT_EQ(RB_writeSpace(ring), 0u);
    EXPECT_EQ(RB_readSpace(ring, reader), 16u);
    int i = 0;
    while (RB_readSpace(ring, reader) > 0)
    {
        EXPECT_EQ(*RB_READ(ring, reader, int), vals[i++]);
        RB_post(ring);
    }
    EXPECT_EQ(RB_writeSpace(ring), 16u);
    RB_destroy(ring);
    free(reader);
}
TEST(RBOverwrite, Rube)
{

    const char* DieRube = "Es waren einmal zwei Bruder, die dienten"
                           "beide als Soldaten, und war der eine reich," 
                           "der andere arm. Da wollte der Arme sich aus"
                           "seiner Not helfen, zog den Soldatenrock aus und" 
                           "ward ein Bauer. Also grub und hackte er sein Stuckchen"
                           "Acker und sate Rubsamen. Der Same ginf auf, und es wuchs"
                           "da eine Rube, die ward gross und stark und zusehends"
                           "dicker und wollte gar nicht aufhoren zu wachsen, so dass" 
                           "sie eien Furstin aller Ruben heissen konnte.";
    for (int repeat = 0; repeat < 10000; repeat++) { 
    RingBuffer *ring = RB_create(sizeof(char), 32);
    DataRead *reader = (DataRead *) malloc(sizeof(DataRead));
    reader->index = 0u;
    ASSERT_NE(ring, nullptr);

    int ri = 0; // read index
    int wi = 0; // write index
    while (DieRube[ri] != '\0')
    {
        int max = RB_writeSpace(ring) < 6 ? RB_writeSpace(ring) : 6;
        int writeamt = std::experimental::randint(1, max);
        for (int j = 0; j < writeamt; j++)  { RB_WRITE(ring, DieRube[wi++]); }
        max = RB_readSpace(ring, reader) < 6 ? RB_readSpace(ring, reader) : 6;
        int readamt = std::experimental::randint(1, max);
        for (int j = 0; j < readamt; j++) { EXPECT_EQ(*RB_READ(ring, reader, char), DieRube[ri++]); }
        RB_postInc(ring, readamt);
    }
    while (RB_readSpace(ring, reader) > 0)
    {
        EXPECT_EQ(*RB_READ(ring, reader, char), DieRube[ri++]);
        RB_post(ring);
    }
    RB_destroy(ring);
    free(reader); 
    }
}


