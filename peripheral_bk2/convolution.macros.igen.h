
////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20210408.0
//
////////////////////////////////////////////////////////////////////////////////

#ifndef CONVOLUTION_MACROS_IGEN_H
#define CONVOLUTION_MACROS_IGEN_H       

// Before including this file in the application, define the indicated macros
// to fix the base address of each slave port.

// Set the macro 'CONVOLUTIONPORT' to the base of port 'convolutionPort'
#ifndef CONVOLUTIONPORT
#error CONVOLUTIONPORT is undefined. It needs to be set to the port base address
#endif


#define CONVOLUTIONPORT_AB_POFFSET      0x0
#define CONVOLUTIONPORT_AB_STATUS_POFFSET  0x0
#define CONVOLUTIONPORT_AB_STATUS       (CONVOLUTIONPORT + CONVOLUTIONPORT_AB_POFFSET + CONVOLUTIONPORT_AB_STATUS_POFFSET)

#define CONVOLUTIONPORT_AB_M_SIZE_POFFSET  0x4
#define CONVOLUTIONPORT_AB_M_SIZE       (CONVOLUTIONPORT + CONVOLUTIONPORT_AB_POFFSET + CONVOLUTIONPORT_AB_M_SIZE_POFFSET)

#define CONVOLUTIONPORT_AB_ADDR_M1_POFFSET  0x8
#define CONVOLUTIONPORT_AB_ADDR_M1      (CONVOLUTIONPORT + CONVOLUTIONPORT_AB_POFFSET + CONVOLUTIONPORT_AB_ADDR_M1_POFFSET)

#define CONVOLUTIONPORT_AB_ADDR_M2_POFFSET  0xc
#define CONVOLUTIONPORT_AB_ADDR_M2      (CONVOLUTIONPORT + CONVOLUTIONPORT_AB_POFFSET + CONVOLUTIONPORT_AB_ADDR_M2_POFFSET)

#define CONVOLUTIONPORT_AB_ADDR_RE_POFFSET  0x10
#define CONVOLUTIONPORT_AB_ADDR_RE      (CONVOLUTIONPORT + CONVOLUTIONPORT_AB_POFFSET + CONVOLUTIONPORT_AB_ADDR_RE_POFFSET)


#endif
