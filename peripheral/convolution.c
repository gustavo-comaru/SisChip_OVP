
////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20210408.0
//
////////////////////////////////////////////////////////////////////////////////

#include "convolution.igen.h"
#include <string.h>

#define CONV_IDLE           0
#define CONV_REQUEST        1
#define CONV_PROCESSING     2
#define CONV_READY          4
#define CONV_FINISH         8

unsigned int val = 20;

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
    if(convolutionPort_ab_data.status.value == CONV_REQUEST) {
        convolutionPort_ab_data.addr_re.value = convolutionPort_ab_data.addr_m1.value + convolutionPort_ab_data.addr_m2.value;
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


