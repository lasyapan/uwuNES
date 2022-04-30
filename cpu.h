#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

typedef uint8_t byte;
typedef uint16_t byte2;


class cpu{
    public: 
    
    
    // Registers for 6502 CPU
    byte a = 0x00; // Accumulator register
    byte x = 0x00; // X register
    byte y = 0x00; // Y register
    byte stack = 0x00; // Stack Pointer
    byte2 pc = 0x0000;  // Program Counter
    byte status = 0x00; // Status register

    // Condition codes for 6502 Status register
    enum flags
    {
        //to modify the status register
        negative = 1 << 7, //1 << 7 => shifted left 7 times
        overflow = 1 << 6,
        reserved = 1 << 5, //unused
        bbreak = 1 << 4,
        decimal = 1 << 3,
        interrupt_disable = 1 << 2,
        zero = 1 << 1,
        carry = 1 << 0,
    };

    void reset(); // hard reset
    void irq(); // interrupt req
    void nmi(); // non-maskable interrupt
    void sync(); // clock timing update

    private: 
    // Addressing Mode
  
    byte ACC(); // accumulator addressing
    byte IMM(); // immediate addressing
    byte ZPO(); // zero page addressing
    byte ZPX(); // indexed zero page (x) addressing
    byte ZPY(); // indexed zero page (y) addressing
    byte ABS(); // absolute addressing
    byte ABX(); // absolute indexed (x) addressing
    byte ABY(); // absolute indexed (y) addressing
    byte IMP(); // implied addressing
    byte REL(); // relative addressing
    byte INX(); // indirect indexed (x) addressing
    byte INY(); // indirect indexed (y) addressing
    byte ABI(); // absolute indexed addressing

    // little endian
    
    private: 
    // opcodes
    byte ADC();
    byte AND();
    byte ASL();
    byte BCC();
    byte BCS();
    byte BEQ();
    byte BIT();
    byte BMI();
    byte BNE();
    byte BPL();
    byte BRK();
    byte BVC();
    byte BVS();
    byte CLC();
    byte CLD();
    byte CLI();
    byte CLV();
    byte CMP();
    byte CPX();
    byte CPY();
    byte DEC();
    byte DEX();
    byte DEY();
    byte EOR();
    byte INC();
    byte INX();
    byte INY();
    byte JMP();
    byte JSR();
    byte LDA();
    byte LDX();
    byte LDY();
    byte LSR();
    byte NOP();
    byte ORA();
    byte PHA();
    byte PHP();
    byte PLA();
    byte PLP();
    byte ROL();
    byte ROR();
    byte RTI();
    byte RTS();
    byte SBC();
    byte SEC();
    byte SED();
    byte SEI();
    byte STA();
    byte STX();
    byte STY();
    byte TAX();
    byte TAY();
    byte TSX();
    byte TXA();
    byte TXS();
    byte TYA();
    byte UNO(); // unofficial opcodes (nop)

    struct OPCODE{
        string num; 
        byte (cpu::*opcode) (void) = NULL; // function pointer to implementation of opcode
        byte (cpu::*address) (void) = NULL; // function pointer to addressing mode
        byte cycle = 0;
    };

    //status register functions
    byte getFlag();
    void setFlag();

    byte absAddress = 0x00;
    byte relAddress = 0x00;
    byte cycles;
    byte opcode;


    bool complete(); // if complete, cycle++ instead of counting
    byte fetch();
    void clock();

    
 };