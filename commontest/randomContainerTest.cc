#include "gtest/gtest.h"
#include "common/randomContainer.h"

class Entity : public CoW::RandomContainerElem 
{
public:
	Entity(int d) : data(d) {}
	int data;
};

class randomContainerTest : public ::testing::Test 
{
protected:
	randomContainerTest() : e1(1), e2(2), e3(3) {}
	Entity e1;
	Entity e2;
	Entity e3;
	CoW::RandomContainer<Entity> theContainer;
};

TEST_F(randomContainerTest, pushOnePop)
{
    theContainer.push(e1);
    auto& r1 = theContainer.pop();

    ASSERT_EQ(&e1, &r1);
    ASSERT_TRUE(theContainer.empty());
}

TEST_F(randomContainerTest, pushThreePopThree)
{
    theContainer.push(e1);
    theContainer.push(e2);
    theContainer.push(e3);

    int count = 0;
    while (!theContainer.empty())
    {   
        auto& r1 = theContainer.pop();
        ++count;
        ASSERT_TRUE(&r1 == &e1 || &r1 == &e2 || &r1 == &e3);
    }

    ASSERT_EQ(count, 3);
}