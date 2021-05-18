#pragma once
#include "Cache.h"
#include "Main_Memory.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <math.h>

class Simulator {
    private:
        Cache * cache;
        Main_Memory * main_memory;
        size_t sets;
        size_t blocks;
        size_t k_bytes;
        size_t strategy_one;
        size_t strategy_two;
        size_t algorithm;
        size_t cache_type;
        size_t instruction_type;
        size_t access_time;
        size_t next_level_access;
        size_t misses;
        size_t hits;
        size_t total_cycles;
        size_t evictions;
        size_t total_instructions;
        std::string file;
        std::vector <std::string> tokens;
        std::vector <std::string> instructions;
        std::vector <std::string> binary_instructions; 
        std::vector <size_t> instruction_operations;
        std::vector <std::string> offsets;
        std::vector <std::string> indexes;
        std::vector <std::string> tags;
        std::vector <std::string> events; 
        std::vector <size_t> cycles_per_instruction;
        void setCacheType(size_t, size_t);
        void readFromFile();
        void separateInstruction();
        void processInstruction();
        void directMappedWrite();
        void fullyAssociativeWrite();
        size_t binaryToDec(std::string);
        std::string hexToBinary(char);

    public:
        Simulator();
        Simulator(size_t, size_t, size_t, size_t, size_t, size_t, size_t , size_t, std::string);
        ~Simulator();
        size_t getCacheType();
        void print_Results();
        void write();
        void run();
        
};