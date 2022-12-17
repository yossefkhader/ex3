#ifndef __Queuenew_H__
#define __Queuenew_H__

#include "Node.h"

typedef int T;
typedef bool (*FilterType)(T);
typedef void (*TransformType)(T&);

class Queue
{
    private:
        Node* m_front = nullptr;    //pointer to the first item in the queue
        Node* m_back = nullptr;     //pointet to the last item in the queue
        T m_backCopy;     //a copy from the last item in the queue
        int m_size=0;    //the size of the queue
        friend class Iterator;
    public:
        class Iterator;
        Queue() = default;
        ~Queue();    //a for loop that deetes each node
        void pushBack(T item);
        T& front();
        void popFront();
        int size();
        Iterator* begin();
        Iterator* end();
};

class Queue::Iterator
{
private:
    const Queue* q;
    int index;
    Iterator(Queue* q, int index);
    friend class Queue;
public:
    Node* node; 
    ~Iterator();
    Queue::Iterator& operator++();
    bool operator!=(Queue::Iterator& it);
    const Node* operator*() const;
};

/**
 * ------------------------------------------------------
 * Here starts the implementation of the class Queue
 * ------------------------------------------------------
*/

/**
 * gets an item and puts it in the back of the queue,
 * after that adds 1 to the size of the queue.
*/
void Queue::pushBack(T item)
{
    /**
     * TODO: check if there is a need for a dummy node at the end
    */
    this->m_backCopy = item;
    Node* tmp = new Node(item);
    this->m_back->setNext(tmp); 
    this->m_size++;

}


T& Queue::front()
{
    return this->m_front->getItemR();
}


/**
 * removes the first node in the queue,
 * and then subtracts 1 from the size of the queue.
*/
void Queue::popFront()
{
    Node* tmp = this->m_front;
    this->m_front = this->m_front->getNext();
    delete tmp;
    this->m_size--;
}

int Queue::size()
{
    return this->m_size;
}

Queue::Iterator* Queue::begin()
{
    Queue::Iterator* result = new Queue::Iterator(this, 0);
    return result;
}

Queue::Iterator* Queue::end()
{
    Queue::Iterator* result = new Queue::Iterator(this, this->size());
    return result;
}

/**
 * ------------------------------------------------------
 * Here starts the implementation of the class Queue::Iterator
 * ------------------------------------------------------
*/

Queue::Iterator::Iterator(Queue* q, int index):
    q(q),
    index(index)
{
    this->node = q->m_front;

    for(int i=0; i < this->index; ++i)
    {
        this->node = this->node->getNext();
    }
}

/**
 * returns a reference to the Iterator after we made the change
*/
Queue::Iterator& Queue::Iterator::operator++()
{
    node = node->getNext();
    return *this;
}

/**
 * returns true if we are not at the same index
*/
bool Queue::Iterator::operator!=(Queue::Iterator& it)
{
    return !(index == it.index);
}

/**
 * returns a pointer to the node we are at
*/
const Node* Queue::Iterator::operator*() const
{
    return this->node;
}

/**
 * ------------------------------------------------------
 * Here starts the implementation of extra functions
 * ------------------------------------------------------
*/

Queue filter(Queue q, FilterType f)
{
    Queue* result = new Queue();
    for(Queue::Iterator* it = q.begin(); it != q.end(); ++it)
    {
        if(f(it->node->getItemV()))
        {
            result->pushBack(it->node->getItemV());
        }
    }

    return *result;
}

void transform(Queue q, FilterType f)
{
    for(Queue::Iterator* it = q.begin(); it != q.end(); ++it)
    {
        f(it->node->getItemR());
    }
}
#endif