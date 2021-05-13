#include "../include/Simulator.h"

Simulator::Simulator() {}

Simulator::Simulator(size_t sets, size_t blocks, size_t k_bytes, size_t strategy_one, size_t strategy_two, size_t algorithm, std::string file)
{
    this->sets = sets;
    this->blocks = blocks;
    this->k_bytes = k_bytes;
    this->strategy_one = strategy_one;
    this->strategy_two = strategy_two;
    this->file = file;
    this->cache = new Cache(sets, blocks);
    this->cache->setType(getCacheType());
}

Simulator::~Simulator() 
{
    delete this->cache;
}

void Simulator::setCacheType(size_t sets, size_t blocks)
{
    if (sets >= 1 && blocks == 1)
    {
        this->cache_type = 0; /* direct-mapped */
    }
    else if (sets >= 1 && blocks >= 1)
    {
        this->cache_type = 1; /* m-way set-associative */
    }
    else if (sets == 1 && blocks >= 1)
    {
        this->cache_type = 2; /* fully-asociative */
    }
}

size_t Simulator::getCacheType()
{
    return this->cache_type;
}

void Simulator::readFromFile(std::string file)
{
    std::string temp;
    std::ifstream readFile(file);

    while (getline(readFile, temp, ' '))
    {
        tokens.push_back(temp);
    }

    /* Verifying the instruction */
    if (this->tokens[0].compare("l") == 0)
    {
        this->instruction_type = 0; /* load */
    }
    else if (this->tokens[0].compare("r") == 0)
    {
        this->instruction_type = 1; /* read */
    }
    else
    {
        std::cout << "Error, invalid instruction type. Must be l or r" << std::endl;
        exit(0);
    }
}

void Simulator::separateInstruction(std::vector<std::string> tokens)
{
    char instructions_bytes[8];
    std::vector<char> aux_vector(tokens[1].begin() + 2, tokens[1].end());

    for (size_t i = 0; i < 8; ++i)
    {
        instructions_bytes[i] = aux_vector[i];
    }

    for (size_t i = 0; i < 8; ++i)
    {
        this->instruction_operations.push_back(hexToBinary(instructions_bytes[i]));
    }
}

std::string Simulator::hexToBinary(char hex)
{
    std::string result = "";
    switch (hex)
    {
    case '0':
        result += "0000";
        break;
    case '1':
        result += "0001";
        break;
    case '2':
        result += "0010";
        break;
    case '3':
        result += "0011";
        break;
    case '4':
        result += "0100";
        break;
    case '5':
        result += "0101";
        break;
    case '6':
        result += "0110";
        break;
    case '7':
        result += "0111";
        break;
    case '8':
        result += "1000";
        break;
    case '9':
        result += "1001";
        break;
    case 'a':
    case 'A':
        result += "1010";
        break;
    case 'b':
    case 'B':
        result += "1011";
        break;
    case 'c':
    case 'C':
        result += "1100";
        break;
    case 'd':
    case 'D':
        result += "1101";
        break;
    case 'e':
    case 'E':
        result += "1110";
        break;
    case 'f':
    case 'F':
        result += "1111";
        break;
    default:
        std::cout << "Error, invalid format of instruction. Must be 32 bits hexadecimal word." << std::endl;
        exit(0);
        break;
    }
    return result;
}

void Simulator::run()
{
    setCacheType(this->sets, this->blocks);
    readFromFile(this->file);
    separateInstruction(this->tokens);
}