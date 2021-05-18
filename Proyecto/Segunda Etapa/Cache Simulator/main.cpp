/** 
 * @brief Simulator of a cache
 * 
 * @author Emmanuel Zúñiga Chaves - B98729
 * Contact: emmanuel.zunigachaves@ucr.ac.cr
*/

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <fstream>
#include "include/Simulator.h"
using namespace std;

string write_allocate = "write-allocate";
string no_write_allocate = "no-write-allocate";
string write_through = "write-through";
string write_back = "write-back";
string least_recently_used = "lru";
string first_in_first_out = "fifo";
string random_s = "random";

bool isPowerOfTwo(size_t);
size_t getStrategy(string);
size_t getAlgorithm(string);

int main(int argc, char *argv[])
{
    size_t sets;
    size_t blocks;
    size_t k_bytes;
    size_t strategyOne;
    size_t strategyTwo;
    size_t algorithm;
    size_t access_time;
    size_t next_level_access;
    string file;
    if (argc > 9)
    {
        sets = (size_t)strtoul(argv[1], NULL, 10);
        blocks = (size_t)strtoul(argv[2], NULL, 10);
        k_bytes = (size_t)strtoul(argv[3], NULL, 10);

        if (!isPowerOfTwo(sets) || !isPowerOfTwo(blocks) || !isPowerOfTwo(k_bytes) || !k_bytes >= 4)
        {
            cout << "Error, Invalid parameters, the numerical arguments must be power of two, non negatives." << endl;
            exit(0);
        }

        if (getStrategy(argv[4]) == -1 || getStrategy(argv[5]) == -1)
        {
            cout << "Error, Invalid strategy" << endl;
            exit(0);
        }
        else
        {
            if ((getStrategy(argv[4]) == 0 && getStrategy(argv[5]) == 3) || (getStrategy(argv[4]) == 3 && getStrategy(argv[5]) == 0))
            {
                cout << "Error, invalid combination of parameters" << endl;
                exit(0);
            }
            strategyOne = getStrategy(argv[4]);
            strategyTwo = getStrategy(argv[5]);
        }
        algorithm = getAlgorithm(argv[6]);
        access_time = (size_t)strtoul(argv[7], NULL, 10);
        next_level_access = (size_t)strtoul(argv[8], NULL, 10);
        file = string(argv[9]);
    }
    else
    {
        cout << "Error, Invalid number of parameters." << endl;
        cout << "Usage: ./simulator.out <sets> <blocks> <bytes> <strategy one> <strategy two> <replacement algorithm> <access time (cycles)> <next level access time(cyles)> <file>" << endl;
        exit(0);
    }
    Simulator simulator(sets, blocks, k_bytes, strategyOne, strategyTwo, algorithm, access_time, next_level_access,file);
    simulator.run();

    return 0;
}

/**
 * @brief determinated if a number is a power of two
 * @param  n the number to evaluate
 * @return 0 if is not a power of two, 1 if it is
 */
bool isPowerOfTwo(size_t n)
{
    if (n <= 0)
    {
        return false;
    }
    return (ceil(log2(n)) == floor(log2(n)));
}

/**
 * @brief compare the string with the name of the strategies 
 * @param strategy a string to determinate which strategy the cache will use
 * @return a number related to the strategy
 */
size_t getStrategy(string strategy)
{
    size_t result = -1;
    if ( strategy.compare(no_write_allocate) == 0)
    {
        result = 0;
    }
    else if ( strategy.compare(write_allocate) == 0)
    {
        result = 1;
    }
    else if ( strategy.compare(write_through) == 0)
    {
        result = 2;
    }
    else if ( strategy.compare(write_back) == 0)
    {
        result = 3;
    }
    return result;
}

/**
 * @brief compare the string with the name of the replacement algorithms 
 * @param algorithm a string to determinate which replacement algorithm the cache will use
 * @return a number related to the algorithm
 */
size_t getAlgorithm(string algorithm)
{
    size_t result = -1;
    if ( algorithm.compare(least_recently_used) == 0)
    {
        result = 0;
    }
    else if ( algorithm.compare(first_in_first_out) == 0)
    {
        result = 1;
    }
    else if ( algorithm.compare(random_s) == 0)
    {
        result = 2;
    }
    return result;
}