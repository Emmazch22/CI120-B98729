#include "../include/Simulator.h"

Simulator::Simulator(){}

Simulator::Simulator(size_t sets, size_t blocks, size_t k_bytes, size_t strategy_one, size_t strategy_two, size_t algorithm, std::string file){
    this->sets = sets;
    this->blocks = blocks;
    this->k_bytes = k_bytes;
    this->strategy_one = strategy_one;
    this->strategy_two = strategy_two;
    this->file = file;
    setCacheType(this->sets, this->blocks);
    readFromFile(this->file);   
}

Simulator::~Simulator(){}

void Simulator::setCacheType(size_t sets, size_t blocks){
    if ( sets >= 1 && blocks == 1 ){
        this->cache_type = 0; /* direct-mapped */
    } else if ( sets >= 1 && blocks >= 1 ){
        this->cache_type = 1; /* m-way set-associative */
    } else if ( sets == 1 && blocks >= 1 ){
        this->cache_type = 2; /* fully-asociative */
    }
}

size_t Simulator::getCacheType(){
    return this->cache_type;
}

void Simulator::readFromFile(std::string file){
    std::vector <std::string> tokens;
    std::string temp;
    std::ifstream readFile(file);

    while ( getline(readFile, temp, ' ') ){
        tokens.push_back(temp);
    }
    
    /* Verifying the instruction */
    if ( tokens[0].compare("l") == 0){
        this->instruction_type = 0; /* load */
    } else if ( tokens[0].compare("r") == 0){
        this->instruction_type = 1; /* read */
    } else {
        std::cout << "Error, invalid instruction type. Must be l or r" << std::endl;
        exit(0);
    }
    separateInstruction(tokens);

}

void Simulator::separateInstruction(std::vector <std::string> tokens){
    std::vector <char> instructions_bytes(tokens[1].begin(), tokens[1].end());
}