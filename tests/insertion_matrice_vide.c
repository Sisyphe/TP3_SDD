#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* file=fopen("empty_matrix.dat","r");
    matrix_t matrix=readFromFile(file);
    fclose(file);
    addValue(&matrix,23,44,90);
    printTable(&matrix);
    freeTable(&matrix);

    return 0;
}