#ifndef HELPERS_H
#define HELPERS_H

#include <cstdint>

inline bool CompareArrays(uint16_t* arrayA, uint16_t* arrayB, unsigned int size)
{
    for(unsigned int index = 0; index < size; index++)
    {
        if(arrayA[index] != arrayB[index])
        {
            return false;
        }
    }

    return true;
}

#endif // HELPERS_H
