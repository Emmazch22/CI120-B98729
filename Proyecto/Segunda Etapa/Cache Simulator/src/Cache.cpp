#include "../include/Cache.h"
#include <string.h>

Cache::Cache()
{
    this->type = 0;
    this->blocks = 0;
}

Cache::Cache(size_t sets, size_t blocks)
{
    this->sets = sets;
    this->blocks = blocks;
    this->set = new set_t[sets];
    init(sets, blocks);
}

Cache::~Cache()
{
    delete[] this->set;
    for (size_t i = 0; i < this->sets; ++i)
    {
        delete[] this->set[i].block;
    }
}

void Cache::setType(size_t)
{
    this->type = type;
}

size_t Cache::getType()
{
    return this->type;
}

void Cache::init(size_t sets, size_t blocks)
{
    size_t result = 0;
    if (getType() == 0)
    {
        this->set->block = new block_t[1];
    }
    else if (getType() == 2)
    {
        this->set->block = new block_t[blocks];
    }
}