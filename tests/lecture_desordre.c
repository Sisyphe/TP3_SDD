#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* file=fopen("matrix.dat","r");
    matrix_t matrix=readFromFile(file);
    fclose(file);
    printTable(&matrix);
    freeTable(&matrix);

    return 0;
}