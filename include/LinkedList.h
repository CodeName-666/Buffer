#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <stdio.h>

/**
 * @brief The ListEntry class
 */
template <class T> class ListEntry
{
public:
    ListEntry() : m_next(NULL) {}
    ListEntry(T& data) : m_data(&data), m_next(NULL) {}
    ListEntry(T data): m_data(data), m_next(NULL){}

    /**
     * @brief data
     * @param data
     */
    void data(T& data) { m_data = data;}

    /**
     * @brief data
     * @return
     */
    T* data(void) {return &m_data;}

    /**
     * @brief next
     * @return
     */
    ListEntry<T>* next(void) {return m_next;}

    /**
     * @brief next
     * @param next
     */
    void next(ListEntry<T>& next) { m_next  = &next;}

    /**
     * @brief isNext
     * @return
     */
    bool isNext(void) {return m_next != NULL ? true: false;}

private:
    T m_data;
    ListEntry<T>* m_next;

};


/**
 * @brief The LinkedList class
 */
template <class T> class LinkedList
{
public:

        /**
         * @brief LinkedList
         */
        LinkedList() :m_list_data(), m_list_size(0)
        {

        }

        /**
         * @brief pop_front
         */
        void pop_front(void) {

        }

        /**
         * @brief pop_back
         */
        void pop_back(void)
        {

        }

        /**
         * @brief insert
         * @param pos
         * @param entry
         */
        void insert(uint16_t pos,ListEntry<T>& entry)
        {
            ListEntry<T>* e = index(pos);
            ListEntry<T>* current_next = e->next();

            e->next(entry);
            entry.next(current_next);
            m_list_size++;

            return;
        }

        /**
         * @brief clear
         */
        void clear(void){
            m_list_data = NULL;
            m_list_size = 0;
            return;
        }

        /**
         * @brief erase
         * @param pos
         */
        void erase(uint16_t pos)
        {
            ListEntry<T>* ref_enty = index(pos - 1);
            ListEntry<T>* pos_entry = ref_enty->next();
            ListEntry<T>* after_entry = pos_entry->next();

            ref_enty->next(after_entry);
            m_list_size--;
            return;
        }

        /**
         * @brief push_front
         * @param entry
         */
        void push_front(ListEntry<T>& entry)
        {
            ListEntry<T>* e = m_list_data->isNext();
            m_list_data = &entry;
            m_list_data->next(e);
            m_list_size++;
            return;
        }

        /**
         * @brief push_back
         * @param entry
         */
        void push_back(ListEntry<T>& entry)
        {
           if(m_list_data == NULL)
           {
               m_list_data = &entry;
           }
           else
           {
               ListEntry<T>* e  = last();
               e->next(entry);
           }
           m_list_size++;
           return;
        }
        
        /**
         * @brief size
         * @return
         */
        uint16_t size(void) {return m_list_size;}

        /**
         * @brief at
         * @param pos
         * @return
         */
        T* at(uint16_t pos) {
            ListEntry<T>* entry = index(pos);
            return entry->data();
        };

    private:
        ListEntry<T>* last(void) {
            ListEntry<T>* entry = m_list_data;
            while(entry->isNext())
            {
                 entry = entry->next();
            }
            return entry;
        }

        ListEntry<T>* index(uint16_t pos) {
            ListEntry<T>* entry = m_list_data;
            for(uint16_t i = 0; (i < pos && pos < m_list_data && entry->isNext()); i++)
            {
                entry = entry->next();
            }

            return entry;
        }



    private:
        ListEntry<T>* m_list_data;
        uint16_t m_list_size;
};


#endif
