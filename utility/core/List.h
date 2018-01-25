//
// List.h
//

#ifndef NEXUSOS_LIST_H
#define NEXUSOS_LIST_H

//
// A list data-structure that doesn't require allocation. Nodes are inherited.
//
    
template<typename T>
class List {

  public:

    class Node {

      public:

        void setNext(T* next) { _next = next; }
        T*   getNext() const  { return _next; }

      private:

        T* _next;
        
    };

    void add(T* node)
    {
        if (_first == nullptr)
        {
            _first = node;
            _last = node;
        }
        else
        {
            _last->setNext(node);
            _last = node;
        }
    }

    T* remove(T* node, T* prev)
    {
        if (prev)
        {
            prev->setNext(node->getNext());

            return prev;
        }
        else _first = node->getNext();

        return node;
    }

    T* getFirst() const { return _first; }

  private:

    T* _first = nullptr;
    T* _last = nullptr;
    
};

#endif
