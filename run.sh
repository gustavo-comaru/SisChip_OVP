#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

# CROSS=OR1K
CROSS=RISCV32IM

# compile the application
make -C application CROSS=${CROSS}

# generate and compile the iGen created module
make -C module 

# peripheral
cd ./peripheral
make
make NOVLNV=1
cd ..

# run the module using the harness
harness.exe --modulefile module/model.${IMPERAS_SHRSUF} --program application/application.${CROSS}.elf $*
