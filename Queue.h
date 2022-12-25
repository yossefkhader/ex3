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
    [x] check which of the functions has to be const
    [x] check also if there is enough function in the class to be const
    [x] create custom exception classes 
    [x] add the error indicators (try, catch, throw) in the needed places
    [ ] add the Iterator exceptions
    [x] complete the remaining functions(filter and transform)
    [x] make an another copy for filter and transform that has function object in the argument
    FIXME: change it into template
    [x] write notes here and there
*/

template <class T>
class Queue
{
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
    
    private:
        Node<T>* m_front = nullptr;    //pointer to the first item in the queue
        Node<T>* m_back = nullptr;    //pointet to the last item in the queue
        int m_size=0;     //the size of the queue
        friend class Iterator;
        friend class ConstIterator;
};

template <class T>
class Queue<T>::Iterator
{
public:
    class InvalidOperation;
    
    ~Iterator() = default;
    Iterator(const Queue<T>::Iterator&) = default;
    Queue<T>::Iterator& operator=(const Queue::Iterator& it) = default;
    

    T& operator*() const;
    bool operator!=(const Queue::Iterator& it) const;
    Queue<T>::Iterator& operator++();
    
    /**
     * using 'typename E' as extra "type" for declaring transform as a friend
     * and 'typename' F for the function object
    */
    template <typename E>
    friend void transform(Queue<E>& q, void (*TransformType)(E&)); //takes function ptr in the argumnt
    template <class E, typename F>
    friend void transform(Queue<E>& q, F function); //takes a function object in the argument

private:
    Node<T>* m_node;
    Iterator(Node<T>* node);
    friend class Queue;
};

template <class T>
class Queue<T>::ConstIterator
{
public:
    class InvalidOperation;

    ~ConstIterator() =default;
    ConstIterator(const Queue<T>::ConstIterator&) = default;
    Queue<T>::ConstIterator& operator=(const Queue::ConstIterator& it) = default;
    
    const T& operator*() const;
    bool operator!=(const Queue::ConstIterator& it) const;
    Queue<T>::ConstIterator& operator++();

    /**
     * using 'typename E' as extra "type" for declaring filter as a friend
     * and 'typename' F for the function object
    */
    template <typename E>
    friend Queue<E>& filter(const Queue<E>& q, bool (*FilterType)(E)); //takes function ptr in the argumnt
    template <typename E, typename F>
    friend Queue<E>& filter(const Queue<E>& q, F function); //takes a function object in the argument

private:
    Node<T>* m_node;
    ConstIterator(Node<T>* node);    
    friend class Queue;

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
Queue<T>::Queue(const Queue& q)
{
    if(!q.m_front)
    {
        throw Queue::EmptyQueue();
    }
    this->m_size = 0;
    for(Queue::ConstIterator it = q.begin(); it != q.end(); ++it)
    {
        this->pushBack(it.m_node->getRefItem());
    }
}

//Todo: check this shit
template <class T>
Queue<T>& Queue<T>::operator=(const Queue& q)
{
    if(this == &q){
        return *this;
    }
    Queue<T>* tmp = nullptr;

    try
    {
        tmp = new Queue<T>(*this);
    }
    catch (std::bad_alloc& e)
    {
        std::cerr << e.what() << std::endl;
    }

    int qSize = this->size();
    for(int i=0; i < qSize; i++)
    {
        this->popFront();
    }
    this->m_size = 0;
    try
    {
        for(Queue::ConstIterator it = q.begin(); it != q.end(); ++it)
        {
            this->pushBack(it.m_node->getRefItem());
        }
    }
    catch (std::bad_alloc& e)
    {
        std::cerr << e.what() << std::endl;
        delete this;
        return tmp;
    }
    
    return *this;
}

template <class T>
const void Queue<T>::pushBack(T item)
{
    Node<T> *new_node = nullptr;
    try 
    {
        new_node = new Node<T>(item);
    } 
    catch (std::bad_alloc &e) 
    {
        std::cerr << e.what() << std::endl;
        throw;
    }

    if (this->m_front == nullptr) 
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

template <class T>
const void Queue<T>::popFront()
{
    if(!(this->m_front)){
        throw Queue::EmptyQueue();

    }
    
    Node<T>* tmp = this->m_front;
    this->m_front = this->m_front->getNext();
    delete tmp;
    this->m_size -= 1;
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
T& Queue<T>::Iterator::operator*() const
{
    if(this->m_node == nullptr)
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    return this->m_node->getRefItem();
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Queue<T>::Iterator& it) const
{
    return this->m_node != it.m_node;
}

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if(this->m_node == nullptr)
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    this->m_node = this->m_node->getNext();
    return *this;
}



template <class T>
Queue<T>::ConstIterator::ConstIterator(Node<T>* node):
    m_node(node)
{}

template <class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    if(this->m_node == nullptr)
    {
        throw Queue<T>::ConstIterator::InvalidOperation();
    }
    return this->m_node->getRefItem();
}

template <class T>
bool Queue<T>::ConstIterator::operator!=(const Queue::ConstIterator& it) const
{
    return this->m_node != it.m_node;
}

template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if(this->m_node == nullptr)
    {
        throw Queue<T>::ConstIterator::InvalidOperation();
    }
    this->m_node = this->m_node->getNext();
    return *this;
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

template <class T, typename F>
Queue<T>& filter(const Queue<T>& q, F function)
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
        if(function(it.m_node->getRefItem()))
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

template <class T, typename F>
void transform(Queue<T>& q, F function)
{
    for(typename Queue<T>::Iterator it = q.begin(); it != q.end(); ++it)
    {
        function(it.m_node->getRefItem());
    }
}

#endif