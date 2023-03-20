#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <iostream>
#include <stdio.h>

template <class T> class LinkedList 
{
    private: /* Types*/ 
        struct Data_t{
            T* data;
            T* next;
        };

    public: 
        LinkedList() {}


        Data_t m_data;
};


#endif