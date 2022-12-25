#ifndef __LinkedList_H__
#define __LinkedList_H__

typedef int T;

class LinkedList
{
private:
    T* ptr;
    T item;
public:
    LinkedList(T item);
    ~LinkedList() = default;
    void setPtr(T* item);
};

LinkedList::LinkedList(T item)
{
    this->ptr = nullptr;
    this->item = item;
}

void LinkedList::setPtr(T* item)
{
    this->ptr = item;
}




#endif