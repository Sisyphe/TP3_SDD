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
    minor_table_cell_t ** cell;
    
    major_table_index = findMajorTableIndex(matrix, row_number);
        
    cell = findMinorTableIndex(&(matrix->major_table[major_table_index]), column_number);
    insertElemMinorTable(cell, column_number, value);
}

unsigned int findMajorTableIndex(matrix_t * matrix, unsigned int row_number)
{
    int mean_index = 0;
    int min_index = 0;
    int max_index = matrix->major_table_size-1;
    int is_found = 0;
        
    while((min_index <= max_index) && !is_found)
    {
        mean_index = (min_index + max_index) / 2;
        
        if (matrix->major_table[mean_index].row_number == row_number)
            is_found=1;
        else
        {
            if (matrix->major_table[mean_index].row_number > row_number)
                max_index = mean_index-1;
            else
                min_index = mean_index+1;
        }
    }
            
    if (!is_found)
    {
        if (mean_index != 0) mean_index++;
        insertElemMajorTable(matrix, row_number, mean_index);
    }
        
    return mean_index;
}

void insertElemMajorTable(matrix_t * matrix, unsigned int row_number, unsigned int row_insert)
{
    int i;
            
    for (i = matrix->major_table_size ; i > row_insert ; i--)
    {
        matrix->major_table[i] = matrix->major_table[i-1];
    }
    matrix->major_table[row_insert].cell = NULL;
    matrix->major_table[row_insert].row_number = row_number;
    matrix->major_table_size++;
}

minor_table_cell_t ** findMinorTableIndex(major_table_cell_t * matrix_cell, unsigned int column_number)
{
    minor_table_cell_t ** prev = &(matrix_cell)->cell;
    minor_table_cell_t * current = matrix_cell->cell;
    
    while (current != NULL && current->column_number < column_number)
    {
        prev = &(current)->next;
        current = *(prev);
    }

    return prev;
}

void insertElemMinorTable(minor_table_cell_t ** minor_cell, unsigned int column_insert, cell_type value)
{    
    minor_table_cell_t * newColumn = malloc(sizeof(minor_table_cell_t));
    newColumn->column_number = column_insert;
    newColumn->value = value;
    newColumn->next = (*minor_cell);
    (*minor_cell) = newColumn;
}

void printTable(matrix_t * matrix)
{
    struct minor_table_cell_ * cell = NULL;
    int i;
    
    printf("\n********** Matrix **********\n\n");
    for (i = 0 ; i < matrix->major_table_size ; i++)
    {
        printf("row : %d\n", matrix->major_table[i].row_number);
        cell = matrix->major_table[i].cell;
        
        while (cell != NULL)
        {
            printf("    col : %d value : %d\n", cell->column_number, cell->value);
            cell = cell->next;
        }
    }
    printf("\n*****************************\n\n");
}

void freeTable(matrix_t * matrix)
{
    struct minor_table_cell_ * cell = NULL;
    struct minor_table_cell_ * cell_to_delete = NULL;
    int i;

    for (i = 0 ; i < matrix->major_table_size ; i++)
    {
        cell = matrix->major_table[i].cell;
        
        while (cell != NULL)
        {
            cell_to_delete = cell;
            cell = cell->next;
            free(cell_to_delete);
        }
    }

    free(matrix->major_table);
}