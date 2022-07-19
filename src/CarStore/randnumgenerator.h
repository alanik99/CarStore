#pragma once

#include <ctime>
#include <cmath>
#include <cassert>

class RandNumGenerator
{
public:
    RandNumGenerator()
    {
        srand(time(0));
    }

    int genRandInt( int min, int max )
    {
        assert(min <= max && "max must be greater than or equal to min");

        return rand() % (max - min + 1)  +  min;
    }

    float genRandFloat( float min, float max )
    {
        assert(min <= max && "max must be greater than or equal to min");

        float random = ((float)rand()) / (float)RAND_MAX;
        float diff = max - min;

        return min + random * diff;
    }
};
