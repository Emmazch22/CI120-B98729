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

/**
 * @brief sets the placement policy of this cache
 * @param type placement policy of the cache, 0 for direct mapped, 1 for fully associative
 */
void Cache::setType(size_t type)
{
    this->type = type;
}

/**
 * @brief returns the placement policy of the cache
 * @return 0 for direct mapped, 1 for fully associative
 */
size_t Cache::getType()
{
    return this->type;
}

/**
 * @brief determine to which set the block belongs
 * @param block a value associated to the cache block (index)
 * @return returns in which set the block is located
 */
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