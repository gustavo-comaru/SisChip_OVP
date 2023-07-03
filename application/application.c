#include <stdio.h>
#include <stdlib.h>

#define CONV_IDLE           0
#define CONV_REQUEST        1
#define CONV_PROCESSING     2
#define CONV_READY          4
#define CONV_FINISH         8

#define MMR_BASE ((unsigned int *)0x10000000)

volatile int *conv_status  = MMR_BASE + 0; // ((unsigned int *)0x10000000)
volatile int *conv_m_size  = MMR_BASE + 1; // ((unsigned int *)0x10000004)
volatile int *conv_addr_m1 = MMR_BASE + 2; // ((unsigned int *)0x10000008)
volatile int *conv_addr_m2 = MMR_BASE + 3; // ((unsigned int *)0x1000000C)
volatile int *conv_addr_re = MMR_BASE + 4; // ((unsigned int *)0x10000010)

int main(int argc, char **argv) {

    // First test

    int result = *conv_addr_re;
    printf("Res 0: %d\n", result);

    // Second test

    int a = 361;
    int b = 125;

    *conv_addr_m1 = a;
    *conv_addr_m2 = b;
    *conv_status = CONV_REQUEST;

    result = *conv_addr_re;
    printf("Res 2: %u\n", result);

    // Finish

    printf("\nHello first world from iGen generated platform\n\n");

    return 0;
}
