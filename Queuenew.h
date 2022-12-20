#ifndef __Queuenew_H__
#define __Queuenew_H__

#include "Node.h"

typedef int T;
// typedef T* Iterator; //it's forbidden to do that if you want to change the implementation of operator++ or any other operator
// typedef const T* const_Iterator; //the note above also for this one
typedef bool (*FilterType)(T);
typedef void (*TransformType)(T&);

/*
 TODO:
    [x] make an iterator class 
    [x] CHECK WTF I'VE DID WITH THE ITERATOR CLASS
    [ ] check which of the functions has to be const
    [ ] add the error indicators (try, catch, throw) in the needed places
    [x] complete the remaining functions(filter and transform)
    [ ] make an another copy for filter and transform that has function object in the argument
    [ ] change it into template    
    [x] write notes here and there
*/

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
        class const_Iterator;
        Queue() = default;
        ~Queue();    //TODO: a for loop that deletes each node
        const void pushBack(T item);
        T& front();
        const void popFront();
        const int size() const;
        Node* gotoIndex(int index);
        Iterator begin();
        const_Iterator begin() const;
        Iterator end();
        const_Iterator end() const;
};

class Queue::Iterator
{
private:
    // const Queue* m_q;
    Node* m_node;
    Iterator(Node* node);
    friend class Queue;
public:
    ~Iterator();
    // Queue::Iterator& operator=(const Queue::Iterator& it) = default;
    Queue::Iterator& operator++();
    const T& operator*() const;
    bool operator!=(const Queue::Iterator& it) const;
    friend Queue filter(Queue q, FilterType f);
    friend void transform(Queue q, FilterType f);

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
const void Queue::pushBack(T item)
{
    /**
      TODO: check if there is a need for a dummy node at the end
    */
    this->m_backCopy = item;
    Node* tmp = new Node(item);
    this->m_back->setNext(tmp); 
    this->m_size++;

}


T& Queue::front()
{
    return this->m_front->getRefItem();
}

/**
 * removes the first node in the queue,
 * and then subtracts 1 from the size of the queue.
*/
const void Queue::popFront()
{
    Node* tmp = this->m_front;
    this->m_front = this->m_front->getNext();
    delete tmp;
    this->m_size--;
}

const int Queue::size() const
{
    return this->m_size;
}

Node* Queue::gotoIndex(int index)
{
    Node* tmp = this->m_front;

    for(int i=0; i < index; ++i)
    {
        tmp = tmp->getNext();
    }

    return tmp;
}

Queue::Iterator Queue::begin()
{
    return Queue::Iterator(this->m_front);
}

Queue::Iterator Queue::end()
{
    return Queue::Iterator(nullptr);
}

/**
 * ------------------------------------------------------
 * Here starts the implementation of the class Queue::Iterator
 * ------------------------------------------------------
*/

Queue::Iterator::Iterator(Node* node):
    m_node(node)
{}

bool Queue::Iterator::operator!=(const Queue::Iterator& it) const
{
    return this->m_node != it.m_node;
}

/**
 * returns a reference to the Iterator after we made the change
*/

Queue::Iterator& Queue::Iterator::operator++()
{
    this->m_node = this->m_node->getNext();
    return *this;
}


/**
 * returns a pointer to the node we are at
*/
const T& Queue::Iterator::operator*() const
{
    return this->m_node->m_item;
}

/**
 * ------------------------------------------------------
 * Here starts the implementation of extra functions
 * ------------------------------------------------------
*/



Queue filter(Queue q, FilterType f)
{
    Queue result;
    for(Queue::Iterator it = q.begin(); it != q.end(); ++it)
    {
        if(f(it.m_node->getRefItem()))
        {
            result.pushBack(it.m_node->getRefItem());
        }
    }
    return result;
}

void transform(Queue q, FilterType f)
{
    for(Queue::Iterator it = q.begin(); it != q.end(); ++it)
    {
        f(it.m_node->getRefItem());
    }
}
#endif