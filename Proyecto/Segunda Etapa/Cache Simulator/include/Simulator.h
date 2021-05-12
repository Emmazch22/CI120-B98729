#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <string.h>

class Simulator {
    private:
        size_t sets;
        size_t blocks;
        size_t k_bytes;
        size_t strategy_one;
        size_t strategy_two;
        size_t algorithm;
        size_t cache_type;
        size_t instruction_type;
        std::string file;
        std::vector <std::string> tokens;
        std::vector <std::string> instruction_operations;
        void setCacheType(size_t, size_t);
        void readFromFile(std::string);
        void separateInstruction(std::vector <std::string>);
        std::string hexToBinary(char);

        //Cache cache;
    public:
        Simulator();
        Simulator(size_t, size_t, size_t, size_t, size_t, size_t, std::string);
        ~Simulator();
        size_t getCacheType();
        void run();
        
};