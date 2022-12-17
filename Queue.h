#ifndef __QUEUE_H__
#define __QUEUE_H__


#include "Node.h"

/*
 TODO:
    [ ] make an iterator class 
    [ ] CHECK WTF I'VE DID WITH THE ITERATOR CLASS
    [ ] check which of the functions has to be const
    [ ] complete the remaining functions(filter and transform)
    [ ] add the error indicators (try, catch, throw) in the needed places
    [ ] write notes here and there
    [ ] change it into template
*/

int typedef T;
typedef bool (*FunctionType)(int, int);

class Queue
{
    private:
        Node* first;    //pointer to the first item in the queue
        Node* last;     //pointet to the last item in the queue
        T lastItem;     //a copy from the last item in the queue
        int qSize=0;    //the size of the queue

    public:
        class Iterator;
        Queue();
        Queue(T item);
        ~Queue();
        void pushBack(T item);
        T* front();
        void popFront();
        int size();
};
//_____________________________________________________________________________________________________________________
class Queue::Iterator
{
    private:
        const Node* node;
        const Queue* queue;
        int index;
        Iterator(Queue* queue, int index);
        friend class Queue;
    public:
        ~Iterator();
        Iterator& operator++();
        Iterator operator++(int);
        bool operator!=(Iterator&);
        const Node& operator*() const;
};
//---------------------------------------------------------------------------------------------------------------------


Queue::Queue()
{
    this->first = nullptr;
    this->last = nullptr;
}

Queue::~Queue()
{
}

void Queue::pushBack(T item)
{
    Node* tmp = new Node(item);
    this->last->setNext(tmp);
    this->last = tmp;
    this->qSize++;
    this->lastItem = item;
}

T* Queue::front()
{
    return this->first->getItem();
}

void Queue::popFront()
{
    Node* tmp = this->first;
    this->first = this->first->getNext();
    delete tmp;
    this->qSize--;
}

int Queue::size()
{
    return this->qSize;
}

Queue& filter(Queue queue, FunctionType f)
{

}
//_____________________________________________________________________________________________________________________
/**
 * here we impliment the Queue::Iterator class
*/

Queue::Iterator::Iterator(Queue* queue, int index)
{

}

Queue::Iterator::~Iterator()
{

}

Queue::Iterator& Queue::Iterator::operator++()
{
    node = node->next;
    index++;
    return *this;
}


Queue::Iterator Queue::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++*this;
    return tmp;
}

bool Queue::Iterator::operator!=(Iterator& s )
{
    return index != s.index;
}


/**
 * here i'm trying to get to the node using the queue,
 * not the node that the iterator has in it, by making the [] operator
 * and then using it as an array
*/
const Node& Queue::Iterator::operator*() const
{
    //TODO: make a [] operator in Queue
    return *node;
}

#endif