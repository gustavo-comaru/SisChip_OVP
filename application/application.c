#include <stdio.h>
#include <stdlib.h>
#include "../config.h"

#define MMR_BASE ((unsigned int *)0x10000000)

volatile int            *conv_status  = MMR_BASE + 0; // ((unsigned int *)0x10000000)
volatile int            *conv_m_size  = MMR_BASE + 1; // ((unsigned int *)0x10000004)
volatile unsigned int   *conv_addr_m1 = MMR_BASE + 2; // ((unsigned int *)0x10000008)
volatile unsigned int   *conv_addr_m2 = MMR_BASE + 3; // ((unsigned int *)0x1000000C)
volatile unsigned int   *conv_addr_re = MMR_BASE + 4; // ((unsigned int *)0x10000010)

int buffer_m1[MATRIX_SIZE*MATRIX_SIZE];
int buffer_m2[MATRIX_SIZE*MATRIX_SIZE];
int buffer_mr[MATRIX_SIZE*MATRIX_SIZE];

void print_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for(int i = 0; i < MATRIX_SIZE; i++) {
        for(int j = 0; j < MATRIX_SIZE; j++)
            printf("%02d ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

void write_matrix(int* buff, int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int pos = 0;
    for(int i = 0; i < MATRIX_SIZE; i++) {
        for(int j = 0; j < MATRIX_SIZE; j++) {
            buff[pos] = matrix[i][j];
            pos++;
        }
    }
}

void read_matrix(int* buff, int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int pos = 0;
    for(int i = 0; i < MATRIX_SIZE; i++) {
        for(int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = buff[pos];
            pos++;
        }
    }
}

int main(int argc, char **argv) {

    /* Init Matrices */

    int m1[MATRIX_SIZE][MATRIX_SIZE];
    int m2[MATRIX_SIZE][MATRIX_SIZE];
    int mr[MATRIX_SIZE][MATRIX_SIZE];

    for(int i = 0; i < MATRIX_SIZE; i++) {
        for(int j = 0; j < MATRIX_SIZE; j++) {
            m1[i][j] = i + j;
            m2[i][j] = (i + j) * 2;
            mr[i][j] = 0;
        }
    }

    printf("Matrix 1:\n");
    print_matrix(m1);

    printf("Matrix 2:\n");
    print_matrix(m2);

    /* Request Operation */

    write_matrix(buffer_m1, m1);
    write_matrix(buffer_m2, m2);

    while(*conv_status != CONV_IDLE);

    (*conv_addr_m1) = (unsigned int) buffer_m1;
    (*conv_addr_m2) = (unsigned int) buffer_m2;
    (*conv_addr_re) = (unsigned int) buffer_mr;
    (*conv_status)  = CONV_REQUEST;

    /* Read Result */

    while(*conv_status != CONV_READY);

    *conv_status = CONV_IDLE;

    read_matrix(buffer_mr, mr);

    printf("Resulting Matrix:\n");
    print_matrix(mr);

    return 0;
}
