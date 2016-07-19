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
	template<class U> friend class DirGraph;
	template<class U> friend class Vertex;

protected:
	SLinkedList() :sz(0), head(NULL) {}

	bool isEmpty() const
	{
		return head == NULL;
	}

	int getSize() const
	{
		return sz;
	}

	Node<T>* insert(const T & data)
	{
		Node<T> *tmp = new Node<T>(data);

		if (head == NULL)
		{
			head = tmp;
			sz++;
		}
		else
		{
			Node<T> *ptr = head;

			while (ptr->next != NULL)
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
			while (ptr->next != NULL)
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

	void del(const T& data)
	{
		Node<T> *ptr = head;
		Node<T> *prev = head;

		if (this->isEmpty())  // check if the list is empty
		{
			throw underflow_error("You cannot delete something when there's nothing to delete. Can you ?");
		}
		else
		{
			while (ptr->next != NULL)
			{
				if (ptr->data == data)
				{
					if (ptr == head)
					{
						head = head->next;
						delete prev;

						sz--;
						return;  // Return statement added to resolve error.
					}
					else
					{
						Node<T>* tmp = ptr->next;

						ptr->data = ptr->next->data;
						ptr->next = ptr->next->next;

						delete tmp;
						sz--;
						return;  // Return statement added to resolve error.
					}
				}
				prev = ptr;
				ptr = ptr->next;
			}

			if (ptr->data == data)
			{
				prev->next = NULL;
				delete ptr;
				sz--;
			}
		}

		if (sz == 0)
			head = NULL;
	}

	void printList() const
	{
		Node<T> *ptr = head;
		while (ptr->next != NULL)
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

		while (ptr != NULL)
		{
			ptr = ptr->next;
			delete prev;
			prev = ptr;
		}

		head = NULL;
	}

	/*friend ostream& operator<<(ostream& os, const SLinkedList<T>& ls)
	{

	}*/
};
#endif
