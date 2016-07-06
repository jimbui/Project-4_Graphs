#ifndef HASHTABLECHAIN_H
#define HASHTABLECHAIN_H

#include "ChainNode.h"
#include <iostream>
#include <cassert>

using namespace std;

template<class Key, class Value> class HashTableChain
{
private:
	ChainNode<Key, Value> * head;
	int sz;

	template<class key, class value> friend class HashTable;

public:
	HashTableChain() :head(nullptr), sz(0)
	{}

	bool isEmpty() const
	{
		return head == nullptr;
	}

	int Size() const { return sz; };

	~HashTableChain()
	{
		// clear();
	}

	// Accessors -----------------------------------------------------------------
	ChainNode<Key, Value>* GetHead() const { return head; };

	Value getHeadValue()
	{
		return head->data;
	}

	// Mutators -----------------------------------------------------------------
	void insert(const Value& data, const Key& dataKey)
	{
		ChainNode<Key, Value> *tmp_node = new ChainNode<Key, Value>(data, dataKey);
		ChainNode<Key, Value> *ptr = head;

		if (ptr == nullptr)
		{
			head = tmp_node;
			sz++;
		}

		else
		{
			while (ptr->next != nullptr)
			{
				ptr = ptr->next;
			}

			ptr->next = tmp_node;
			sz++;
		}
	}

	void insertBefore(const Value& data, const Key& dataKey, int pos)
	{
		if (pos <= 1)
		{
			ChainNode<Key, Value> *newNode = new ChainNode<Key, Value>(data, dataKey, head);
			head = newNode;
			sz++;
			// printLst();
		}
		else if (pos > sz)
		{
			insert(data, dataKey);
		}
		else
		{
			int p = 1;

			ChainNode<Key, Value> *newNode = new ChainNode<Key, Value>(data, dataKey);
			ChainNode<Key, Value> *ptr = head;

			while (p != pos - 1)
			{
				ptr = ptr->next;
				p++;
			}

			newNode->next = ptr->next;
			ptr->next = newNode;

			// printLst();
		}
	}

	void del(const Value& data)
	{
		ChainNode<Key, Value> *ptr = head;
		ChainNode<Key, Value> *prev = head;

		while (ptr != nullptr)
		{
			if (ptr->data == data)
			{
				if (ptr == head) 
					head = ptr->next;
				else
				{
					prev->next = ptr->next;
					ptr = prev;
				}
			}

			prev = ptr;
			ptr = ptr->next;

		}

		if (sz == 0)
			head = nullptr;

		// printLst();
	}

	void printLst() const
	{
		ChainNode<Key, Value> *ptr = head;
		int counter = 0;

		while (ptr != nullptr)
		{
			cout << ptr->data << " --> ";
			ptr = ptr->next;
		}

		cout << "[NULL]" << endl;
	}

	void clear()
	{
		ChainNode<Key, Value> *ptr = head;
		ChainNode<Key, Value> *prev = head;

		while (ptr != nullptr)
		{
			ptr = ptr->next;
			delete prev;
			prev = ptr;
		}

		head = nullptr;
	}
};

#endif