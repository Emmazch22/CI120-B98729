#pragma once
#include <cstddef>
#include <cstring>

class Main_Memory{
    private:
        size_t * memory;
        size_t size;
    public:
        Main_Memory();
        Main_Memory(size_t);
        ~Main_Memory();
        void setData(size_t, size_t);
        size_t getData(size_t);
        bool searchData(size_t);
};