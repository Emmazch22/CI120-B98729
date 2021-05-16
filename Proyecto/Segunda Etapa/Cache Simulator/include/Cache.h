#pragma once
#include <string>

typedef struct {
    size_t tag;
    bool dirty = 0;
    std::string data;
} block_t;

typedef struct {
    block_t * block;
} set_t;

class Cache {
    private:
        size_t type;
        size_t sets;
        size_t blocks;
        void init(size_t, size_t);
        set_t * set;
    public:
        Cache();
        Cache(size_t, size_t);
        ~Cache();
        void setType(size_t);
        size_t getType();
};