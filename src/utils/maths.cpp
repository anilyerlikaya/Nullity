#include "maths.h"

/*
 * Check if value is between start and end
 */
template <typename T>
bool isBetween(T val, T start, T end) {
    if(val < start || val > end)
        return false;
    return true;
}