
#ifndef RING_BUFFER_H
#define RING_BUFFER_H
#include <iostream>
#include <stdio.h>

/**
 * @enum Direction_e
 * @brief Enumeration for the direction of the ring buffer operations.
 *
 * This enum defines two possible directions for ring buffer navigation:
 * - DIR_FORWARD: Indicates forward navigation.
 * - DIR_BACKWARD: Indicates backward navigation.
 */
enum Direction_e
{
    DIR_FORWARD = 0, ///< Forward direction.
    DIR_BACKWARD = 1 ///< Backward direction.
};

/**
 * @class RingBuffer
 * @brief A template class for implementing a circular buffer (ring buffer).
 *
 * This class allows for efficient handling of data in a circular manner. It provides
 * functionalities to add, retrieve, and navigate elements in the buffer while maintaining
 * a fixed size.
 *
 * @tparam T The type of elements stored in the buffer.
 */
template <class T>
class RingBuffer
{
public:
    /**
     * @brief Construct a new Ring Buffer object.
     *
     * @param size_of_buffer The total size of the buffer.
     * @param start_index The starting index within the buffer. Defaults to 0.
     * @param direction The direction of navigation in the buffer. Defaults to DIR_FORWARD.
     */
    explicit RingBuffer(uint16_t size_of_buffer,
                        uint16_t start_index = 0,
                        Direction_e direction = DIR_FORWARD) : m_current_idx(start_index),
                                                               m_buffer_size(size_of_buffer),
                                                               m_direction(direction)
    {
        m_buffer_data = new T[size_of_buffer];
    }

    /**
     * @brief Add an element to the buffer at a specific index (rvalue overload).
     *
     * @param idx The index to insert the element at.
     * @param data The data to be inserted.
     */
    void add(uint16_t idx, T &&data)
    {
        if (idx < m_buffer_size)
        {
            m_buffer_data[idx] = data;
        }
    }

    /**
     * @brief Add an element to the buffer at a specific index (lvalue overload).
     *
     * @param idx The index to insert the element at.
     * @param data The data to be inserted.
     */
    void add(uint16_t idx, T &data)
    {
        if (idx < m_buffer_size)
        {
            m_buffer_data[idx] = data;
        }
    }

    /**
     * @brief Add an element to the current index of the buffer (rvalue overload).
     *
     * @param data The data to be inserted.
     * @param move_next_idx Indicates whether to move to the next index after insertion. Defaults to true.
     */
    void add(T &&data, bool move_next_idx = true)
    {
        m_buffer_data[m_current_idx] = data;
        if (move_next_idx)
            moveNext();
    }

    /**
     * @brief Move the buffer to a specific index.
     *
     * @param index The index to move to.
     */
    void moveToIndex(uint16_t index)
    {
        if (index < m_buffer_size)
            m_current_idx = index;
    }

    /**
     * @brief Add an element to the current index of the buffer (lvalue overload).
     *
     * @param data The data to be inserted.
     * @param move_next_idx Indicates whether to move to the next index after insertion. Defaults to true.
     */
    void add(T &data, bool move_next_idx = true)
    {
        m_buffer_data[m_current_idx] = data;
        if (move_next_idx)
            moveNext();
    }

    /**
     * @brief Move the buffer by a specific offset.
     *
     * @param offset The offset to move. Positive values move forward, and negative values move backward.
     */
    void move(int16_t offset)
    {
        setOffset(offset);
    }

    /**
     * @brief Move to the next index in the buffer.
     */
    void moveNext(void)
    {
        setOffset(+1);
    }

    /**
     * @brief Move to the previous index in the buffer.
     */
    void movePrevious(void)
    {
        setOffset(-1);
    }

    /**
     * @brief Get the length of the buffer.
     *
     * @return uint16_t The length of the buffer.
     */
    uint16_t length(void) { return m_buffer_size; }

    /**
     * @brief Access the element at a specific index.
     *
     * @param idx The index to access.
     * @return T& A reference to the element at the specified index.
     */
    T &atIndex(uint16_t idx)
    {
        if (idx < m_buffer_size)
            return m_buffer_data[idx];
        else
            return m_buffer_data[0];
    }

    /**
     * @brief Access the element at a specific offset.
     *
     * @param offset The offset from the current index.
     * @return T& A reference to the element at the specified offset.
     */
    T &at(int16_t offset)
    {
        uint16_t idx = 0;
        if (m_direction == DIR_FORWARD)
            idx = calculateIndex(offset);
        else
            idx = calculateIndex(-1 * offset);

        return m_buffer_data[idx];
    }

    /**
     * @brief Get the current element in the buffer.
     *
     * @return T& A reference to the current element.
     */
    T &current(void)
    {
        return m_buffer_data[m_current_idx];
    }

    /**
     * @brief Get the current direction of navigation.
     *
     * @return Direction_e The current direction.
     */
    Direction_e direction(void) { return m_direction; }

    /**
     * @brief Set the direction of navigation.
     *
     * @param direction The new direction to set.
     */
    void direction(Direction_e direction) { m_direction = direction; }

    /**
     * @brief Get the current index of the buffer.
     *
     * @return uint16_t The current index.
     */
    uint16_t currentIdx(void) { return m_current_idx; }

    /**
     * @brief size
     * @return
     */
    uint16_t size(void) { return m_list_size; }


private:
    /**
     * @brief Update the current index by a specified offset.
     *
     * @param offset The offset to apply.
     */
    void setOffset(int16_t offset)
    {
        if (m_direction == DIR_FORWARD)
            m_current_idx = calculateIndex(offset);
        else
            m_current_idx = calculateIndex(-1 * offset);
    }

    /**
     * @brief Calculate the index based on an offset.
     *
     * @param offset The offset to calculate.
     * @return int16_t The calculated index.
     */
    int16_t calculateIndex(int16_t offset)
    {
        int16_t c = ((int16_t)m_current_idx + offset) % m_buffer_size;
        if (c < 0)
            c = m_buffer_size + c;
        return (uint16_t)c;
    }

private:
    T *m_buffer_data;        ///< Pointer to the buffer data array.
    uint16_t m_current_idx;  ///< Current index within the buffer.
    uint16_t m_buffer_size;  ///< Total size of the buffer.
    Direction_e m_direction; ///< Current direction of navigation.
};

#endif
