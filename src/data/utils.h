#pragma once

#include <stdlib.h>

/* Allocate size * T memory and initialize it as default_value */
template <typename T>
T* defloc( int size, T default_value) {
    T* temp = (T*) malloc(size * sizeof(T));

    for(int i=0; i<size; i++)
       temp[i] = default_value;

    return temp;
}

/* Reallocate memory */
template<typename T>
void reloc(T* ptr, int size){
    ptr = realloc(ptr, size * sizeof(T));

    return;
}