#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <typeinfo>
#include <stdexcept>
#include "HashTableChain.h"

template<class Key, class Value> class HashTable
{
	template<class U> friend class Graph;
	template<class U> friend class DirGraph;

private:
	// Contains the total number of values in the entire hash table
	int numElements;

	// Contains the number of buckets
	int arraySize;
	double loadFactorCriterion;

	// Contains array of buckets to hold data
	HashTableChain<Key, Value>* bucket;

	// THIS HASH TABLE IS DESIGNED ONLY TO USE STRINGS AS KEYS!  DO
	// NOT USE ANY OTHER VALUE TYPE!
	int HashValString(const string& key, const int& capacity)
	{
		int sumCharacters = 0;
		int keyLength = key.length();

		for (int i = 0; i < keyLength; i++)
			sumCharacters += (int)key[i] * (i + 1);

		return sumCharacters % capacity;
	}

	// The hash function --> note that this one is basic.
	int GetHashValue(const Key &key, const int& capacity)
	{
		return HashValString(key, capacity);
	}

	// Resizes the array of buckets if resizing is needed.
	void ResizeBucketArray(const double& factor)
	{
		HashTableChain<Key, Value>* newBucket = new HashTableChain<Key, Value>[(int)(arraySize * factor)];

		// Copy the elements of the old set of buckets to the new one
		for (int i = 0; i < arraySize; i++)
		{
			// Traverse the old list, get the nodes, and assign them to the correct place in the new list
			ChainNode<Key, Value>* ptr = bucket[i].GetHead();

			while (ptr != nullptr)
			{
				Key nodeDataKey = ptr->dataKey;

				newBucket[GetHashValue(nodeDataKey, (int)(arraySize * factor))].insertBefore(ptr->data, nodeDataKey, 0);

				ptr = ptr->next;
			}

			// newBucket[i] = bucket[i];
		}

		// Deletes the old bucket
		delete[] bucket;

		// Assigns the value of the old bucket to that of the new one.
		bucket = newBucket;

		// Multiplies arraySize by 2
		arraySize = (int)(arraySize * factor);
	}

public:
	// Constructor ------------------------------------------------------------------
	// Initialize the hash table with a certain number of buckets
	HashTable(int n = 13, double LoadFactorCriterion = 0.5) :arraySize(n), loadFactorCriterion(LoadFactorCriterion)
	{
		bucket = new HashTableChain<Key, Value>[n];
		numElements = 0;
	}


	// Destructor ------------------------------------------------------------------
	~HashTable()
	{
		clear();

		delete[] bucket;
	}

	// Accessors ------------------------------------------------------------------
	// Gets the number of elements currently in the hash table
	int NumberOfDataItems() const { return numElements; };

	// Gets the number of buckets in the hash table
	int NumberOfBuckets() const { return arraySize; };

	// Searches the hash table by key and returns the value of the node associated with that key
	Value search(const Key &key)
	{
		// Determine what hash function to use
		int hashValue = GetHashValue(key, arraySize);

		ChainNode<Key, Value>* ptr = bucket[hashValue].GetHead();

		Value returnVal;

		if (ptr == nullptr)
			throw underflow_error("The bucket is empty; no value was returned.");

		else
		{
			// Searches the list until the item is found. O(1) is the optimal circumstance.  The worst-case
			// scenario is one in which the key entered hashes to a list, but none of the list elements 
			// contain the desired key (Search time = O(n)).
			bool foundValue = false;

			while (ptr != nullptr)
			{
				if (key == ptr->dataKey)
				{
					returnVal = ptr->data;
					foundValue = true;
					break;
				}

				ptr = ptr->next;
			}

			if (!foundValue)
				throw underflow_error("The bucket is full, but there is no value associated with the entered key.");
		}

		return returnVal;
	}

	// Check to see if a value exists at a certain key
	bool CheckExistenceOf(const Key& key)
	{
		int hashValue = GetHashValue(key, arraySize);

		ChainNode<Key, Value>* ptr = bucket[hashValue].GetHead();

		if (ptr == nullptr)
			return false;

		else
		{
			// Searches the list until the item is found. O(1) is the optimal circumstance.  The worst-case
			// scenario is one in which the key entered hashes to a list, but none of the list elements 
			// contain the desired key (Search time = O(n)).
			bool foundValue = false;

			while (ptr != nullptr)
			{
				if (key == ptr->dataKey)
				{
					/*returnVal = ptr->data;
					foundValue = true;
					break;*/

					return true;
				}

				ptr = ptr->next;
			}

			return foundValue;
		}

		// return returnVal;
	}

	// Mutators ------------------------------------------------------------------
	// Inserts an element at the position specified by key
	void insert(const Key &key, const Value &val)
	{
		int hashVal = GetHashValue(key, arraySize);

		ChainNode<Key, Value>* ptr = bucket[hashVal].GetHead();

		if (ptr == nullptr)  // The bucket is empty
		{
			bucket[hashVal].insert(val, key);
			numElements++;

			// Check to see whether dynamic allocation is necessary.  (Allocate memory if so)
			if ((double)numElements / arraySize > loadFactorCriterion)
				ResizeBucketArray(1.7389);
		}
		else  // Check to see whether the bucket already contains an element of the specified key
		{
			bool keyFound = false;

			while (ptr != nullptr)
			{
				if (ptr->dataKey == key)
				{
					keyFound = true;
					// cout << "Key already contains value.  Unable to insert element." << endl;
					break;
				}

				ptr = ptr->next;
			}

			if (!keyFound)
			{
				bucket[hashVal].insert(val, key);
				numElements++;

				// Check to see whether dynamic allocation is necessary.  (Allocate memory if so)
				if ((double)numElements / arraySize > loadFactorCriterion)
					ResizeBucketArray(1.7389);
			}
		}
	}

	// Erases an element at the position specified by key
	void erase(const Key &key)
	{
		int hashValue = GetHashValue(key, arraySize);

		// Change this code.
		ChainNode<Key, Value>* prevPtr = nullptr;
		ChainNode<Key, Value>* ptr = bucket[hashValue].GetHead();

		if (ptr == nullptr)
			cout << "The key does not contain a value." << endl;
		else
		{
			bool foundValue = false;

			while (ptr != nullptr)
			{
				if (key == ptr->dataKey)
				{
					if (prevPtr == nullptr)  // The current position of ptr is the head
					{
						bucket[hashValue].head = ptr->next;
						cout << "Value at key " << ptr->dataKey << " deleted" << endl;
						delete ptr;
						ptr = bucket[hashValue].head;
						foundValue = true;
						numElements--;
						bucket[hashValue].sz--;
						break;
					}
					else  // The current position of ptr is elsewhere
					{
						prevPtr->next = ptr->next;
						cout << "Value at key " << ptr->dataKey << " deleted" << endl;
						delete ptr;
						foundValue = true;
						numElements--;
						bucket[hashValue].sz--;
						break;
					}
				}

				prevPtr = ptr;
				ptr = ptr->next;
			}

			if (!foundValue)
				cout << "The key does not contain a value." << endl;
		}
	}

	// Removes an element from the hash table without deleting it.
	Value Remove(const Key &key)
	{
		int hashValue = GetHashValue(key, arraySize);

		// Change this code.
		ChainNode<Key, Value>* prevPtr = nullptr;
		ChainNode<Key, Value>* ptr = bucket[hashValue].GetHead();

		Value returnVal;

		if (ptr == nullptr)
			cout << "The key does not contain a value." << endl;
		else
		{
			bool foundValue = false;

			while (ptr != nullptr)
			{
				if (key == ptr->dataKey)
				{
					if (prevPtr == nullptr)  // The current position of ptr is the head
					{
						bucket[hashValue].head = ptr->next;
						// cout << "Value at key " << ptr->dataKey << " deleted" << endl;
						returnVal = ptr->data;
						// delete ptr;
						ptr = bucket[hashValue].head;
						foundValue = true;
						numElements--;
						bucket[hashValue].sz--;
						break;
					}
					else  // The current position of ptr is elsewhere
					{
						prevPtr->next = ptr->next;
						// cout << "Value at key " << ptr->dataKey << " deleted" << endl;
						returnVal = ptr->data;
						// delete ptr;
						foundValue = true;
						numElements--;
						bucket[hashValue].sz--;
						break;
					}
				}

				prevPtr = ptr;
				ptr = ptr->next;
			}

			if (!foundValue)
				cout << "The key does not contain a value." << endl;
		}

		return returnVal;
	}

	// Deletes all of the elements in the hash table, but not the table itself.
	void clear()
	{
		for (int i = 0; i < arraySize; i++)
		{
			bucket[i].clear();
		}

		numElements = 0;
	}

	// Debug ------------------------------------------------------------------
	// Displays the entire hash table
	void Display() const
	{
		// How would one go about using strings as keys...?
		// cout << "This is a hash table." << endl;
		for (int i = 0; i < arraySize; i++)
		{
			cout << "Bucket[" << i << "]:\t";
			bucket[i].printLst();
		}

		cout << endl;
	}

	// Displays all of the elements of the hash table on their own line (use for adjacency-list representation)
	void DisplayElementList()
	{
		if (numElements > 0) // How to get all of the vertices in the hash table...
		{
			for (int i = 0; i < arraySize; i++)
			{
				ChainNode<Key, Value>* ptr = bucket[i].GetHead();

				if (ptr != nullptr)
					cout << ptr->data << endl;
			}
		}
		else
			cout << "The table is empty." << endl;

		cout << endl;
	}

	// DO NOT USE THE DISPLAY FUNCTION LISTED BELOW!

	// Displays statistics
	void DisplayDebugInfo() const
	{
		cout << "Number of buckets:  " << arraySize << endl;
		cout << "Number of elements in table:  " << numElements << endl;
		cout << "% Space Usage:  " << (double)numElements / arraySize * 100 << endl
			<< " --> Higher values are better." << endl;
		cout << "Max chain length:  ";

		int maxChainLength = 0;

		for (int i = 0; i < arraySize; i++)
		{
			int bucketSize = bucket[i].Size();

			if (maxChainLength < bucketSize)
				maxChainLength = bucketSize;
		}
		cout << maxChainLength << endl << " --> Lower values are better." << endl;

		cout << "Average chain length (bucket not empty):  ";

		double averageChainLength = 0;
		int numBucketsFilled = 0;

		for (int i = 0; i < arraySize; i++)
		{
			int bucketSize = bucket[i].Size();

			averageChainLength += bucketSize;

			if (bucketSize > 0)
				numBucketsFilled++;
		}

		averageChainLength = (numBucketsFilled > 0 ? averageChainLength / numBucketsFilled : 0);

		cout << averageChainLength << endl << " --> Lower values are better." << endl;
	}
};

#endif