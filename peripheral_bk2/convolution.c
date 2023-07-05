
////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20210408.0
//
////////////////////////////////////////////////////////////////////////////////

#include "convolution.igen.h"
#include <string.h>
#include <stdio.h>

#define CONV_IDLE           0
#define CONV_REQUEST        1
#define CONV_PROCESSING     2
#define CONV_READY          4
#define CONV_FINISH         8

#define MATRIX_SIZE         4

// Global variable to handle a flit in VECTOR type
char chFlit[4];

// Global variable to handle a flit in UNSIGNED type
unsigned int usFlit;

/////////////////////////// Big endian/Little endian ///////////////////////////
#define __bswap_constant_32(x) \
     ((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >>  8) |		      \
      (((x) & 0x0000ff00) <<  8) | (((x) & 0x000000ff) << 24))

unsigned int htonl(unsigned int x){
    return x;//__bswap_constant_32(x);
}

// Transform a flit from VECTOR to UNSIGNED INT (using the global variables)
void vec2usi(){
    unsigned int auxFlit = 0x00000000;
    unsigned int aux;
    aux = 0x000000FF & chFlit[3];
    auxFlit = ((aux << 24) & 0xFF000000);
    aux = 0x000000FF & chFlit[2];
    auxFlit = auxFlit | ((aux << 16) & 0x00FF0000);
    aux = 0x000000FF & chFlit[1];
    auxFlit = auxFlit | ((aux << 8) & 0x0000FF00);
    aux = 0x000000FF & chFlit[0];
    auxFlit = auxFlit | ((aux) & 0x000000FF);
    usFlit = auxFlit;
    return;
}

void usi2vec(){
    chFlit[3] = (usFlit >> 24) & 0x000000FF;
    chFlit[2] = (usFlit >> 16) & 0x000000FF;
    chFlit[1] = (usFlit >> 8) & 0x000000FF;
    chFlit[0] = usFlit & 0x000000FF;
}

// Writes a flit inside an address in the processor memory
void writeMem(unsigned int flit, unsigned int addr){
    usFlit = flit;
    usi2vec();
    ppmAddressSpaceHandle h = ppmOpenAddressSpace("MWRITE");
    if(!h) {
        bhmMessage("I", "NI_ITERATOR", "ERROR_WRITE h handling!");
        while(1){} // error handling
    }
    ppmWriteAddressSpace(h, addr, sizeof(chFlit), chFlit);
    ppmCloseAddressSpace(h);
    return;
}

// Reads a flit from a given address
unsigned int readMem(unsigned int addr){
    ppmAddressSpaceHandle h = ppmOpenAddressSpace("MREAD");
    if(!h) {
        bhmMessage("I", "NI_ITERATOR", "ERROR_READ h handling!");
        while(1){} // error handling
    }
    ppmReadAddressSpace(h, addr, sizeof(chFlit), chFlit);
    ppmCloseAddressSpace(h);
    vec2usi(); // transform the data from vector to a single unsigned int
    return usFlit;
}

//////////////////////////////// Multiply Matrices ////////////////////////////////

int m1[MATRIX_SIZE][MATRIX_SIZE];
int m2[MATRIX_SIZE][MATRIX_SIZE];
int mr[MATRIX_SIZE][MATRIX_SIZE];

void write_matrix(unsigned int buff, int matrix[MATRIX_SIZE][MATRIX_SIZE], int size) {
    int pos, i=0, j=0;
    for(pos = 0; pos < size*size; pos++) {
        writeMem(matrix[i][j], buff + (pos*4));
        i++;
        if(i == size){
            i = 0;
            j++;
        }
    }
}

void read_matrix(unsigned int buff, int matrix[MATRIX_SIZE][MATRIX_SIZE], int size) {
    int pos, i=0, j=0;
    for(pos = 0; pos < size*size; pos++) {
        matrix[i][j] = readMem(buff + (pos*4));
        i++;
        if(i == size){
            i = 0;
            j++;
        }
    }
}

