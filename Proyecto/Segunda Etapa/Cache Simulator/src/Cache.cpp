#include "../include/Cache.h"
#include <string.h>

Cache::Cache()
{
    this->type = 0;
    this->blocks = 0;
    this->size = 0;
}

Cache::Cache(size_t sets, size_t blocks)
{
    this->sets = sets;
    this->blocks = blocks;
    this->size = sets * blocks;
    this->cache = new block_t[size];
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

bool Cache::searchInCache(std::string data){
    bool exists = 0;
    for (size_t i = 0; i < this->size; ++i){
        if ( data.compare(this->cache[i].tag) ){
            exists = 1;
        }
    }
    return exists;
}

bool Cache::isDirty(size_t index){
    return this->cache[index].dirty == 1;
}

bool Cache::isValid(size_t index){
    return this->cache[index].valid == 1;
}

void Cache::writeData(std::string tag, size_t index){
    this->cache[index].tag = tag;
}

std::string Cache::getTag(size_t index){
    return this->cache[index].tag;
}