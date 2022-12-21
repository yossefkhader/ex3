#ifndef __Queuenew_H__
#define __Queuenew_H__

#include <exception>
#include <new>
#include <iostream>
#include "Node.h"

typedef int T;

typedef bool (*FilterType)(T);
typedef void (*TransformType)(T&);

/*
 TODO:
    [x] make an iterator class 
    [x] CHECK WTF I'VE DID WITH THE ITERATOR CLASS
    [ ] check which of the functions has to be const
    [x] create custom exception classes 
    [x] add the error indicators (try, catch, throw) in the needed places
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
        T m_backCopy;    //a copy from the last item in the queue
        int m_size=0;    //the size of the queue
        friend class Iterator;
    public:
        class Iterator;
        class const_Iterator;
        class EmptyQueue;
        Queue() = default;
        ~Queue();
        Queue(const Queue& q);
        Queue& operator=(const Queue& q);
        const void pushBack(const T item);
        T& front();
        const T& front() const; //needs implementation
        const void popFront();
        const int size() const;
        Iterator begin();
        const_Iterator begin() const;
        Iterator end();
        const_Iterator end() const;
};

class Queue::Iterator
{
private:
    Node* m_node;
    Iterator(Node* node);
    friend class Queue;
public:
    class InvalidOperation;
    ~Iterator();
    Queue::Iterator& operator=(const Queue::Iterator& it) = default;
    Queue::Iterator& operator++();
    const T& operator*() const;
    bool operator!=(const Queue::Iterator& it) const;
    friend void transform(Queue& q, FilterType f);

};

class Queue::const_Iterator
{
private:
    Node* m_node;
    const_Iterator(Node* node);
    friend class Queue;
public:
    class InvalidOperation;
    ~const_Iterator();
    Queue::const_Iterator& operator=(const Queue::const_Iterator& it) = default;
    Queue::const_Iterator& operator++();
    const T& operator*() const;
    bool operator!=(const Queue::const_Iterator& it) const;
    friend Queue& filter(const Queue& q, FilterType f);

};

class Queue::EmptyQueue
{
public:
    EmptyQueue() = default;
    ~EmptyQueue() = default;
    EmptyQueue(const EmptyQueue&) = default;
    EmptyQueue& operator=(const EmptyQueue&) = default;
    const char* what()
    {
        return "Failed: Empty Queue";
    }
};

class Queue::Iterator::InvalidOperation
{
public:
    InvalidOperation() = default;
    ~InvalidOperation() = default;
    InvalidOperation(const InvalidOperation&) = default;
    InvalidOperation& operator=(const InvalidOperation&) = default;
    const char* what()
    {
        return "Failed: Invalid Operation on the Iterator";
    }
};


/**
 * ------------------------------------------------------------------------------------------------------------
 * 
 * Here starts the implementation of the class Queue
 * 
 * ------------------------------------------------------------------------------------------------------------
*/

Queue::~Queue()
{
    for(int i=0; i<this->size(); ++i)
    {
        this->popFront();
    }

}

Queue::Queue(const Queue& q):
    m_size(q.m_size)
{
    if(!q.m_front)
    {
        throw Queue::EmptyQueue();
    }
    try{
        m_front = new Node(q.front());
    }
    catch(std::bad_alloc& e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }
    for(Queue::const_Iterator it = q.begin(); it != q.end(); ++it)
    {
        pushBack(it.m_node->getRefItem());
    }
}

Queue& Queue::operator=(const Queue& q)
{
    if(this == &q){
        return *this;
    }
    int qSize = this->size();
    for(int i=0; i < qSize; i++)
    {
        this->popFront();
    }
    this->m_size = q.m_size;
    for(Queue::const_Iterator it = q.begin(); it != q.end(); ++it)
    {
        this->pushBack(it.m_node->getRefItem());
    }

}


/**
 * gets an item and puts it in the back of the queue,
 * after that adds 1 to the size of the queue.
*/
const void Queue::pushBack(T item)
{
    try{
        this->m_backCopy = item;
        Node* tmp = new Node(item);
        this->m_back->setNext(tmp);
        this->m_size++;
    }
    catch(std::bad_alloc& e)
    {
        std::cerr << e.what() << std::endl;
        this->~Queue();
        throw;
    } 
}

T& Queue::front()
{
    if(!(this->m_front))
    {
        throw Queue::EmptyQueue();
    }
    return this->m_front->getRefItem();
}

const T& Queue::front() const
{
    if(!(this->m_front))
    {
        throw Queue::EmptyQueue();
    }
    return this->m_front->getRefItem();
}

/**
 * removes the first node in the queue,
 * and then subtracts 1 from the size of the queue.
*/
const void Queue::popFront()
{
    if(!(this->m_front)){
        return;
    }
    Node* tmp = this->m_front;
    this->m_front = this->m_front->getNext();
    delete tmp;
    this->m_size--;
}

const int Queue::size() const
{
    return this->m_size;
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
 * ------------------------------------------------------------------------------------------------------------
 * 
 * Here starts the implementation of the class Queue::Iterator and Queue::const_Iterator
 * 
 * ------------------------------------------------------------------------------------------------------------
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
const T& Queue::const_Iterator::operator*() const
{
    return this->m_node->m_item;
}

Queue::const_Iterator::const_Iterator(Node* node):
    m_node(node)
{}

bool Queue::const_Iterator::operator!=(const Queue::const_Iterator& it) const
{
    return this->m_node != it.m_node;
}

/**
 * returns a reference to the Iterator after we made the change
*/

Queue::const_Iterator& Queue::const_Iterator::operator++()
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
 * ------------------------------------------------------------------------------------------------------------
 * 
 * Here starts the implementation of extra functions
 * 
 * ------------------------------------------------------------------------------------------------------------
*/


Queue& filter(const Queue& q, FilterType f)
{
    Queue* result;
    try{
        result = new Queue();
    }
    catch(std::bad_alloc& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }
    for(Queue::const_Iterator it = q.begin(); it != q.end(); ++it)
    {
        if(f(it.m_node->getRefItem()))
        {
            result->pushBack(it.m_node->getRefItem());
        }
    }
    return *result;
}

void transform(Queue& q, FilterType f)
{
    for(Queue::Iterator it = q.begin(); it != q.end(); ++it)
    {
        f(it.m_node->getRefItem());
    }
}

#endif