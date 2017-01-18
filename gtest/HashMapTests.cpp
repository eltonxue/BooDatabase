// HashMapTests.cpp
//
// ICS 45C Fall 2016
// Project #3: Maps and Legends
//
// Write unit tests for your HashMap class here.  I've provided one test already,
// though I've commented it out, because it won't compile until you've implemented
// three things: the HashMap constructor, the HashMap destructor, and HashMap's
// size() member function.

#include <gtest/gtest.h>
#include "HashMap.hpp"


TEST(TestHashMap, sizeOfNewlyCreatedHashMapIsZero)
{
    HashMap empty;
    ASSERT_EQ(0, empty.size());
}

// Default Constructor
TEST(TestHashMap, defaultConstructorConstructsCorrectly)
{
	HashMap hm1;
	HashMap hm2;
	ASSERT_TRUE(hm1.equalTo(hm2, "Elton"));
}

// Constructor with new hashfunction

namespace
{
    unsigned int testHashFunction(const std::string& key)
    {
    	return 1337;
    }
}

TEST(TestHashMap, constructorWithHashFunctionConstructsCorrectly)
{
	HashMap hm1{testHashFunction};
	ASSERT_EQ(hm1.returnHasherValue("Hello"), testHashFunction("Hello"));

}

// Copy Constructor
TEST(TestHashMap, copyConstructorWorks)
{
	HashMap hm1;
	hm1.add("Elton", "20");
	hm1.add("Amy", "19");
	hm1.add("Boo", "11");
	HashMap hm2{hm1};
	ASSERT_TRUE(hm1.equalTo(hm2, "Elton"));
}

TEST(TestHashMap, copyConstructorWorksOpposite)
{
	HashMap hm1;
	HashMap hm2{hm1};
	hm1.add("EltonXue", "1234567");
	ASSERT_FALSE(hm1.equalTo(hm2, "Elton"));
}

// Assignment Constructor
TEST(TestHashMap, assignmentConstructorWorks)
{
	HashMap hm1;
	hm1.add("EltonXue", "1234567");
	HashMap hm2;
	hm1 = hm2;
	ASSERT_TRUE(hm1.equalTo(hm2, "Elton"));
}

TEST(TestHashMap, assignmentConstructorWorksOpposite)
{
	HashMap hm1;
	HashMap hm2 = hm1;
	hm1.add("EltonXue", "1234567");
	ASSERT_FALSE(hm1.equalTo(hm2, "Elton"));
}

TEST(TestHashMap, assignmentConstructorDoesNotAffectOriginalHashMap)
{
	HashMap hm1;
	hm1.add("EltonXue", "123456789");
	HashMap hm2 = hm1;
	hm2.remove("EltonXue");
	ASSERT_FALSE(hm1.equalTo(hm2, "Elton"));
}

// Add
TEST(TestHashMap, addFunctionWorks)
{
	HashMap hm1;
	hm1.add("EltonXue", "1234567");
	ASSERT_TRUE(hm1.contains("EltonXue"));
}

TEST(TestHashMap, addFunctionDoesNotAddSameKey)
{
	HashMap hm1;
	hm1.add("Elton", "1234567");
	hm1.add("Alex", "41");
	hm1.add("Elton", "abcdefg");
	ASSERT_EQ(hm1.size(), 2);
}

TEST(TestHashMap, addFunctionDoesNotAffectOriginalHashMap)
{
	HashMap hm1;
	HashMap hm2{hm1};
	hm2.add("Elton", "1234567");
	ASSERT_EQ(hm1.size(), 0);
	ASSERT_EQ(hm2.size(), 1);
	ASSERT_FALSE(hm1.equalTo(hm2, "Elton"));
}

// Remove
TEST(TestHashMap, removeFunctionWorks)
{
	HashMap hm1;
	hm1.add("Elton", "1234567");
	hm1.add("Alex", "abcdefg");
	hm1.remove("Elton");
	ASSERT_FALSE(hm1.contains("Elton"));
}

TEST(TestHashMap, removeFunctionDoesNotRemoveIfNotThere)
{
	HashMap hm1;
	hm1.add("Elton", "1234567");
	hm1.remove("Alex");
	ASSERT_EQ(hm1.size(), 1);
}

TEST(TestHashMap, removeFunctionDoesNotRemoveFromEmpty)
{
	HashMap hm1;
	hm1.remove("Alex");
	ASSERT_EQ(hm1.size(), 0);
}

TEST(TestHashMap, removeFunctionDoesNotAffectOriginalHashMap)
{
	HashMap hm1;
	hm1.add("Alex", "41");
	HashMap hm2{hm1};
	hm2.remove("Alex");
	ASSERT_EQ(hm1.size(), 1);
	ASSERT_EQ(hm2.size(), 0);
	ASSERT_FALSE(hm1.equalTo(hm2, "Elton"));
}

