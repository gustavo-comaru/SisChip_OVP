ihwnew -name convolutionAccelerator

#######
# BUS #
#######

ihwaddbus -instancename bus0 -addresswidth 32
#ihwaddnet -instancename convolutionPort

#############
# PROCESSOR #
#############

#ihwaddprocessor -instancename cpu0 \
#                -vendor ovpworld.org -library processor -type or1k -version 1.0 \
#                -variant generic \
#                -semihostname or1kNewlib

ihwaddprocessor -instancename cpu0 -id 0 -semihostname riscv32Newlib \
                -type riscv -vendor riscv.ovpworld.org -library processor -version 1.0 \
                -simulateexceptions
ihwsetparameter -handle cpu0 -name variant        -value RVB32I -type enum
ihwsetparameter -handle cpu0 -name add_Extensions -value MSU -type string

ihwconnect -bus bus0 -instancename cpu0 -busmasterport INSTRUCTION
ihwconnect -bus bus0 -instancename cpu0 -busmasterport DATA

ihwaddmemory -instancename ram0 -type ram
ihwconnect -bus bus0 -instancename ram0 -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x0fffffff

ihwaddmemory -instancename ram1 -type ram
ihwconnect -bus bus0 -instancename ram1 -busslaveport sp1 -loaddress 0x20000000 -hiaddress 0xffffffff

##############
# PERIPHERAL #
##############

ihwaddperipheral -instancename convolution0 -modelfile peripheral/pse.pse
ihwconnect -instancename convolution0 -busslaveport convolutionPort -bus bus0 -loaddress 0x10000000 -hiaddress 0x10000013
ihwconnect -instancename convolution0 -busmasterport MREAD -bus bus0
ihwconnect -instancename convolution0 -busmasterport MWRITE -bus bus0