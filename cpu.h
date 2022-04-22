#include <iostream>
#include <stdio.h>
#include <string>

typedef byte uint8_t
typedef byte2 uint16_t


class cpu{
    public: 
    
    struct registers{
    // Registers for 6502 CPU
    byte a = 0x00; // Accumulator register
    byte x = 0x00; // X register
    byte y = 0x00; // Y register
    byte stack = 0x00; // Stack Pointer
    byte2 pc = 0x0000;  // Program Counter
    byte status = 0x00; // Status register
    }
    // Condition codes for 6502 Status register
    enum flags
    {
        //to modify the status register
        negative = 0 >> 7,
        overflow = 0 >> 6,
        reserved = 0 >> 5, //unused
        break = 0 >> 4,
        decimal = 0 >> 3,
        interrupt_disable = 0 >> 2,
        zero = 0 >> 1,
        carry = 0,
    };

    void reset(); // hard reset
    void irq(); // interrupt req
    void nmi(); // non-maskable interrupt
    void sync(); // clock timing update

    private: 
    // Addressing Modes
  
    byte ACC(); // accumulator addressing
    byte IMM(); // immediate addressing
    byte ZP(); // zero page addressing
    byte ZPX(); // indexed zero page (x) addressing
    byte ZPY(); // indexed zero page (y) addressing
    byte ABS(); // absolute addressing
    byte ABX(); // absolute indexed (x) addressing
    byte ABY(); // absolute indexed (y) addressing
    byte IMP(); // implied addressing
    byte REL(); // relative addressing
    byte INX(); // indirect indexed (x) addressing
    byte INY(); // indirect indexed (y) addressing
    byte ABI(); // absolute indirect addressing

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
        std::string num; 
        byte (cpu::*opcode) (void) = NULL; // function pointer to implementation of opcode
        byte (cpu::*address) (void) = NULL; // function pointer to addressing mode
        byte cycle = 0;
    }

    //lookup table constructor 
    cpu(){
        opcodes[] = 
	{
		{ "BRK", cpu::BRK, cpu::IMP, 7 },{ "ORA", cpu::ORA, cpu::IZX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 3 },{ "ORA", cpu::ORA, cpu::ZP0, 3 },{ "ASL", cpu::ASL, cpu::ZP0, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "PHP", cpu::PHP, cpu::IMP, 3 },{ "ORA", cpu::ORA, cpu::IMM, 2 },{ "ASL", cpu::ASL, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "ORA", cpu::ORA, cpu::ABS, 4 },{ "ASL", cpu::ASL, cpu::ABS, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },
		{ "BPL", cpu::BPL, cpu::REL, 2 },{ "ORA", cpu::ORA, cpu::IZY, 5 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "ORA", cpu::ORA, cpu::ZPX, 4 },{ "ASL", cpu::ASL, cpu::ZPX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "CLC", cpu::CLC, cpu::IMP, 2 },{ "ORA", cpu::ORA, cpu::ABY, 4 },{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 7 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "ORA", cpu::ORA, cpu::ABX, 4 },{ "ASL", cpu::ASL, cpu::ABX, 7 },{ "UNO", cpu::UNO, cpu::IMP, 7 },
		{ "JSR", cpu::JSR, cpu::ABS, 6 },{ "AND", cpu::AND, cpu::IZX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "BIT", cpu::BIT, cpu::ZP0, 3 },{ "AND", cpu::AND, cpu::ZP0, 3 },{ "ROL", cpu::ROL, cpu::ZP0, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "PLP", cpu::PLP, cpu::IMP, 4 },{ "AND", cpu::AND, cpu::IMM, 2 },{ "ROL", cpu::ROL, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "BIT", cpu::BIT, cpu::ABS, 4 },{ "AND", cpu::AND, cpu::ABS, 4 },{ "ROL", cpu::ROL, cpu::ABS, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },
		{ "BMI", cpu::BMI, cpu::REL, 2 },{ "AND", cpu::AND, cpu::IZY, 5 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "AND", cpu::AND, cpu::ZPX, 4 },{ "ROL", cpu::ROL, cpu::ZPX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "SEC", cpu::SEC, cpu::IMP, 2 },{ "AND", cpu::AND, cpu::ABY, 4 },{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 7 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "AND", cpu::AND, cpu::ABX, 4 },{ "ROL", cpu::ROL, cpu::ABX, 7 },{ "UNO", cpu::UNO, cpu::IMP, 7 },
		{ "RTI", cpu::RTI, cpu::IMP, 6 },{ "EOR", cpu::EOR, cpu::IZX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 3 },{ "EOR", cpu::EOR, cpu::ZP0, 3 },{ "LSR", cpu::LSR, cpu::ZP0, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "PHA", cpu::PHA, cpu::IMP, 3 },{ "EOR", cpu::EOR, cpu::IMM, 2 },{ "LSR", cpu::LSR, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "JMP", cpu::JMP, cpu::ABS, 3 },{ "EOR", cpu::EOR, cpu::ABS, 4 },{ "LSR", cpu::LSR, cpu::ABS, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },
		{ "BVC", cpu::BVC, cpu::REL, 2 },{ "EOR", cpu::EOR, cpu::IZY, 5 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "EOR", cpu::EOR, cpu::ZPX, 4 },{ "LSR", cpu::LSR, cpu::ZPX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "CLI", cpu::CLI, cpu::IMP, 2 },{ "EOR", cpu::EOR, cpu::ABY, 4 },{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 7 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "EOR", cpu::EOR, cpu::ABX, 4 },{ "LSR", cpu::LSR, cpu::ABX, 7 },{ "UNO", cpu::UNO, cpu::IMP, 7 },
		{ "RTS", cpu::RTS, cpu::IMP, 6 },{ "ADC", cpu::ADC, cpu::IZX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 3 },{ "ADC", cpu::ADC, cpu::ZP0, 3 },{ "ROR", cpu::ROR, cpu::ZP0, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "PLA", cpu::PLA, cpu::IMP, 4 },{ "ADC", cpu::ADC, cpu::IMM, 2 },{ "ROR", cpu::ROR, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "JMP", cpu::JMP, cpu::IND, 5 },{ "ADC", cpu::ADC, cpu::ABS, 4 },{ "ROR", cpu::ROR, cpu::ABS, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },
		{ "BVS", cpu::BVS, cpu::REL, 2 },{ "ADC", cpu::ADC, cpu::IZY, 5 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "ADC", cpu::ADC, cpu::ZPX, 4 },{ "ROR", cpu::ROR, cpu::ZPX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "SEI", cpu::SEI, cpu::IMP, 2 },{ "ADC", cpu::ADC, cpu::ABY, 4 },{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 7 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "ADC", cpu::ADC, cpu::ABX, 4 },{ "ROR", cpu::ROR, cpu::ABX, 7 },{ "UNO", cpu::UNO, cpu::IMP, 7 },
		{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "STA", cpu::STA, cpu::IZX, 6 },{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "STY", cpu::STY, cpu::ZP0, 3 },{ "STA", cpu::STA, cpu::ZP0, 3 },{ "STX", cpu::STX, cpu::ZP0, 3 },{ "UNO", cpu::UNO, cpu::IMP, 3 },{ "DEY", cpu::DEY, cpu::IMP, 2 },{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "TXA", cpu::TXA, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "STY", cpu::STY, cpu::ABS, 4 },{ "STA", cpu::STA, cpu::ABS, 4 },{ "STX", cpu::STX, cpu::ABS, 4 },{ "UNO", cpu::UNO, cpu::IMP, 4 },
		{ "BCC", cpu::BCC, cpu::REL, 2 },{ "STA", cpu::STA, cpu::IZY, 6 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "STY", cpu::STY, cpu::ZPX, 4 },{ "STA", cpu::STA, cpu::ZPX, 4 },{ "STX", cpu::STX, cpu::ZPY, 4 },{ "UNO", cpu::UNO, cpu::IMP, 4 },{ "TYA", cpu::TYA, cpu::IMP, 2 },{ "STA", cpu::STA, cpu::ABY, 5 },{ "TXS", cpu::TXS, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "UNO", cpu::NOP, cpu::IMP, 5 },{ "STA", cpu::STA, cpu::ABX, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },
		{ "LDY", cpu::LDY, cpu::IMM, 2 },{ "LDA", cpu::LDA, cpu::IZX, 6 },{ "LDX", cpu::LDX, cpu::IMM, 2 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "LDY", cpu::LDY, cpu::ZP0, 3 },{ "LDA", cpu::LDA, cpu::ZP0, 3 },{ "LDX", cpu::LDX, cpu::ZP0, 3 },{ "UNO", cpu::UNO, cpu::IMP, 3 },{ "TAY", cpu::TAY, cpu::IMP, 2 },{ "LDA", cpu::LDA, cpu::IMM, 2 },{ "TAX", cpu::TAX, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "LDY", cpu::LDY, cpu::ABS, 4 },{ "LDA", cpu::LDA, cpu::ABS, 4 },{ "LDX", cpu::LDX, cpu::ABS, 4 },{ "UNO", cpu::UNO, cpu::IMP, 4 },
		{ "BCS", cpu::BCS, cpu::REL, 2 },{ "LDA", cpu::LDA, cpu::IZY, 5 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "LDY", cpu::LDY, cpu::ZPX, 4 },{ "LDA", cpu::LDA, cpu::ZPX, 4 },{ "LDX", cpu::LDX, cpu::ZPY, 4 },{ "UNO", cpu::UNO, cpu::IMP, 4 },{ "CLV", cpu::CLV, cpu::IMP, 2 },{ "LDA", cpu::LDA, cpu::ABY, 4 },{ "TSX", cpu::TSX, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 4 },{ "LDY", cpu::LDY, cpu::ABX, 4 },{ "LDA", cpu::LDA, cpu::ABX, 4 },{ "LDX", cpu::LDX, cpu::ABY, 4 },{ "UNO", cpu::UNO, cpu::IMP, 4 },
		{ "CPY", cpu::CPY, cpu::IMM, 2 },{ "CMP", cpu::CMP, cpu::IZX, 6 },{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "CPY", cpu::CPY, cpu::ZP0, 3 },{ "CMP", cpu::CMP, cpu::ZP0, 3 },{ "DEC", cpu::DEC, cpu::ZP0, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "INY", cpu::INY, cpu::IMP, 2 },{ "CMP", cpu::CMP, cpu::IMM, 2 },{ "DEX", cpu::DEX, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "CPY", cpu::CPY, cpu::ABS, 4 },{ "CMP", cpu::CMP, cpu::ABS, 4 },{ "DEC", cpu::DEC, cpu::ABS, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },
		{ "BNE", cpu::BNE, cpu::REL, 2 },{ "CMP", cpu::CMP, cpu::IZY, 5 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "CMP", cpu::CMP, cpu::ZPX, 4 },{ "DEC", cpu::DEC, cpu::ZPX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "CLD", cpu::CLD, cpu::IMP, 2 },{ "CMP", cpu::CMP, cpu::ABY, 4 },{ "NOP", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 7 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "CMP", cpu::CMP, cpu::ABX, 4 },{ "DEC", cpu::DEC, cpu::ABX, 7 },{ "UNO", cpu::UNO, cpu::IMP, 7 },
		{ "CPX", cpu::CPX, cpu::IMM, 2 },{ "SBC", cpu::SBC, cpu::IZX, 6 },{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "CPX", cpu::CPX, cpu::ZP0, 3 },{ "SBC", cpu::SBC, cpu::ZP0, 3 },{ "INC", cpu::INC, cpu::ZP0, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "INX", cpu::INX, cpu::IMP, 2 },{ "SBC", cpu::SBC, cpu::IMM, 2 },{ "NOP", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::SBC, cpu::IMP, 2 },{ "CPX", cpu::CPX, cpu::ABS, 4 },{ "SBC", cpu::SBC, cpu::ABS, 4 },{ "INC", cpu::INC, cpu::ABS, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },
		{ "BEQ", cpu::BEQ, cpu::REL, 2 },{ "SBC", cpu::SBC, cpu::IZY, 5 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "SBC", cpu::SBC, cpu::ZPX, 4 },{ "INC", cpu::INC, cpu::ZPX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "SED", cpu::SED, cpu::IMP, 2 },{ "SBC", cpu::SBC, cpu::ABY, 4 },{ "NOP", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 7 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "SBC", cpu::SBC, cpu::ABX, 4 },{ "INC", cpu::INC, cpu::ABX, 7 },{ "UNO", cpu::UNO, cpu::IMP, 7 },
	};

    void reset(){
    // registers are set to 0x00,
    registers.a = 0;
    registers.x = 0;
    registers.y = 0;
    registers.stack = 0x00 | reserved; //result of OR is 1 if any of the two bits is 1


    
    }


    }

}