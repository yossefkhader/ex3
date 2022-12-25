#ifndef __Queuenew_H__
#define __Queuenew_H__

#include <exception>
#include <new>
#include <iostream>
#include "Node.h"




/*
 TODO:
    [x] make an iterator class 
    [x] CHECK WTF I'VE DID WITH THE ITERATOR CLASS
    [ ] check which of the functions has to be const
    [ ] check also if there is enough function in the class to be const
    [x] create custom exception classes 
    [x] add the error indicators (try, catch, throw) in the needed places
    [ ] add the Iterator exceptions
    [x] complete the remaining functions(filter and transform)
    [ ] make an another copy for filter and transform that has function object in the argument
    FIXME: change it into template
    [x] write notes here and there
*/

template <class T>
class Queue
{
    private:
        Node<T>* m_front = nullptr;    //pointer to the first item in the queue
        Node<T>* m_back = nullptr;     //pointet to the last item in the queue
        T m_backCopy;    //a copy from the last item in the queue
        int m_size=0;    //the size of the queue
        friend class Iterator;
        friend class ConstIterator;
    public:
        class Iterator;
        class ConstIterator;
        class EmptyQueue;
        Queue() = default;
        ~Queue();
        Queue(const Queue& q);
        Queue& operator=(const Queue& q);
        const void pushBack(const T item);
        T& front();
        const T& front() const;
        const void popFront();
        const int size() const;
        Iterator begin();
        ConstIterator begin() const;
        Iterator end();
        ConstIterator end() const;
};

template <class T>
class Queue<T>::Iterator
{
private:
public:
    Iterator(Node<T>* node);
    Node<T>* m_node;
    class InvalidOperation;
    ~Iterator() = default;
    typename Queue<T>::Iterator& operator=(const Queue::Iterator& it) = default;
    typename Queue<T>::Iterator& operator++();
    T& operator*() const;
    bool operator!=(const Queue::Iterator& it) const;
};

template <class T>
class Queue<T>::ConstIterator
{
private:
public:
    ConstIterator(Node<T>* node);
    Node<T>* m_node;
    class InvalidOperation;
    ~ConstIterator() =default;
    Queue<T>::ConstIterator& operator=(const Queue::ConstIterator& it) = default;
    Queue<T>::ConstIterator& operator++();
    const T& operator*() const;
    bool operator!=(const Queue::ConstIterator& it) const;
};

template <class T>
class Queue<T>::EmptyQueue
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

template <class T>
class Queue<T>::Iterator::InvalidOperation
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

template <class T>
class Queue<T>::ConstIterator::InvalidOperation
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
template <class T>
Queue<T>::~Queue()
{
    for(int i=0; i<this->size(); ++i)
    {
        this->popFront();
    }

}

template <class T>
Queue<T>::Queue(const Queue& q):
    m_size(q.m_size)
{
    if(!q.m_front)
    {
        throw Queue::EmptyQueue();
    }
    for(Queue::ConstIterator it = q.begin(); it != q.end(); ++it)
    {
        this->pushBack(it.m_node->getRefItem());
    }
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue& q)
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
    for(Queue::ConstIterator it = q.begin(); it != q.end(); ++it)
    {
        this->pushBack(it.m_node->getRefItem());
    }

}


/**
 * gets an item and puts it in the back of the queue,
 * after that adds 1 to the size of the queue.
*/
template <class T>
const void Queue<T>::pushBack(T item)
{
    Node<T>* new_node = nullptr;
    this->m_backCopy = item;
    try{
        new_node = new Node<T>(item);
    }
    catch(std::bad_alloc& e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }

    if(this->m_front == nullptr)
    {
        this->m_front = new_node;
    } 
    else
    {
        this->m_back->setNext(new_node);
    }

    this->m_back = new_node;
    this->m_size++;
}

template <class T>
T& Queue<T>::front()
{
    if(!(this->m_front))
    {
        throw Queue::EmptyQueue();
    }
    return this->m_front->getRefItem();
}

template <class T>
const T& Queue<T>::front() const
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
template <class T>
const void Queue<T>::popFront()
{
    if(!(this->m_front)){
        return;
    }
    Node<T>* tmp = this->m_front;
    this->m_front = this->m_front->getNext();
    delete tmp;
    this->m_size--;
}

template <class T>
const int Queue<T>::size() const
{
    return this->m_size;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    return Queue::Iterator(this->m_front);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    return Queue::Iterator(nullptr);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return Queue::ConstIterator(this->m_front);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return Queue::ConstIterator(nullptr);
}

/**
 * ------------------------------------------------------------------------------------------------------------
 * 
 * Here starts the implementation of the class Queue::Iterator and Queue::ConstIterator
 * 
 * ------------------------------------------------------------------------------------------------------------
*/

template <class T>
Queue<T>::Iterator::Iterator(Node<T>* node):
    m_node(node)
{}

template <class T>
bool Queue<T>::Iterator::operator!=(const Queue<T>::Iterator& it) const
{
    return this->m_node != it.m_node;
}

/**
 * returns a reference to the Iterator after we made the change
*/

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    this->m_node = this->m_node->getNext();
    return *this;
}


/**
 * returns a pointer to the node we are at
*/
template <class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    return this->m_node->getRefItem();
}

template <class T>
Queue<T>::ConstIterator::ConstIterator(Node<T>* node):
    m_node(node)
{}

template <class T>
bool Queue<T>::ConstIterator::operator!=(const Queue::ConstIterator& it) const
{
    return this->m_node != it.m_node;
}

/**
 * returns a reference to the Iterator after we made the change
*/
template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    this->m_node = this->m_node->getNext();
    return *this;
}


/**
 * returns a pointer to the node we are at
*/
template <class T>
T& Queue<T>::Iterator::operator*() const
{
    return this->m_node->getRefItem();
}

/**
 * ------------------------------------------------------------------------------------------------------------
 * 
 * Here starts the implementation of extra functions
 * 
 * ------------------------------------------------------------------------------------------------------------
*/

template <class T>
Queue<T>& filter(const Queue<T>& q, bool (*FilterType)(T))
{
    Queue<T>* result;
    try{
        result = new Queue<T>();
    }
    catch(std::bad_alloc& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }
    for(typename Queue<T>::ConstIterator it = q.begin(); it != q.end(); ++it)
    {
        if(FilterType(it.m_node->getRefItem()))
        {
            result->pushBack(it.m_node->getRefItem());
        }
    }
    return *result;
}

template <class T>
void transform(Queue<T>& q, void (*TransformType)(T&))
{
    for(typename Queue<T>::Iterator it = q.begin(); it != q.end(); ++it)
    {
        TransformType(it.m_node->getRefItem());
    }
}

#endif