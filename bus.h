#include <stdio.h> 
#include <array> //stl array for easier use

typedef uint8_t byte;
typedef uint16_t byte2;

#include "cpu.h"

//Emulating the bus in the NES requires two things: mirroring and direct access to the RAM.

class bus{
    public:
        cpu cpu;
        std::array<byte, 64*1024> RAM;
        void write(byte2 address, byte data);
        byte read(byte2 address);
};

