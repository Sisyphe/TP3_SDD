#include "matrix.h"

#define BUFFER_SIZE (1024)

matrix_t readFromFile(FILE * data_file)
{
    unsigned int major_table_size = 0;
    unsigned int row_number=0;
    unsigned int column_number=0;
    cell_type value;
    matrix_t matrix;
    char buffer[BUFFER_SIZE];

    /* Read major table size */
    fgets(buffer, BUFFER_SIZE, data_file);
    sscanf(buffer, "%u", &major_table_size);
    matrix.major_table = malloc(sizeof(major_table_cell_t) * major_table_size);
    matrix.major_table_size = 0;

    while(fgets(buffer, BUFFER_SIZE, data_file))
    {
        sscanf(buffer, "%u %u %d", &row_number,
                                   &column_number,
                                   &value);
        addValue(&matrix, row_number, column_number, value);
        matrix.major_table_size++;
    }

    return matrix;
}

void addValue(matrix_t * matrix,
              unsigned int row_number,
              unsigned int column_number,
              cell_type value)
{
    unsigned int major_table_index = 0;
    major_table_index = findMajorTableIndex(matrix, row_number);
    printf("index = %u\n", major_table_index);
}

unsigned int findMajorTableIndex(matrix_t * matrix, unsigned int row_number)
{
    unsigned int mean_index = 0;
    unsigned int min_index = 0;
    unsigned int max_index = matrix->major_table_size + 1;

    printf("max index = %u\n", max_index);
    /* TODO tester les effets de bord */
    while(min_index != max_index - 1)
    {
        mean_index = (min_index + max_index) / 2;
        /*printf("mean index = %u\n", mean_index);*/

        if(row_number > matrix->major_table[mean_index].row_number)
        {
            min_index = mean_index + 1;
        }
        else
        {
            max_index = mean_index;
        }
    }

    return min_index;
}