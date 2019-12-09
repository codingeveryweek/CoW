#include "gtest/gtest.h"
#include "common/inPlaceList.h"

class Entity : public CoW::InPlaceListElem 
{
public:
	Entity(int d) : data(d) {}
	int data;
};

class inPlaceListTest : public ::testing::Test 
{
protected:
	inPlaceListTest() : e1(1), e2(2), e3(3) {}
	Entity e1;
	Entity e2;
	Entity e3;
	CoW::InPlaceList<Entity> theList;
};

TEST_F(inPlaceListTest, StartEmpty)
{
	ASSERT_TRUE(theList.empty());
}

TEST_F(inPlaceListTest, PushFrontNotEmpty)
{
	theList.push_front(e1);
	ASSERT_FALSE(theList.empty());
}

TEST_F(inPlaceListTest, PushBackNotEmpty)
{
	theList.push_back(e1);
	ASSERT_FALSE(theList.empty());
}

TEST_F(inPlaceListTest, PushFrontGetFront)
{
	theList.push_front(e1);
	Entity& r1 = theList.front();
	ASSERT_EQ(&r1, &e1);
}

TEST_F(inPlaceListTest, PushFrontGetBack)
{
	theList.push_front(e1);
	Entity& r1 = theList.back();
	ASSERT_EQ(&r1, &e1);
}

TEST_F(inPlaceListTest, PushFrontPopFrontEmpty)
{
	theList.push_front(e1);
	theList.pop_front();
	ASSERT_TRUE(theList.empty());
}

TEST_F(inPlaceListTest, PushBackPopFrontEmpty)
{
	theList.push_back(e1);
	theList.pop_front();
	ASSERT_TRUE(theList.empty());
}

TEST_F(inPlaceListTest, PushFront2GetBack)
{
	theList.push_front(e1);
	theList.push_front(e2);
	Entity& r1 = theList.back();
	ASSERT_EQ(&r1, &e1);
}

TEST_F(inPlaceListTest, PushFrontBackFrontPopGetBack)
{
	theList.push_back(e1);
	theList.push_front(e2);
	theList.push_back(e3);
	theList.pop_front();
	Entity& r1 = theList.back();
	ASSERT_EQ(&r1, &e3);
	Entity& r2 = theList.front();
	ASSERT_EQ(&r2, &e1);
}

TEST_F(inPlaceListTest, Iter)
{
	theList.push_back(e1);
	theList.push_back(e2);
	theList.push_back(e3);

	auto iter = theList.begin();
	Entity& r1 = *iter;
	ASSERT_EQ(&r1, &e1);

	++iter;
	Entity& r2 = *iter;
	ASSERT_EQ(&r2, &e2);

	++iter;
	Entity& r3 = *iter;
	ASSERT_EQ(&r3, &e3);

	++iter;
	ASSERT_EQ(iter, theList.end());
}
