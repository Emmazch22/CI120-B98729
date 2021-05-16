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

void Main_Memory::setData(size_t data, size_t index)
{
    this->memory[index] = data;
}

size_t Main_Memory::getData(size_t index)
{
    return this->memory[index];
}

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