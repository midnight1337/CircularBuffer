/*
Circular Buffer - FIFO algorithm, data is stored in a continous loop in a const length buffer that has a "connection" from end to beginning,
so oldest data can be replaced by new coming data. Each time we add data, write pointer moves forward, same with read data.
Circular buffer O notation is O(1).

Head indicates new space (index) to write
Tail indicates space (index) to read

API Design
    Initialize the circular buffer container with a size
    Be able to add data to the buffer
    Be able to get data from the buffer
    Reset the circular buffer container
    Need to know whether the buffer is full or empty
    Need to know the current size of the buffer

Write/Read Description step by step:
Write:
-Write data in buffer on current head index (1 indicates written space in buffer)
-If buffer full flag is true, then move tail (false by default)
-Move head
-Check if head index is same as tail, if so then buffer is full -> set true full flag
-Increase buffer size indicator

Read:
-If buffer is not empty, but tail equals to head, then buffer is empty, throw exception
-Save value from buffer by tail index in stack variable
-Write data in buffer on current tail index (0 indicates empty space in buffer)
-Set buffer flag to false as it wasn't full
-Decrease buffer size indicator
*/
#include <iostream>


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
    m_buffer = new int[size];    // declare uninitialised array of size elements
    m_head = 0;
    m_tail = 0;
    m_size = 0;
    m_isFull = false;
}

void CircularBuffer::write(int number)
{
    *(m_buffer + m_head) = number;

    if (m_isFull) {m_tail = (m_tail + 1) % m_buffer_size;}
    
    ((m_head + 1) == m_buffer_size) ? m_head = 0 : m_head++;

    m_isFull = (m_head == m_tail);
    
    (m_size == m_buffer_size) ? m_size = m_buffer_size : m_size++;
}

void CircularBuffer::read()
{
    if (!m_isFull && (m_head == m_tail))
    {
        throw std::runtime_error("Buffer is empty");
    }

    int value = *(m_buffer + m_tail);

    *(m_buffer + m_tail) = 0;
    
    ((m_tail + 1) == m_buffer_size) ? m_tail = 0 : m_tail++;
    // More cpu consuming but same as above, 
    // Every time we get to the end of the array we will automatically start back at zero: 
    // m_tail = (m_tail + 1) % m_buffer_size;

    m_isFull = false;

    (m_size == 0) ? m_size = 0 : m_size--;
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

    std::cout << "Buffer: " << std::endl;
    for (int i = 0; i < m_tail; i++)
    {
        std::cout << " ";
    }
    std::cout << "T" << std::endl;
    
    for (int i = 0; i < m_head; i++)
    {
        std::cout << " ";
    }
    std::cout << "H" << std::endl;
    
    for (int i = 0; i < m_buffer_size; i++)
    {
        std::cout << m_buffer[i];
    }
    std::cout << std::endl;
}


int main()
{
    const int buffer_size = 5;
    CircularBuffer circular_buffer = CircularBuffer(buffer_size);
    char choice;
    
    while (true)
    {
        circular_buffer.buffer_info();
        
        std::cin >> choice;
    
        switch(choice)
        {
            case 'w':
                circular_buffer.write(1);
                break;
            case 'r':
                circular_buffer.read();
                break;
            case 'x':
                circular_buffer.reset();
                break;
            default:
                continue;
        }
    }

    return 0;
}
