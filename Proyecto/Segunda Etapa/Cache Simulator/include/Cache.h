#pragma once
#include <string>

typedef struct {
    size_t tag;
    size_t dirty;
    size_t data;
} block_t;
class Cache {
    private:
        size_t type;
        size_t sets;
        size_t blocks;
        block_t * cache;
    public:
        Cache();
        Cache(size_t, size_t);
        ~Cache();
        void setType(size_t);
        size_t getSet(size_t);
        size_t getType();
        void writeData(size_t, size_t);
};