#ifndef __NODE_H__
#define __NODE_H__
#include "Queue.h"

/**
 * in this file we impliment the Node class which is used in the Queue class
*/

typedef int T;

/*s
 TODO: 
    [x] check which of the functions has to be const
    [ ] check also if there is enough function in the class to be const
    [x] add the error indicators (try, catch, throw) in the needed places
    [x] write notes here and there
    [x] change it into template
*/

template <class T>
class Node
{     
public:
    Node(const T& item);
    Node(const Node<T>&) = default;
    ~Node() = default;
    Node<T>& operator=(const Node<T>&) = default;
    
    void setNext(Node* next);   //changes the m_next pointer to the next node  
    Node* getNext() const;   //returns the m_next pointer
    T& getRefItem();    //returns a reference to m_item

private:
    Node* m_next;
    T m_item;
};

template <class T>
Node<T>::Node(const T& item):
    m_next(nullptr),
    m_item(item)
{}

template <class T>
void Node<T>::setNext(Node<T>* next)
{
    //sometimes this method called when there isn't a Node created (using a pointer)
    if(next == nullptr || this == nullptr)  
    {
        return;
    }
    this->m_next = next;
}

template <class T>
Node<T>* Node<T>::getNext() const
{
    return this->m_next;
}

template <class T>
T& Node<T>::getRefItem() 
{
    return this->m_item;
}


#endif