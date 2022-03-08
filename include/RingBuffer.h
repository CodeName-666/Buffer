#ifndef RING_BUFFER_H
#define RING_BUFFER_H
#include <iostream>
#include <stdio.h>

enum Direction_e
{
    DIR_FORWARD = 0,
    DIR_BACKWARD = 1
};

template <class T> class RingBuffer {
    
    public:
        /**
         * @brief Construct a new Ring Buffer object
         * 
         * @param size_of_buffer 
         * @param start_index 
         * @param direction 
         */
        explicit RingBuffer(uint16_t size_of_buffer, uint16_t start_index = 0, Direction_e direction = DIR_FORWARD) :
                                        m_current_idx(start_index),
                                        m_buffer_size(size_of_buffer),
                                        m_direction(direction)
                                        
        {
            m_buffer_data = new T[size_of_buffer];
        }

        /**
         * @brief 
         * 
         * @param idx 
         * @param data 
         */
        void add(uint16_t idx, T&& data)
        {
            if(idx < m_buffer_size)
            {
                m_buffer_data[idx] = data;
            }
        }

        /**
         * @brief 
         * 
         * @param idx 
         * @param data 
         */
        void add(uint16_t idx, T& data)
        {
            if(idx < m_buffer_size)
            {
                m_buffer_data[idx] = data;
            }
        }

        void add(T&& data, bool move_next_idx = true)
        {
            m_buffer_data[m_current_idx] = data;
            if(move_next_idx)
                moveNext();
        }
        
        void moveToIndex(uint16_t index)
        {
            if(index < m_buffer_size)
                m_current_idx = index;
        }
        /**
         * @brief 
         * 
         * @param data 
         * @param move_next_idx 
         */
        void add(T& data, bool move_next_idx = true)
        {
            m_buffer_data[m_current_idx] = data;
            if(move_next_idx)
                moveNext();
        } 

        /**
         * @brief Move the RingBuffer 
         * @param[in] offset Offset to move the RingBuffer
         * 
         * This method allows to move the ring buffer by the given offset. 
         * A positive value moves the ring buffer forward. 
         * A negative value moves the ring buffer backword.
         * 
         * Keep in mind the direction of the ring buffer. This flag allows 
         * to switch the direction.
         */
        void move(int16_t offset)
        {
            setOffset(offset);
        }

        /**
         * @brief Move to next RingBuffer entry
         */
        void moveNext(void) 
        {
            setOffset(+1);
        }

        /**
         * @brief Move to previous RingBuffer entry
         */
        void movePrevious(void)
        {
            setOffset(-1);
        }
        
        /**
         * @brief Lentgth of the RingBuffer
         * @return uint16_t 
         */
        uint16_t length(void) {return m_buffer_size;}
        
        /**
         * @brief Get T at index
         * @param[in] idx Index of the RingBuffer. Not the Offset
         * @return T Referenze to the required T parameter.
         */
        T& atIndex(uint16_t idx)
        {
            if(idx < m_buffer_size)
                return m_buffer_data[idx];
            else 
                return m_buffer_data[0];
        }

        /**
         * @brief Get T at offset
         * @param[in] offset Offest of the RingBuffer. Not the Index
         * @return T Referenze to the required T parameter.
         */
        T& at(int16_t offset)
        {
            uint16_t idx = 0;
            if(m_direction == DIR_FORWARD)
                idx = calculateIndex(offset);
            else 
                idx = calculateIndex(-1 * offset);
                
            return m_buffer_data[idx];
        }


        T& current(void) 
        {
            return m_buffer_data[m_current_idx];
        }

        /**
         * @brief Get the driection of the RingBuffer
         * @return Direction_e 
         */
        Direction_e direction(void) {return m_direction;}

        /**
         * @brief Set the Direction of the Ringbuffer
         * @param direction 
         */
        void direction(Direction_e direction) {m_direction = direction;}

        /**
         * @brief Get the current index of the ring buffer.
         * 
         * @return uint16_t 
         */
        uint16_t currentIdx(void) {return m_current_idx;}
    private: 
        /**
         * @brief Set a offset of the RingBuffer
         * @param[in] offset Index which should be set.
         */
        void setOffset(int16_t offset)
        {
            if(m_direction == DIR_FORWARD)
                m_current_idx = calculateIndex(offset);
            else 
                m_current_idx = calculateIndex(-1*offset);
        }
        
        /**
         * @brief Calulator of the index by given Offset
         * @param[in] offset Needed Offset
         * @return int16_t Calculated index
         */
        int16_t calculateIndex(int16_t offset)
        {
            int16_t c = ((int16_t)m_current_idx + offset) % m_buffer_size;
            if(c < 0)
                c = m_buffer_size + c;
            return (uint16_t)c;
        }
    private:    
        T* m_buffer_data;
        uint16_t m_current_idx;
        uint16_t m_buffer_size;
        Direction_e m_direction;
        
};


#endif