// Contains
TEST(TestHashMap, containsFunctionWorks)
{
	HashMap hm1;
	hm1.add("Elton", "abcdefg");
	hm1.add("Alex", "41");
	ASSERT_TRUE(hm1.contains("Elton"));
	ASSERT_TRUE(hm1.contains("Alex"));
	ASSERT_FALSE(hm1.contains("Harambe"));
	ASSERT_FALSE(hm1.contains("Harambe's friend"));
}

// Value
TEST(TestHashMap, valueFunctionReturnsCorrectValue)
{
	HashMap hm1;
	hm1.add("Elton", "abcdefg");
	ASSERT_EQ(hm1.value("Elton"), "abcdefg");
}

// Size
TEST(TestHashMap, sizeFunctionReturnsCorrectSize)
{
	HashMap hm1;
	hm1.add("Elton", "1234567");
	hm1.add("Alex", "41");
	hm1.add("Boo", "11");
	ASSERT_EQ(hm1.size(), 3);
}

// BucketCount
TEST(TestHashMap, bucketCountFunctionReturnsCorrectCount)
{
	HashMap hm1;
	hm1.add("Elton", "1234567");
	hm1.add("Alex", "41");
	ASSERT_EQ(hm1.bucketCount(), 10);
}

// LoadFactor
TEST(TestHashMap, loadFactorFunctionReturnsCorrectValue)
{
	HashMap hm1;
	hm1.add("Elton", "abcdefghijklmnopqrstuvwxyz");
	ASSERT_EQ(hm1.loadFactor(), 0.1);
	hm1.add("Alex", "41yearsold");
	ASSERT_EQ(hm1.loadFactor(), 0.2);
	hm1.remove("Elton");
	ASSERT_EQ(hm1.loadFactor(), 0.1);
}

// MaxBucketSize
TEST(TestHashMap, maxBucketSizeFunctionReturnsCorrectSize)
{
	HashMap hm1;
	hm1.add("Elton", "abcdefg");
	ASSERT_EQ(hm1.maxBucketSize(), 1); 
}

TEST(TestHashMap, maxBucketSizeAfterCopyCompared)
{
	HashMap hm1;
	hm1.add("Elton", "123456");
	hm1.add("Xue", "123456");
	HashMap hm2 = hm1;
	ASSERT_EQ(hm1.maxBucketSize(), hm2.maxBucketSize());
}

// Personal helper member functions

// BucketSize
TEST(TestHashMap, bucketSizeFunctionReturnsCorrectSize)
{
	HashMap hm1;
	for (int i = 0; i < hm1.bucketCount(); ++i)
	{
		ASSERT_EQ(hm1.bucketSize(i), 0);
	}
}

// EqualTo
TEST(TestHashMap, equalToFunctionReturnsCorrectBool)
{
	HashMap hm1;
	HashMap hm2;
	hm1.add("Elton", "1234567");
	hm2.add("Elton", "1234567");
	ASSERT_TRUE(hm1.equalTo(hm2, "Elton"));
}

// ReturnHasherValue
TEST(TestHashMap, returnHasherValueReturnsCorrectValue)
{
	HashMap hm1{testHashFunction};
	ASSERT_EQ(hm1.returnHasherValue("Elton"), 1337);

}

// ClearMainBuckets
TEST(TestHashMap, clearMainBucketsDeletesEverythingInPrivateBuckets)
{
	HashMap hm1;
	hm1.add("Elton", "1234567");
	hm1.clearMainBuckets();
	hm1.setNewBuckets();
	ASSERT_FALSE(hm1.contains("Elton"));
}

// ReHashMap
TEST(TestHashMap, reHashMapFunctionWorks)
{
	HashMap hm1;
	hm1.add("Elton", "1234567");
	hm1.add("Alex", "41");
	hm1.add("Chanun", "hello");
	hm1.add("Boo", "wowzers");
	hm1.add("Amy", "20");
	hm1.add("Rudy", "19");
	hm1.add("MyUsername", "MyPassword");
	hm1.add("userid", "userpass");
	ASSERT_EQ(hm1.bucketCount(), hm1.initialBucketCount);
	ASSERT_EQ(hm1.size(), 8);
	ASSERT_EQ(hm1.loadFactor(), 0.8);

	hm1.add("rehash", "hashmap");

	double eqLoadFactor = 9.0/21.0;
	ASSERT_EQ(hm1.bucketCount(), 21);
	ASSERT_EQ(hm1.size(), 9);
	ASSERT_EQ(hm1.loadFactor(), eqLoadFactor);
}