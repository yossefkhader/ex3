#ifndef __QUEUE_H__
#define __QUEUE_H__


#include "Node.h"



int typedef T;
typedef bool (*FunctionType)(T);

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
        Iterator* begin();
        Iterator* end();
};
//_____________________________________________________________________________________________________________________
class Queue::Iterator
{
    private:
        Node* node;
        const Queue* queue;
        int index;
        Iterator(Queue* queue, int index);
        friend class Queue;
    public:
        ~Iterator() = default;
        Queue::Iterator& operator++();
        Queue::Iterator operator++(int);
        bool operator!=(Queue::Iterator& it);
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

Queue::Iterator* Queue::begin()
{
    Queue::Iterator* tmp = new Queue::Iterator(this, 0);
    return tmp;
}

Queue::Iterator* Queue::end()
{
    Queue::Iterator* tmp = new Queue::Iterator(this, this->size());
    return tmp;
}

Queue& filter(Queue queue, FunctionType f)
{
    Queue* tmp = new Queue();
    
}

/**_____________________________________________________________________________________________________________________
 * 
 * here we impliment the Queue::Iterator class
 * 
*/

Queue::Iterator::Iterator(Queue* queue, int index):
    queue(queue),
    node(queue->first),
    index(index)
{
    for(int i=0; i<index; ++i)      //move to the node that we have to point at
    {
        node = node->next;
    }
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

bool Queue::Iterator::operator!=(Queue::Iterator& it)
{
    return index != it.index;
}


/**
 * here i'm trying to get to the node using the queue,
 * not the node that the iterator has in it, by making the [] operator
 * and then using it as an array
*/
const Node& Queue::Iterator::operator*() const
{
    return *node;
}

#endif