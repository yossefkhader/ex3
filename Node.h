#ifndef __NODE_H__
#define __NODE_H__
#include "Queuenew.h"

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

template <typename T>
class Node
{
private:
    Node* m_next;
    T m_item;      
public:
    Node(const T& m_item);
    ~Node() = default;
    const void setNext(Node* item);   //changes the m_next pointer to the next node  
Node* getNext() const;            //returns the m_next pointer
    T& getRefItem();         //returns a reference to m_item
};

template <class T>
Node<T>::Node(const T& m_item)
{
    this->m_next = nullptr;
    this->m_item = m_item;
}

template <class T>
const void Node<T>::setNext(Node<T>* item)
{
    this->m_next = item;
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