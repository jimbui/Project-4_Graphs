#ifndef CHAINNODE_H
#define CHAINNODE_H

// Node contains key info used in preserving the contents of the hash table after resizing
#include <iostream>
#include <string>

using namespace std;

template <class Key, class Value> class ChainNode
{
private:
	Value data;
	Key dataKey;

	ChainNode* next;

	template<class key, class value> friend class HashTableChain;
	template<class key, class value> friend class HashTable;

public:
	ChainNode() :data(0), next(0), dataKey(0)
	{}

	ChainNode(const Value& data, const Key& dataKey) :next(0)
	{
		this->data = data;
		this->dataKey = dataKey;
	}

	ChainNode(const Value& data, const Key& dataKey, ChainNode* next)
	{
		this->data = data;
		this->dataKey = dataKey;
		this->next = next;
	}

	// Include operator overloading in final project.
	friend ostream& operator<<(ostream& os, const ChainNode<Key, Value>& n)
	{
		os << n.data;
		return os;
	}
};

#endif