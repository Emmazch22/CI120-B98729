#include "../include/Simulator.h"

Simulator::Simulator() {}

Simulator::Simulator(size_t sets, size_t blocks, size_t k_bytes, size_t strategy_one, size_t strategy_two, size_t algorithm, size_t access_time, size_t next_level_access, std::string file)
{
    this->sets = sets;
    this->blocks = blocks;
    this->k_bytes = k_bytes;
    this->strategy_one = strategy_one;
    this->strategy_two = strategy_two;
    this->access_time = access_time;
    this->next_level_access = next_level_access;
    this->hits = 0;
    this->misses = 0;
    this->total_cycles = 0;
    this->total_instructions = 0;
    this->file = file;
    this->cache = new Cache(sets, blocks);
    this->cache->setType(getCacheType());
    this->main_memory = new Main_Memory(blocks);
}

Simulator::~Simulator()
{
    this->tokens.clear();
    this->instructions.clear();
    this->binary_instructions.clear();
    this->instruction_operations.clear();
    this->offsets.clear();
    this->indexes.clear();
    this->tags.clear();
}

/**
 * @brief Set the placement policie of the cache
 * @param sets amount of sets in the cache 
 * @param blocks amount of blocks in the cache
 */
void Simulator::setCacheType(size_t sets, size_t blocks)
{
    if (sets >= 1 && blocks == 1)
    {
        this->cache_type = 0; /* direct-mapped */
    }
    else if (sets == 1 && blocks >= 1)
    {
        this->cache_type = 2; /* fully-asociative */
    }
}
/**
 * @brief returns the placement police of the cache
 * @return 0 for direct mapped, 1 for fully asociative
 */
size_t Simulator::getCacheType()
{
    return this->cache_type;
}
/**
 * @brief read the input file and copy the instructions into a vector
 */
void Simulator::readFromFile()
{
    std::string temp;
    std::ifstream readFile(this->file);

    while (getline(readFile, temp))
    {
        this->tokens.push_back(temp);
    }
    this->total_instructions = this->tokens.size();
}
/**
 * @brief separates the instruction into the operant (l or s) and the 32 bit string
 */
void Simulator::separateInstruction()
{
    std::string temp = "";
    size_t first_blank;
    size_t first_comma;

    //Separates only the instruction and saves them into a new vector
    for (auto value : this->tokens)
    {
        first_blank = value.find_first_of(' ');
        first_comma = value.find_first_of(',');
        temp = value.substr(first_blank + 1, first_comma - 2);
        this->instructions.push_back(temp);
    }
}

/**
 * @brief process the instruction to get the type (Load or Store) and the tag, index and offset of the 32 bit string
 */
void Simulator::processInstruction()
{
    size_t offset_size;
    size_t index_size;
    size_t tag_size;
    size_t counter = 0;
    std::string temp = "";
    //Getting the operations of the instruction, and saving them into a vector
    for (auto value : this->tokens)
    {
        if (value.at(0) == 'L' || value.at(0) == 'L')
        {
            this->instruction_operations.push_back(0);
        }
        else if (value.at(0) == 'S' || value.at(0) == 's')
        {
            this->instruction_operations.push_back(1);
        }
    }

    //Convert the instruction into 32 bits string
    for (auto value : this->instructions)
    {
        for (size_t i = 0; i < value.length(); ++i)
        {
            temp += hexToBinary(value.at(i));
        }
        this->binary_instructions.push_back(temp);
        temp = "";
    }
    //Divide the 32 bit string into tag, index and offset
    offset_size = log2(this->k_bytes);
    index_size = log2(this->sets);
    tag_size = 32 - offset_size - index_size;

    for (auto value : this->binary_instructions)
    {
        this->offsets.push_back(value.substr(value.length() - offset_size, value.length()));
        this->tags.push_back(value.substr(0, tag_size));
        this->indexes.push_back(value.substr(tag_size, index_size));
    }
}

/**
 * @brief convert a hexadecimal character to a 4 bits string
 * @param hex the hexadecimal character
 * @return the 4 bits string
 */
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

/**
 * @brief depending of the placement policy of the cache, this select the correspondent method
 */
void Simulator::write()
{
    if (getCacheType() == 0)
    {
        //Direct Mapping
        directMappedWrite();
    }
    else if (getCacheType() == 1)
    {
        //Fully Associative
        fullyAssociativeWrite();
    }
}

/**
 * @brief writes into the cache using the direct mapped policy
 */
void Simulator::directMappedWrite()
{
    size_t numerical_index = -1;
    for (size_t i = 0; i != this->instruction_operations.size(); ++i)
    {
        //If this operation is Load
        numerical_index = binaryToDec(this->indexes[i]);

        if (this->instruction_operations[i] == 0)
        {
            if (this->cache->isValid(numerical_index) == 0)
            {
                this->misses++;
                this->total_cycles++;
                this->events.push_back("Miss");
                this->cache->writeData(this->tags[i], numerical_index);
                this->cycles_per_instruction.push_back(this->next_level_access + this->access_time);
            }
            else
            {
                if (this->tags[i].compare(this->cache->getTag(numerical_index)) != 0)
                {
                    this->events.push_back("Miss");
                    this->misses++;
                    this->total_cycles++;
                    //replaces the tag at the cache index
                    this->cache->writeData(this->tags[i], numerical_index);
                    this->cycles_per_instruction.push_back(this->access_time);
                }
                else
                {
                    this->events.push_back("Hit");
                    this->hits++;
                    this->total_cycles;
                    this->cycles_per_instruction.push_back(this->access_time);
                }
            }
        }
        else
        {
            if (this->tags[i].compare(this->cache->getTag(numerical_index)) != 0)
            {
                this->misses++;
                this->total_cycles++;
                this->events.push_back("Miss");
                this->cycles_per_instruction.push_back(this->access_time);
            }
            else
            {
                this->hits++;
                this->total_cycles++;
                this->events.push_back("Hit");
                this->cycles_per_instruction.push_back(this->access_time);
            }
        }
    }
}
/**
 * @brief writes into the cache using the fully asociative policy
 */
void Simulator::fullyAssociativeWrite()
{
}

/**
 * @brief convert a binary string to a integer
 * @param binary the binary string to convert
 * @return the decimal corresponding to the string
 */
size_t Simulator::binaryToDec(std::string binary)
{
    return (size_t)stoi(binary, 0, 2);
}

/**
 * @brief executes all the functions necessaries to simulate the cache
 */
void Simulator::run()
{
    setCacheType(this->sets, this->blocks);
    readFromFile();
    separateInstruction();
    processInstruction();
    write();
    print_Results();
}

/**this->total_cycles
 * @brief prints using the results using the standart output 
 */
void Simulator::print_Results()
{
    long sum = 0;
    if (getCacheType() == 0)
    {
        std::cout << "Simulated for a Direct Mapped Cache" << std::endl;
    }
    else
    {
        std::cout << "Simulated for a Fully Associative Cache" << std::endl;
    }

    std::cout << "\nInstructions \t Cycles \t Events" << std::endl;
    for (size_t i = 0; i != this->instruction_operations.size(); ++i)
    {
        std::cout << this->tokens[i] << "\t\t" << this->cycles_per_instruction[i] << "\t\t" << this->events[i] << std::endl;
        sum += this->cycles_per_instruction[i];
    }
    std::cout << "\n==============================" << std::endl;
    std::cout << "Total Cycles: " << sum << std::endl; //Determinar cuando se baja al siguiente nivel de la cache
    std::cout << "Total Hits: " << this->hits << std::endl;
    std::cout << "Total Misses. " << this->misses << std::endl;
}