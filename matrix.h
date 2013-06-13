#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

typedef int cell_type;

typedef struct minor_table_cell_
{
    unsigned int column_number;
    cell_type value;
    struct minor_table_cell_ * next;
} minor_table_cell_t;

typedef struct
{
    unsigned int row_number;
    struct minor_table_cell_ * cell;
} major_table_cell_t;

typedef struct
{
    unsigned int major_table_size;
    major_table_cell_t * major_table;
} matrix_t;

matrix_t readFromFile(FILE * data_file);

void addValue(matrix_t * matrix,
              unsigned int row_number,
              unsigned int column_number,
              cell_type value);

unsigned int findMajorTableIndex(matrix_t * matrix, unsigned int row_number);

void insertElemMajorTable(matrix_t * matrix, unsigned int row_number, unsigned int row_insert);

minor_table_cell_t ** findMinorTableIndex(major_table_cell_t * matrix_cell, unsigned int column_number);

void insertElemMinorTable(minor_table_cell_t ** minor_cell, unsigned int column_insert, cell_type value);

void printTable(matrix_t * matrix);

void freeTable(matrix_t * matrix);

#endif