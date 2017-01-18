#include <string>
#include "HashMap.hpp"

namespace
{
	unsigned int defaultHashFunction(const std::string& key)
	{
		unsigned int total = 0;
		for (int i = 0; i < key.length(); ++i)
		{
			total += key[i];
		}
		return total;
	}
}

HashMap::HashMap()
	: hasher{defaultHashFunction}, Buckets{new Node[initialBucketCount]}, totalBucketCount{initialBucketCount},
	totalSize{0}
{
	setNullptrs();
}

HashMap::HashMap(HashFunction hasher)
	:hasher{hasher}, Buckets{new Node[initialBucketCount]}, totalBucketCount{initialBucketCount},
	totalSize{0}
{
	setNullptrs();
}

HashMap::HashMap(const HashMap& hm)
	:hasher{hm.hasher}, Buckets{new Node[hm.totalBucketCount]}, totalBucketCount{hm.totalBucketCount},
	totalSize{hm.totalSize}
{
	for (int i = 0; i < totalBucketCount; ++i)
	{
		Node n = hm.Buckets[i];
		Node* copiedLinkedNode = copyLinkedNode(&n);
		Buckets[i] = *copiedLinkedNode;
		delete copiedLinkedNode;
	}
}

HashMap::~HashMap()
{
	clearMainBuckets();
}

HashMap& HashMap::operator=(const HashMap& hm)
{
	if (this != &hm)
	{
		Node* newBuckets = new Node[hm.totalBucketCount];

		for (int i = 0; i < hm.totalBucketCount; ++i)
		{
			Node n = hm.Buckets[i];
			Node* copiedLinkedNode = copyLinkedNode(&n);
			newBuckets[i] = *copiedLinkedNode;
			delete copiedLinkedNode;
		}

		clearMainBuckets();

		hasher = hm.hasher;
		totalBucketCount = hm.totalBucketCount;
		totalSize = hm.totalSize;

		Buckets = newBuckets;
	}
	return *this;
}



void HashMap::add(const std::string& key, const std::string& value) 
{
	reHashMap();

	unsigned int index = findIndex(hasher(key));

	if (not contains(key))
	{
		Node* temp = &Buckets[index];
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}

		temp->next = new Node{key, value, nullptr};
		
		totalSize++;
	}
}

void HashMap::remove(const std::string& key)
{
	unsigned int index = findIndex(hasher(key));

	if (contains(key))
	{
		Node* temp = Buckets[index].next;
		Node* trail = nullptr;

		while (temp != nullptr)
		{
			if (temp->key == key)
			{
				if (temp == Buckets[index].next)			
				{
					Buckets[index].next = Buckets[index].next->next;
					delete temp;
				}
				else if (temp != nullptr)
				{
					trail->next = temp->next;
					delete temp;
				}
				break;
			}
			else
			{
				trail = temp;
				temp = temp->next;
			}
		}

		totalSize--;
	}
}

bool HashMap::contains(const std::string& key) const
{
	unsigned int index = findIndex(hasher(key));

	Node* temp = &Buckets[index];
	while (temp != nullptr)
	{
		if (temp->key == key)
		{
			return true;
		}
		temp = temp->next;
	}
	return false;
}

std::string HashMap::value(const std::string& key) const
{
	unsigned int index = findIndex(hasher(key));

	Node* temp = &Buckets[index];
	while (temp != nullptr)
	{
		if (temp->key == key)
		{
			return temp->value;
		}
		temp = temp->next;
	}
	return "";
}

unsigned int HashMap::size() const
{
	return totalSize;
}


unsigned int HashMap::bucketCount() const 
{
	return totalBucketCount;
}

double HashMap::loadFactor() const
{

	return totalSize/double(totalBucketCount);
}

unsigned int HashMap::maxBucketSize() const
{
	unsigned int max = bucketSize(0);

	for (int i = 0; i < totalBucketCount; ++i)
	{
		unsigned int current = bucketSize(i);
		if (current > max)
		{
			max = current;
		}
	}
	return max;
}

unsigned int HashMap::bucketSize(const unsigned int index) const
{
	int count = 0;
	Node* temp = &Buckets[index];

	while (temp->next != nullptr)
	{
		count++;
		temp = temp->next;
	}
	return count;
}

bool HashMap::equalTo(const HashMap& hm, const std::string& key) const
{
	if (totalSize == hm.totalSize and totalBucketCount == hm.totalBucketCount 
		and maxBucketSize() == hm.maxBucketSize() and loadFactor() == hm.loadFactor()
		and returnHasherValue(key) == hm.returnHasherValue(key))
	{
		for (int i = 0; i < totalBucketCount; ++i)
		{
			Node* temp = &Buckets[i];
			Node* temp2 = &hm.Buckets[i];
			while (temp != nullptr and temp2 != nullptr)
			{
				if (temp->key != temp2->key or temp->value != temp->value)
				{
					return false;
				}
				temp = temp->next;
				temp2 = temp2->next;
			}
		}
		return true;
	}
	return false;
}

unsigned int HashMap::returnHasherValue(const std::string& key) const
{
	return hasher(key);
}

void HashMap::clearMainBuckets()
{
	for (int i = 0; i < totalBucketCount; ++i)
	{
		Node* temp = Buckets[i].next;

		while (temp != nullptr)
		{
			Buckets[i].next = Buckets[i].next->next;
			delete temp;
			temp = Buckets[i].next;
		}
	}
	delete[] Buckets;
}

void HashMap::setNewBuckets()
{
	Buckets = new Node[totalBucketCount];
	totalSize = 0;
	setNullptrs();
}



void HashMap::reHashMap()
{
	if (loadFactor() >= 0.8)
	{
		// copies Buckets into copyBuckets
		Node* copyBuckets = new Node[totalBucketCount];
		unsigned int copyTotalBucketCount = totalBucketCount;

		for (int i = 0; i < copyTotalBucketCount; ++i)
		{
			Node n = Buckets[i];
			Node* copiedLinkedNode = copyLinkedNode(&n);
			copyBuckets[i] = *copiedLinkedNode;
			delete copiedLinkedNode;
		}

		// deletes old Buckets and sets new Buckets
		clearMainBuckets();

		totalBucketCount = totalBucketCount * 2 + 1;
		totalSize = 0;

		setNewBuckets();

		// adds to Buckets from copyBuckets
		for (int i = 0; i < copyTotalBucketCount; ++i)
		{
			Node* temp = copyBuckets[i].next;
			while (temp != nullptr)
			{
				add(temp->key, temp->value);
				temp = temp->next;
			}
		}

		// deletes copyBuckets
		clearBuckets(copyBuckets, copyTotalBucketCount);
	}
}

// Private member functions

HashMap::Node* HashMap::copyLinkedNode(const Node* node)
{
	if (node == nullptr)
	{
		return nullptr;
	}
	else
	{
		Node* result = new Node{node->key, node->value, copyLinkedNode(node->next)};
		return result;
	}
}

void HashMap::clearBuckets(Node* buckets, unsigned int count)
{
	for (int i = 0; i < count; ++i)
	{
		Node* temp = buckets[i].next;

		while (temp != nullptr)
		{
			buckets[i].next = buckets[i].next->next;
			delete temp;
			temp = buckets[i].next;
		}

	}
	delete[] buckets;
}

void HashMap::setNullptrs()
{
	for (int i = 0; i < totalBucketCount; ++i)
	{
		Buckets[i].next = nullptr;
	}
}

unsigned int HashMap::findIndex(unsigned int hashValue) const
{
	return hashValue % totalBucketCount;
}