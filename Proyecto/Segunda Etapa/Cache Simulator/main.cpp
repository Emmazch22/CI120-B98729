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
    string file;

    if (argc > 7)
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
        file = string(argv[7]);
    }
    else
    {
        cout << "Error, Invalid number of parameters." << endl;
        cout << "Usage: ./simulator.out <sets> <blocks> <bytes> <strategy one> <strategy two> <remplacement algorithm> <file>" << endl;
        exit(0);
    }

    Simulator simulator(sets, blocks, k_bytes, strategyOne, strategyTwo, algorithm, file);

    return 0;
}

bool isPowerOfTwo(size_t n)
{
    if (n <= 0)
    {
        return false;
    }
    return (ceil(log2(n)) == floor(log2(n)));
}

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