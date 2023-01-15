#include <iostream>
#include <stdio.h>
#include <string>

typedef uint8_t byte;
typedef uint16_t byte2;


//Forward declaration: prevents circular inclusion of header files by declaring the bus class here itself
class bus;

class cpu{
    public: 
    // Bus connection functions
    byte read(byte2 address);
    void write(byte2 address, byte data);
    void connect(bus *n){
        bus = n;
    }
    bus *bus = NULL;

    
    // Registers for 6502 CPU
    struct registers{
    byte a = 0x00; // Accumulator register
    byte x = 0x00; // X register
    byte y = 0x00; // Y register
    byte stack = 0x00FF; // Stack Pointer
    byte2 pc = 0x0000;  // Program Counter
    byte status = 0x00; // Status register
    } registers;

    // Condition codes for 6502 Status register
    enum flags
    {
        //to modify the status register
        negative = 1 << 7, //1 << 7 => shifted left 7 times
        overflow = 1 << 6,
        useless = 1 << 5, //unused
        bbreak = 1 << 4,
        decimal = 1 << 3,
        interrupt_disable = 1 << 2, // 0 = no, 1 = yes
        zero = 1 << 1,
        carry = 1 << 0,
    };

    void reset(); // hard reset
    void irq(); // interrupt req
    void nmi(); // non-maskable interrupt
    void sync(); // clock timing update

    private: 
    // Addressing Mode
  
    void ACC(); // accumulator addressing
    void IMM(); // immediate addressing
    void ZPO(); // zero page addressing
    void ZPX(); // indexed zero page (x) addressing
    void ZPY(); // indexed zero page (y) addressing
    void ABS(); // absolute addressing
    void ABX(); // absolute indexed (x) addressing
    void ABY(); // absolute indexed (y) addressing
    void IMP(); // implied addressing
    void REL(); // relative addressing
    void INX(); // indirect indexed (x) addressing
    void INY(); // indirect indexed (y) addressing
    void ABI(); // absolute indexed addressing

    // little endian
    
    private: 
    // opcodes
    void ADC();
    void AND();
    void ASL();
    void BCC();
    void BCS();
    void BEQ();
    void BIT();
    void BMI();
    void BNE();
    void BPL();
    void BRK();
    void BVC();
    void BVS();
    void CLC();
    void CLD();
    void CLI();
    void CLV();
    void CMP();
    void CPX();
    void CPY();
    void DEC();
    void DEX();
    void DEY();
    void EOR();
    void INC();
    void INX();
    void INY();
    void JMP();
    void JSR();
    void LDA();
    void LDX();
    void LDY();
    void LSR();
    void NOP();
    void ORA();
    void PHA();
    void PHP();
    void PLA();
    void PLP();
    void ROL();
    void ROR();
    void RTI();
    void RTS();
    void SBC();
    void SEC();
    void SED();
    void SEI();
    void STA();
    void STX();
    void STY();
    void TAX();
    void TAY();
    void TSX();
    void TXA();
    void TXS();
    void TYA();
    void UNO(); // unofficial opcodes (nop)

    struct OPCODE{
        std::string num; 
        void (cpu::*operation) (void) = NULL; // function pointer to implementation of opcode
        void (cpu::*address) (void) = NULL; // function pointer to addressing mode
        byte cycle = 0;
    };

    //status register functions
    byte getFlag(flags flag);
    void setFlag(flags flag, int val);

    byte2 effAddress = 0x00; // effective address
    byte2 relAddress = 0x00;
    byte cycles; //current cycles 
    byte opcode;

    OPCODE lookupcode[256];
    void fetch();
    byte dataFetched;

   
 };