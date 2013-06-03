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
    
    if (major_table_index != -1)
        insertElemMajorTable(matrix, row_number, major_table_index);
        
}

unsigned int findMajorTableIndex(matrix_t * matrix, unsigned int row_number)
{
    int mean_index = 0;
    int min_index = 0;
    int max_index = matrix->major_table_size-1;
    int founded = 0;
        
    while((min_index <= max_index) && (founded==0))
    {
        mean_index = (min_index + max_index) / 2;
        
        if (matrix->major_table[mean_index].row_number == row_number)
            founded=1;
        else
        {
            if (matrix->major_table[mean_index].row_number > row_number)
                max_index = mean_index-1;
            else
                min_index = mean_index+1;
        }
    }
        
    if (founded) mean_index = -1; /* boolean pour savoir si existe deja */
    
    return mean_index;
}

void insertElemMajorTable(matrix_t * matrix, unsigned int row_number, unsigned int row_insert)
{
    int i;
    
    if (row_insert != 0) row_insert++;
        
    for (i = matrix->major_table_size ; i > row_insert ; i--)
    {
        matrix->major_table[i].row_number = matrix->major_table[i-1].row_number;
    }
    matrix->major_table[row_insert].row_number = row_number;
    matrix->major_table_size++;
}