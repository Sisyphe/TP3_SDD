#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* file=fopen("empty_file.dat","r");
    matrix_t matrix=readFromFile(file);
    fclose(file);
    freeTable(&matrix);

    return 0;
}