void print_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int i, j;
    for(i = 0; i < MATRIX_SIZE; i++) {
        for(j = 0; j < MATRIX_SIZE; j++)
            printf("%02d ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

void multiply(unsigned int buffer_m1, unsigned int buffer_m2, unsigned int buffer_mr, int size) {
    
    // printf("m1_ptr = %p\n",  (void*)m1);
    // printf("m2_ptr = %p\n",  (void*)m2);
    // printf("res_ptr = %p\n", (void*)res);
    // printf("size = %d\n", size);
    
    // printf("Convol:\n");

    // int result = readMem(m1);
    // printf("Elemento 0x0 -- %u\n", result);

    read_matrix(buffer_m1, m1, size);
    read_matrix(buffer_m2, m2, size);

    // print_matrix(m1);
    // print_matrix(m2);

    int i, j;
    for(i = 0; i < MATRIX_SIZE; i++)
        for(j = 0; j < MATRIX_SIZE; j++)
            mr[i][j] = m1[i][j] * m2[i][j];
    
    write_matrix(buffer_mr, mr, size);
    
    // print_matrix(mr);  
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(addr_m1_R) {
    if(bytes != 4) {
        bhmMessage("E", "PPM_RNB", "Only 4 byte access permitted");
        return 0;
    }
    // YOUR CODE HERE (addr_m1_R)
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(addr_m1_W) {
    if(bytes != 4) {
        bhmMessage("E", "PPM_WNB", "Only 4 byte access permitted");
        return;
    }
    *(Uns32*)user = data;
    // YOUR CODE HERE (addr_m1_W)
}

PPM_REG_READ_CB(addr_m2_R) {
    if(bytes != 4) {
        bhmMessage("E", "PPM_RNB", "Only 4 byte access permitted");
        return 0;
    }
    // YOUR CODE HERE (addr_m2_R)
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(addr_m2_W) {
    if(bytes != 4) {
        bhmMessage("E", "PPM_WNB", "Only 4 byte access permitted");
        return;
    }
    *(Uns32*)user = data;
    // YOUR CODE HERE (addr_m2_W)
}

PPM_REG_READ_CB(addr_re_R) {
    if(bytes != 4) {
        bhmMessage("E", "PPM_RNB", "Only 4 byte access permitted");
        return 0;
    }
    // YOUR CODE HERE (addr_re_R)
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(addr_re_W) {
    if(bytes != 4) {
        bhmMessage("E", "PPM_WNB", "Only 4 byte access permitted");
        return;
    }
    *(Uns32*)user = data;
    // YOUR CODE HERE (addr_re_W)
}

PPM_REG_READ_CB(m_size_R) {
    if(bytes != 4) {
        bhmMessage("E", "PPM_RNB", "Only 4 byte access permitted");
        return 0;
    }
    // YOUR CODE HERE (m_size_R)
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(m_size_W) {
    if(bytes != 4) {
        bhmMessage("E", "PPM_WNB", "Only 4 byte access permitted");
        return;
    }
    *(Uns32*)user = data;
    // YOUR CODE HERE (m_size_W)
}

PPM_REG_READ_CB(status_R) {
    if(bytes != 4) {
        bhmMessage("E", "PPM_RNB", "Only 4 byte access permitted");
        return 0;
    }
    // YOUR CODE HERE (status_R)
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(status_W) {
    if(bytes != 4) {
        bhmMessage("E", "PPM_WNB", "Only 4 byte access permitted");
        return;
    }
    *(Uns32*)user = data;
    // YOUR CODE HERE (status_W)
     printf("!!\n");
    if(convolutionPort_ab_data.status.value == CONV_REQUEST) {
        printf("!!!!!\n");
        multiply(convolutionPort_ab_data.addr_m1.value, convolutionPort_ab_data.addr_m2.value, convolutionPort_ab_data.addr_re.value, convolutionPort_ab_data.m_size.value);
        convolutionPort_ab_data.status.value = CONV_READY;
    }
}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)
}

PPM_DESTRUCTOR_CB(destructor) {
    // YOUR CODE HERE (destructor)
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}


