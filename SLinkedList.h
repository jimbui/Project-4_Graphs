#ifndef LIST
#define LIST

#include "Node.h"
#include<iostream>
#include<cassert>
#include <stdexcept>      // std::exception

using namespace std;

template <class T> class SLinkedList
{
protected:
	Node<T> * head;
	int sz;

	template<class U> friend class Graph;
	template<class U> friend class Vertex;

protected:
	SLinkedList() :sz(0), head(nullptr) {}

	bool isEmpty() const
	{
		return head == nullptr;
	}

	int getSize() const
	{
		return sz;
	}

	Node<T>* insert(const T & data)
	{
		Node<T> *tmp = new Node<T>(data);

		if (head == nullptr)
		{
			head = tmp;
			sz++;
		}
		else
		{
			Node<T> *ptr = head;

			while (ptr->next != nullptr)
			{
				ptr = ptr->next;
			}

			ptr->next = tmp;
			sz++;
		}

		return tmp;
	}

	void insert(const T & data, int pos)
	{
		if (pos <= 0)
		{
			Node<T> *tmp = new Node<T>(data, head);
			head = tmp;
			sz++;
		}
		else if (pos > sz)
		{
			SLinkedList::insert(data);
		}
		else
		{
			Node<T> *ptr = head;
			int k = 1;
			while (ptr->next != nullptr)
			{
				if (k == pos - 1)
				{
					Node<T> *tmp = new Node<T>(data);
					tmp->next = ptr->next;
					ptr->next = tmp;
					sz++;
					break;
				}
				else
				{
					ptr = ptr->next;
					k++;
				}
			}
		}

	}

	void del(const T & data)
	{
		Node<T> *ptr = head;
		Node<T> *prev = head;

		if (this->isEmpty())
		{//check if the list is empty
			throw underflow_error("You cannot delete something when there's nothing to delete. Can you ?");
		}
		else
		{
			while (ptr->next != nullptr)
			{
				if (ptr->data == data)
				{
					if (ptr == head)
					{
						head = head->next;
						delete prev;
						sz--;
					}
					else
					{
						Node<T> *tmp = ptr->next;
						ptr->id = ptr->next->id;
						ptr->data = ptr->next->data;
						ptr->next = ptr->next->next;
						delete tmp;
						sz--;
					}
				}
				prev = ptr;
				ptr = ptr->next;
			}
			if (ptr->data == data)
			{
				prev->next = nullptr;
				delete ptr;
				sz--;
			}
		}

		if (sz == 0)
			head = nullptr;
	}

	void printList() const
	{
		Node<T> *ptr = head;
		while (ptr->next != nullptr)
		{
			cout << "Node[" << ptr->id << "]= '" << ptr->data << "'-->";
			ptr = ptr->next;
		}

		cout << "Node[" << ptr->id << "]= '" << ptr->data << "'-->";
		cout << "end" << endl;
	}

	void clear()
	{
		Node<T> *ptr = head;
		Node<T> *prev = head;

		while (ptr != nullptr)
		{
			ptr = ptr->next;
			delete prev;
			prev = ptr;
		}

		head = nullptr;
	}

	/*friend ostream& operator<<(ostream& os, const SLinkedList<T>& ls)
	{

	}*/
};
#endif
