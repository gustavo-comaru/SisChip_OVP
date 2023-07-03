#include <stdio.h>
#include <stdlib.h>

#define MMR_BASE ((unsigned int *)0x10000000)

volatile unsigned int *conv_status  = MMR_BASE + 0; // ((unsigned int *)0x10000000)
volatile unsigned int *conv_m_size  = MMR_BASE + 1; // ((unsigned int *)0x10000004)
volatile unsigned int *conv_addr_m1 = MMR_BASE + 2; // ((unsigned int *)0x10000008)
volatile unsigned int *conv_addr_m2 = MMR_BASE + 3; // ((unsigned int *)0x1000000C)
volatile unsigned int *conv_addr_re = MMR_BASE + 4; // ((unsigned int *)0x10000010)

int main(int argc, char **argv) {

    unsigned int result = *conv_addr_re;
    printf("Res 1: %u\n", result);

    result = *conv_addr_re;
    printf("Res 2: %u\n", result);

    *conv_addr_m1 = 135;

    result = *conv_addr_re;
    printf("Res 3: %u\n", result);

    printf("\nHello first world from iGen generated platform\n\n");

    return 0;
}
