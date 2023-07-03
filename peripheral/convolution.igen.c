
////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20210408.0
//
////////////////////////////////////////////////////////////////////////////////


#include "convolution.igen.h"
/////////////////////////////// Port Declarations //////////////////////////////

convolutionPort_ab_dataT convolutionPort_ab_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "convolution", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.convolutionPort = ppmCreateSlaveBusPort("convolutionPort", 20);
    if (!handles.convolutionPort) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'convolutionPort'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_status",
            0,
            handles.convolutionPort,
            0x0,
            4,
            status_R,
            status_W,
            view32,
            &(convolutionPort_ab_data.status.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_m_size",
            0,
            handles.convolutionPort,
            0x4,
            4,
            m_size_R,
            m_size_W,
            view32,
            &(convolutionPort_ab_data.m_size.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_addr_m1",
            0,
            handles.convolutionPort,
            0x8,
            4,
            addr_m1_R,
            addr_m1_W,
            view32,
            &(convolutionPort_ab_data.addr_m1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_addr_m2",
            0,
            handles.convolutionPort,
            0xc,
            4,
            addr_m2_R,
            addr_m2_W,
            view32,
            &(convolutionPort_ab_data.addr_m2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_addr_re",
            0,
            handles.convolutionPort,
            0x10,
            4,
            addr_re_R,
            addr_re_W,
            view32,
            &(convolutionPort_ab_data.addr_re.value),
            True
        );
    }

}

PPM_DOC_FN(installDocs){
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    destructor();
    return 0;
}

