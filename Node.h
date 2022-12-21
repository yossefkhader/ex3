#ifndef __NODE_H__
#define __NODE_H__


/**
 * in this file we impliment the Node class which is used in the Queue class
*/

typedef int T;

/*
 TODO: 
    [x] check which of the functions has to be const
    [x] add the error indicators (try, catch, throw) in the needed places
    [x] write notes here and there
    [ ] change it into template
*/

class Node
{
private:
    Node* m_next;
    T m_item;      
    friend class Queue;
public:
    Node(const T& m_item);
    ~Node() = default;
    const void setNext(Node* item);   //changes the m_next pointer to the next node  
    Node* getNext() const;            //returns the m_next pointer
    T& getRefItem();         //returns a reference to m_item
};

Node::Node(const T& m_item)
{
    this->m_next = nullptr;
    this->m_item = m_item;
}

const void Node::setNext(Node* item)
{
    this->m_next = item;
}

Node* Node::getNext() const
{
    return this->m_next;
}

T& Node::getRefItem() 
{
    return this->m_item;
}


#endif