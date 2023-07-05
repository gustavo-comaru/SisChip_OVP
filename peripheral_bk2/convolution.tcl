imodelnewperipheral -name convolution \
                    -constructor constructor \
                    -destructor  destructor \
                    -vendor gaph \
                    -library peripheral \
                    -version 1.0 

#########################################
# Master read and write ports
#########################################
imodeladdbusmasterport -name "MREAD" -addresswidth 32
imodeladdbusmasterport -name "MWRITE" -addresswidth 32

#########################################
## Slave port on the bus
#########################################
imodeladdbusslaveport -name convolutionPort -size 20 -mustbeconnected

# Address block
imodeladdaddressblock -name ab -port convolutionPort -offset 0x0 -width 32 -size 20

# registers
imodeladdmmregister -addressblock convolutionPort/ab -name status  -readfunction status_R  -writefunction status_W  -offset 0
imodeladdmmregister -addressblock convolutionPort/ab -name m_size  -readfunction m_size_R  -writefunction m_size_W  -offset 4
imodeladdmmregister -addressblock convolutionPort/ab -name addr_m1 -readfunction addr_m1_R -writefunction addr_m1_W -offset 8
imodeladdmmregister -addressblock convolutionPort/ab -name addr_m2 -readfunction addr_m2_R -writefunction addr_m2_W -offset 12
imodeladdmmregister -addressblock convolutionPort/ab -name addr_re -readfunction addr_re_R -writefunction addr_re_W -offset 16
