#ifndef __NODE_H__
#define __NODE_H__


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
    Node* m_next;
    T m_item;      
    friend class Queue;
public:
    Node(T m_item);
    ~Node() = default;
    void setNext(Node* m_item);   //changes the m_next pointer to the next node  
    Node* getNext();            //returns the m_next pointer
    T& getRefItem();         //returns a reference to the m_item
};

Node::Node(T m_item)
{
    this->m_next = nullptr;
    this->m_item = m_item;
}

void Node::setNext(Node* m_item)
{
    this->m_next = m_item;
}

Node* Node::getNext()
{
    return this->m_next;
}

T& Node::getRefItem()
{
    return this->m_item;
}


#endif