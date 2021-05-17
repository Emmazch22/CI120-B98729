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
    this->cache = new block_t[sets];
}

Cache::~Cache()
{
    delete[] this->cache;

}

void Cache::setType(size_t)
{
    this->type = type;
}

size_t Cache::getType()
{
    return this->type;
}

size_t Cache::getSet(size_t block){
    size_t set;
    if ( getType() == 0){
        set = block;
    } else if ( getType() == 1){
        set = 1;
    }
    return set;
}

void Cache::writeData(size_t tag, size_t index){

}