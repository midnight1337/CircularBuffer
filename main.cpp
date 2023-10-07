#include <iostream>
/*
Circular Buffer - FIFO algorithm, data is placed in a buffer that has "connection" from end to beginning so old data can be replaced by new coming data.

Head indicates new space (index) to write
Tail indicates space (index) to read

API Design
    initialize the circular buffer container with a buffer and size
    reset the circular buffer container
    be able to add data to the buffer
    be able to get the next value from the buffer
    need to know whether the buffer is full or empty
    need to know the current number of elements in the buffer

Methods Description
Write:
-Write data on current index
-If buffer full flag is true, then move tail
-Move head
-Check if head index is same as tail, if so then buffer is full -> set true full flag

Read:
-If buffer is not empty, but tail equals to head, then buffer is empty, throw exception
-Save value from buffer by tail index in stack variable
-Write 0 in buffer on tail index (it indicates empty space in buffer)
-Set buffer flag to false as it wasn't full
*/


class CircularBuffer
{
    private:
        int* m_buffer;
        int m_head;
        int m_tail;
        int m_size;
        bool m_isFull;
        const int m_buffer_size;

    public:
        CircularBuffer(int size);
        void write(int number);
        void read();
        void reset();
        void buffer_info();
};

CircularBuffer::CircularBuffer(int size): m_buffer_size(size)
{
    m_head = 0;
    m_tail = 0;
    m_isFull = false;
    m_size = 0;
    m_buffer = new int[size];    // declare uninitialised array of size elements
}

void CircularBuffer::write(int number)
{
    *(m_buffer + m_head) = number;

    if (m_isFull) {m_tail = (m_tail + 1) % m_buffer_size;}

    m_head++;
    if (m_head == m_buffer_size) {m_head = 0;}

    m_isFull = (m_head == m_tail);

    m_size++;
    if (m_size > m_buffer_size) {m_size = m_buffer_size;}
}

void CircularBuffer::read()
{
    if (!m_isFull && (m_head == m_tail))   // buffer is empty, can't read
    {
        throw std::runtime_error("Buffer is empty");
    }

    int value = *(m_buffer + m_tail);

    *(m_buffer + m_tail) = 0;
    
    m_tail++;
    if (m_tail == m_buffer_size) {m_tail = 0;}
    // More cpu consuming but same as above, 
    // Every time we get to the end of the array we will automatically start back at zero: m_tail = (m_tail + 1) % m_buffer_size;

    m_isFull = false;

    m_size--;
    if (m_size < 0) {m_size = 0;}
}

void CircularBuffer::reset()
{
    delete[] m_buffer;

    m_buffer = new int[m_buffer_size];
    m_head = 0;
    m_tail = 0;
    m_size = 0;
    m_isFull = false;
}

void CircularBuffer::buffer_info()
{
    std::cout << "Head: " << m_head << std::endl;
    std::cout << "Tail: " << m_tail << std::endl;
    std::cout << "Size: " << m_size << std::endl;
    std::cout << "Peak: " << *(m_buffer + m_head) << std::endl;
    std::cout << "Bottom: " << *(m_buffer + m_tail)  << std::endl;
    std::cout << "isFull: " << m_isFull << std::endl;

    std::cout << "Buffer: ";
    for (int i = 0; i < m_buffer_size; i++)
    {
        std::cout << m_buffer[i] << " ";
    }
}


int main()
{
    int buffer_size = 5;
    CircularBuffer circular_buffer = CircularBuffer(buffer_size);
    
    circular_buffer.write(1);
    circular_buffer.write(1);
    circular_buffer.write(1);
    circular_buffer.write(1);
    circular_buffer.write(1);

    circular_buffer.read();

    circular_buffer.reset();
    circular_buffer.buffer_info();

    return 0;
}
