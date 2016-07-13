#include "SLinkedList.h"
template<class type>
class mQueue:public SLinkedList<type>{
private:
    Node<type> *tail;
public:
    mQueue():tail(nullptr){}
    bool isEmpty() const{
        return SLinkedList<type>::isEmpty();
    }
    void enqueue(const type & data){
        Node<type> *tmp = new Node<type>(data);
        if(this->isEmpty()){
            SLinkedList<type>::head = tmp;
            tail = tmp;
            SLinkedList<type>::sz++;
        }
        else{
            tail->next =tmp;
            tail = tmp;
            SLinkedList<type>::sz++;
        }
    }

    type front() const {
        if (this->isEmpty()) throw underflow_error("Empty Queue");
        return SLinkedList<type>::head->data;
    }

    type back() const {
        if (this->isEmpty()) throw underflow_error("Empty Queue");
        return tail->data;
    }

    type dequeue(){
        type dat = this->front();
        Node<type> *ptr = SLinkedList<type>::head;
        SLinkedList<type>::head = ptr->next;
        delete ptr;
        SLinkedList<type>::sz--;
        return dat;
    }

    int size(){
        return SLinkedList<type>::sz;
    }

    void static display(mQueue<type> & Q){
        mQueue<type> Qtmp;
        while (!Q.isEmpty()){
            type d = Q.dequeue();
            Qtmp.enqueue(d);
            cout << d << "->";
        }
        cout << "back"<< endl;
        Q = Qtmp;
    }
};
