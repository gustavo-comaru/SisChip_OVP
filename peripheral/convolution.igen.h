
////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20210408.0
//
////////////////////////////////////////////////////////////////////////////////

#ifndef CONVOLUTION_IGEN_H
#define CONVOLUTION_IGEN_H              

#ifdef _PSE_
#    include "peripheral/impTypes.h"
#    include "peripheral/bhm.h"
#    include "peripheral/bhmHttp.h"
#    include "peripheral/ppm.h"
#else
#    include "hostapi/impTypes.h"
#endif

#ifdef _PSE_
//////////////////////////////////// Externs ///////////////////////////////////

extern Uns32 diagnosticLevel;


/////////////////////////// Dynamic Diagnostic Macros //////////////////////////

// Bottom two bits of word used for PSE diagnostics
#define PSE_DIAG_LOW                    (BHM_DIAG_MASK_LOW(diagnosticLevel))
#define PSE_DIAG_MEDIUM                 (BHM_DIAG_MASK_MEDIUM(diagnosticLevel))

#define PSE_DIAG_HIGH                   (BHM_DIAG_MASK_HIGH(diagnosticLevel))
// Next two bits of word used for PSE semihost/intercept library diagnostics
#define PSE_DIAG_SEMIHOST               (BHM_DIAG_MASK_SEMIHOST(diagnosticLevel))

#endif
/////////////////////////// Register data declaration //////////////////////////

typedef struct convolutionPort_ab_dataS { 
    union { 
        Uns32 value;
    } status;
    union { 
        Uns32 value;
    } m_size;
    union { 
        Uns32 value;
    } addr_m1;
    union { 
        Uns32 value;
    } addr_m2;
    union { 
        Uns32 value;
    } addr_re;
} convolutionPort_ab_dataT, *convolutionPort_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern convolutionPort_ab_dataT convolutionPort_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *convolutionPort;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(addr_m1_R);
PPM_REG_WRITE_CB(addr_m1_W);
PPM_REG_READ_CB(addr_m2_R);
PPM_REG_WRITE_CB(addr_m2_W);
PPM_REG_READ_CB(addr_re_R);
PPM_REG_WRITE_CB(addr_re_W);
PPM_REG_READ_CB(m_size_R);
PPM_REG_WRITE_CB(m_size_W);
PPM_REG_READ_CB(status_R);
PPM_REG_WRITE_CB(status_W);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define CONVOLUTIONPORT_AB_STATUS_WIDTH  32
#define CONVOLUTIONPORT_AB_M_SIZE_WIDTH  32
#define CONVOLUTIONPORT_AB_ADDR_M1_WIDTH  32
#define CONVOLUTIONPORT_AB_ADDR_M2_WIDTH  32
#define CONVOLUTIONPORT_AB_ADDR_RE_WIDTH  32

#endif

#endif
