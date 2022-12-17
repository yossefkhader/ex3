#ifndef __NODE_H__
#define __NODE_H__

#include "Queue.h"

/**
 * in this file we impliment the Node class which is used in the Queue class
*/

typedef int T;

/*
 TODO: 
    [ ] check which of the functions has to be const
    [ ] add the error indicators (try, catch, throw) in the needed places
    [ ] write notes here and there
    [ ] change it into template
*/

class Node
{
private:
    Node* next;
    T item;      
    friend class Queue;
public:
    Node(T item);
    ~Node() = default;
    void setNext(Node* item);   //changes the next pointer to the next node  
    Node* getNext();            //returns the next pointer
    T* getItem();               //returns a pointer to the item which is stored in the node
};

Node::Node(T item)
{
    this->next = nullptr;
    this->item = item;
}

void Node::setNext(Node* item)
{
    this->next = item;
}

Node* Node::getNext()
{
    return this->next;
}

T* Node::getItem()
{
    return &this->item;
}

#endif