#pragma once
#include <string>

typedef struct {
    std::string tag;
    size_t valid;
    size_t dirty;
} block_t;
class Cache {
    private:
        size_t type;
        size_t sets;
        size_t blocks;
        size_t size;
        block_t * cache;
    public:
        Cache();
        Cache(size_t, size_t);
        ~Cache();
        void setType(size_t);
        size_t getSet(size_t);
        size_t getType();
        void writeData(std::string, size_t);
        bool searchInCache(std::string);
        std::string getTag(size_t);
        bool isDirty(size_t);
        bool isValid(size_t);
};