#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE         4

#define CONV_IDLE           0
#define CONV_REQUEST        1
#define CONV_PROCESSING     2
#define CONV_READY          4

#define MMR_BASE ((unsigned int *)0x10000000)

volatile int            *conv_status  = MMR_BASE + 0; // ((unsigned int *)0x10000000)
volatile int            *conv_m_size  = MMR_BASE + 1; // ((unsigned int *)0x10000004)
volatile unsigned int   *conv_addr_m1 = MMR_BASE + 2; // ((unsigned int *)0x10000008)
volatile unsigned int   *conv_addr_m2 = MMR_BASE + 3; // ((unsigned int *)0x1000000C)
volatile unsigned int   *conv_addr_re = MMR_BASE + 4; // ((unsigned int *)0x10000010)

int m1[MATRIX_SIZE][MATRIX_SIZE];
int m2[MATRIX_SIZE][MATRIX_SIZE];
int mr[MATRIX_SIZE][MATRIX_SIZE];

void print_matrix(int *m, int size) {
    printf("m_ptr = %p\n",  (void*)m);

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("%02d ", *(m + i * size + j));
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {

    for(int i = 0; i < MATRIX_SIZE; i++) {
        for(int j = 0; j < MATRIX_SIZE; j++) {
            m1[i][j] = i + j;
            m2[i][j] = (i + j) * 2;
        }
    }

    m1[0][0] = 123;

    printf("Matrix 1:\n");
    print_matrix(m1, MATRIX_SIZE);
    printf("\n");

    printf("Matrix 2:\n");
    print_matrix(m2, MATRIX_SIZE);
    printf("\n");

    while(*conv_status != CONV_IDLE);

    printf("m1_ptr = %p\n",  (void*)m1);
    printf("m2_ptr = %p\n",  (void*)m2);
    printf("res_ptr = %p\n", (void*)mr);
    printf("size = %d\n", MATRIX_SIZE);

    (*conv_addr_m1) = (unsigned int) m1;
    (*conv_addr_m2) = (unsigned int) m2;
    (*conv_addr_re) = (unsigned int) mr;
    (*conv_m_size)  = MATRIX_SIZE;
    (*conv_status)  = CONV_REQUEST;

    while(*conv_status != CONV_READY);

    *conv_status = CONV_IDLE;

    printf("Resulting Matrix:\n");
    print_matrix(mr, MATRIX_SIZE);
    printf("\n");

    return 0;
}
