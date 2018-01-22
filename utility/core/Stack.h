//
// Stack.h
//

#ifndef NEXUSOS_STACK_H
#define NEXUSOS_STACK_H

//
// A list data-structure that doesn't require allocation. Nodes are inherited.
//

template<size_t S, size_t R>
class Stack {

  public:

    bool push(char c)
    {
        if (_index < S)
        {
            _items[_index++] = c;

            return true;
        }
        
        return false;
    }

    bool pop()
    {
        if (_index > 0)
        {
            --_index;

            return true;
        }

        return false;
    }

    void reset()
    {
        _index = 0;
    }

    char& operator [](size_t index)
    {
        return _items[index % (S + R)];
    }

    size_t size() const
    {
        return _index;
    }

  private:

    char   _items[S + R];
    size_t _index = 0;

};
    
// template<typename T>
// class List {

//   public:

//     class Node {

//       public:

//         void setNext(T* next) { _next = next; }
//         T*   getNext() const  { return _next; }

//       private:

//         T* _next;
        
//     };

//     List() { }

//     void add(T* node)
//     {
//         if (_first == nullptr)
//         {
//             _first = node;
//             _last = node;
//         }
//         else
//         {
//             _last->setNext(node);
//             _last = node;
//         }
//     }

//     T* remove(T* node, T* prev)
//     {
//         if (prev)
//         {
//             prev->setNext(node->getNext());

//             return prev;
//         }
//         else _first = node->getNext();

//         return node;
//     }

//     T* getFirst() const { return _first; }

//   private:

//     T* _first = nullptr;
//     T* _last = nullptr;
    
// };

#endif
