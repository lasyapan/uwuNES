#include "bus.h"

bus::bus(){
    cpu.connect(this);
    for(int i = 0; i < (64*1024); i++){
        RAM[i] = 0x00;
    }
    // connects cpu to bus, reset ram to 0
}


void bus::write(byte2 address, byte data){
    if(address >= 0x0000 && address <= 0xFFFF){
        RAM[address] = data;
    }
}

byte bus::read(byte2 address){
    if(address >= 0x0000 && address <= 0xFFFF){
        return RAM[address];
    }
    return 0x00;
}