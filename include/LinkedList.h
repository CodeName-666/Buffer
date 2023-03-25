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

    void reset_next(void) {m_next = NULL;}
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
            if(pos < m_list_size)
            {
                ListEntry<T>* e = at_index(pos);
                ListEntry<T>* current_next = e->next();

                e->next(entry);
                entry.next(current_next);
                m_list_size++;
            }
            else
            {
                push_back(entry);
            }

            return;
        }

        /**
         * @brief clear
         */
        void clear(void){
            for(uint16_t i = m_list_size-1; i >= 0; i--)
            {
                erase(i);
            }
            return;
        }

        /**
         * @brief erase
         * @param pos
         */
        void erase(uint16_t pos)
        {
            ListEntry<T>* ref_enty, *pos_entry,*after_entry;

            if(pos > 0)
            {
                //Get entry on at POS
                pos_entry = at_index(pos);
                //Get entry before POS
                ref_enty = at_index(pos - 1);
                //Get entry after POS
                after_entry = at_index(pos + 1);
                //Reset next pointer from entry at pos
                pos_entry->reset_next();
                //Switch position which mean, obj is deleted.
                ref_enty->next(*after_entry);
            }
            else
            {
                pos_entry = at_index(pos);
                pos_entry->reset_next();
            }
            m_list_size--;
            return;
        }

        /**
         * @brief push_front
         * @param entry
         */
        void push_front(ListEntry<T>& entry)
        {
            if(!exists(entry))
            {
                ListEntry<T>* e = m_list_data;
                m_list_data = &entry;
                m_list_data->next(*e);
                m_list_size++;
            }
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
                if(!exists(entry))
                {
                    ListEntry<T>* e  = last();
                    e->next(entry);
                }
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
            ListEntry<T>* entry = at_index(pos);
            return entry->data();
        };

        bool exists(ListEntry<T>& entry)
        {
            bool exist = false;
            ListEntry<T>* e = m_list_data;
            for(uint16_t i = 0; (i < m_list_size && e->isNext() && exist == false) ; i++)
            {
                e = e->next();
                if(e == &entry)
                {
                    exist = true;
                }
            }
            return exist;
        }
    private:
        ListEntry<T>* last(void) {
            ListEntry<T>* entry = m_list_data;
            while(entry->isNext())
            {
                 entry = entry->next();
            }
            return entry;
        }

        ListEntry<T>* at_index(uint16_t pos) {
            ListEntry<T>* entry = m_list_data;
            ListEntry<T>* ret = NULL;
            for(uint16_t i = 0; (i < pos && pos < m_list_size && entry->isNext()); i++)
            {
                entry = entry->next();
            }
            ret = entry;
            return ret;
        }

    private:
        ListEntry<T>* m_list_data;
        uint16_t m_list_size;
};


#endif
