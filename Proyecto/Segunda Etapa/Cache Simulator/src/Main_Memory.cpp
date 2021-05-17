#include "../include/Main_Memory.h"

Main_Memory::Main_Memory()
{
    this->size = 0;
}

Main_Memory::Main_Memory(size_t size)
{
    this->size = size;
    this->memory = new size_t[size];
    memset(this->memory, 0, sizeof(this->memory));
}

Main_Memory::~Main_Memory()
{
    this->size = 0;

    delete[] this->memory;
}

/**
 * @brief assign a data to a specific block of the memory
 * @param data assigned data to save into the memory
 * @param index specific block of the memory where the data it is going to be stored
 */
void Main_Memory::setData(size_t data, size_t index)
{
    this->memory[index] = data;
}
/**
 * @brief returns the data located in a specific memory block
 * @param index specific block of the memory
 * @return data stored in the memory block
 */
size_t Main_Memory::getData(size_t index)
{
    return this->memory[index];
}

/**
 * @brief determinates if the data is stored in the memory
 * @param data information to be searched in the memory
 * @return 0 if the data is not in the memory, 1 if it is stored
 */
bool Main_Memory::searchData(size_t data)
{
    bool exists = false;
    for (size_t i = 0; i < this->size; ++i)
    {
        if (this->memory[i] == data)
        {
            exists = true;
        }
    }
    return false;
}
