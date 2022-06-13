#include <iostream>
#include "cpu.h"
#include "bus.h"

using namespace std;

// imp functions
byte cpu::read(byte2 address){
	return bus->read(address);
}
void cpu::write(byte2 address, byte data){
	bus->write(address, data);
}

void cpu::setFlag(flags flag, int val){
	if (val == 1){
		registers.status |= flag;
		// 1 | 0 = 1, 1 | 1 = 1, 0 | 1 = 1
	}
	else{
		registers.status &= flag;
		// 0 & 0 = 1, 1 & 0 = 0, 0 & 1 = 0
	}
}

byte cpu::getFlag(flags flag){
	return (registers.status & flag > 0) ? 1 : 0;
}  
cpu::cpu(){
        //lookup table constructor 
        OPCODE lookupcode[256] = 
	{
		{ "BRK", cpu::BRK, cpu::IMP, 7 },{ "ORA", cpu::ORA, cpu::INX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 3 },{ "ORA", cpu::ORA, cpu::ZPO, 3 },{ "ASL", cpu::ASL, cpu::ZPO, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "PHP", cpu::PHP, cpu::IMP, 3 },{ "ORA", cpu::ORA, cpu::IMM, 2 },{ "ASL", cpu::ASL, cpu::ACC, 2 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "ORA", cpu::ORA, cpu::ABS, 4 },{ "ASL", cpu::ASL, cpu::ABS, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },
		{ "BPL", cpu::BPL, cpu::REL, 2 },{ "ORA", cpu::ORA, cpu::INY, 5 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "ORA", cpu::ORA, cpu::ZPX, 4 },{ "ASL", cpu::ASL, cpu::ZPX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "CLC", cpu::CLC, cpu::IMP, 2 },{ "ORA", cpu::ORA, cpu::ABY, 4 },{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 7 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "ORA", cpu::ORA, cpu::ABX, 4 },{ "ASL", cpu::ASL, cpu::ABX, 7 },{ "UNO", cpu::UNO, cpu::IMP, 7 },
		{ "JSR", cpu::JSR, cpu::ABS, 6 },{ "AND", cpu::AND, cpu::INX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "BIT", cpu::BIT, cpu::ZPO, 3 },{ "AND", cpu::AND, cpu::ZPO, 3 },{ "ROL", cpu::ROL, cpu::ZPO, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "PLP", cpu::PLP, cpu::IMP, 4 },{ "AND", cpu::AND, cpu::IMM, 2 },{ "ROL", cpu::ROL, cpu::ACC, 2 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "BIT", cpu::BIT, cpu::ABS, 4 },{ "AND", cpu::AND, cpu::ABS, 4 },{ "ROL", cpu::ROL, cpu::ABS, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },
		{ "BMI", cpu::BMI, cpu::REL, 2 },{ "AND", cpu::AND, cpu::INY, 5 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "AND", cpu::AND, cpu::ZPX, 4 },{ "ROL", cpu::ROL, cpu::ZPX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "SEC", cpu::SEC, cpu::IMP, 2 },{ "AND", cpu::AND, cpu::ABY, 4 },{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 7 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "AND", cpu::AND, cpu::ABX, 4 },{ "ROL", cpu::ROL, cpu::ABX, 7 },{ "UNO", cpu::UNO, cpu::IMP, 7 },
		{ "RTI", cpu::RTI, cpu::IMP, 6 },{ "EOR", cpu::EOR, cpu::INX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 3 },{ "EOR", cpu::EOR, cpu::ZPO, 3 },{ "LSR", cpu::LSR, cpu::ZPO, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "PHA", cpu::PHA, cpu::IMP, 3 },{ "EOR", cpu::EOR, cpu::IMM, 2 },{ "LSR", cpu::LSR, cpu::ACC, 2 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "JMP", cpu::JMP, cpu::ABS, 3 },{ "EOR", cpu::EOR, cpu::ABS, 4 },{ "LSR", cpu::LSR, cpu::ABS, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },
		{ "BVC", cpu::BVC, cpu::REL, 2 },{ "EOR", cpu::EOR, cpu::INY, 5 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "EOR", cpu::EOR, cpu::ZPX, 4 },{ "LSR", cpu::LSR, cpu::ZPX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "CLI", cpu::CLI, cpu::IMP, 2 },{ "EOR", cpu::EOR, cpu::ABY, 4 },{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 7 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "EOR", cpu::EOR, cpu::ABX, 4 },{ "LSR", cpu::LSR, cpu::ABX, 7 },{ "UNO", cpu::UNO, cpu::IMP, 7 },
		{ "RTS", cpu::RTS, cpu::IMP, 6 },{ "ADC", cpu::ADC, cpu::INX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 3 },{ "ADC", cpu::ADC, cpu::ZPO, 3 },{ "ROR", cpu::ROR, cpu::ZPO, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "PLA", cpu::PLA, cpu::IMP, 4 },{ "ADC", cpu::ADC, cpu::IMM, 2 },{ "ROR", cpu::ROR, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "JMP", cpu::JMP, cpu::ABI, 5 },{ "ADC", cpu::ADC, cpu::ABS, 4 },{ "ROR", cpu::ROR, cpu::ABS, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },
		{ "BVS", cpu::BVS, cpu::REL, 2 },{ "ADC", cpu::ADC, cpu::INY, 5 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "ADC", cpu::ADC, cpu::ZPX, 4 },{ "ROR", cpu::ROR, cpu::ZPX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "SEI", cpu::SEI, cpu::IMP, 2 },{ "ADC", cpu::ADC, cpu::ABY, 4 },{ "UNO", cpu::NOP, cpu::ACC, 2 },{ "UNO", cpu::UNO, cpu::IMP, 7 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "ADC", cpu::ADC, cpu::ABX, 4 },{ "ROR", cpu::ROR, cpu::ABX, 7 },{ "UNO", cpu::UNO, cpu::IMP, 7 },
		{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "STA", cpu::STA, cpu::INX, 6 },{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "STY", cpu::STY, cpu::ZPO, 3 },{ "STA", cpu::STA, cpu::ZPO, 3 },{ "STX", cpu::STX, cpu::ZPO, 3 },{ "UNO", cpu::UNO, cpu::IMP, 3 },{ "DEY", cpu::DEY, cpu::IMP, 2 },{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "TXA", cpu::TXA, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "STY", cpu::STY, cpu::ABS, 4 },{ "STA", cpu::STA, cpu::ABS, 4 },{ "STX", cpu::STX, cpu::ABS, 4 },{ "UNO", cpu::UNO, cpu::IMP, 4 },
		{ "BCC", cpu::BCC, cpu::REL, 2 },{ "STA", cpu::STA, cpu::INY, 6 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "STY", cpu::STY, cpu::ZPX, 4 },{ "STA", cpu::STA, cpu::ZPX, 4 },{ "STX", cpu::STX, cpu::ZPY, 4 },{ "UNO", cpu::UNO, cpu::IMP, 4 },{ "TYA", cpu::TYA, cpu::IMP, 2 },{ "STA", cpu::STA, cpu::ABY, 5 },{ "TXS", cpu::TXS, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "UNO", cpu::NOP, cpu::IMP, 5 },{ "STA", cpu::STA, cpu::ABX, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },
		{ "LDY", cpu::LDY, cpu::IMM, 2 },{ "LDA", cpu::LDA, cpu::INX, 6 },{ "LDX", cpu::LDX, cpu::IMM, 2 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "LDY", cpu::LDY, cpu::ZPO, 3 },{ "LDA", cpu::LDA, cpu::ZPO, 3 },{ "LDX", cpu::LDX, cpu::ZPO, 3 },{ "UNO", cpu::UNO, cpu::IMP, 3 },{ "TAY", cpu::TAY, cpu::IMP, 2 },{ "LDA", cpu::LDA, cpu::IMM, 2 },{ "TAX", cpu::TAX, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "LDY", cpu::LDY, cpu::ABS, 4 },{ "LDA", cpu::LDA, cpu::ABS, 4 },{ "LDX", cpu::LDX, cpu::ABS, 4 },{ "UNO", cpu::UNO, cpu::IMP, 4 },
		{ "BCS", cpu::BCS, cpu::REL, 2 },{ "LDA", cpu::LDA, cpu::INY, 5 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "LDY", cpu::LDY, cpu::ZPX, 4 },{ "LDA", cpu::LDA, cpu::ZPX, 4 },{ "LDX", cpu::LDX, cpu::ZPY, 4 },{ "UNO", cpu::UNO, cpu::IMP, 4 },{ "CLV", cpu::CLV, cpu::IMP, 2 },{ "LDA", cpu::LDA, cpu::ABY, 4 },{ "TSX", cpu::TSX, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 4 },{ "LDY", cpu::LDY, cpu::ABX, 4 },{ "LDA", cpu::LDA, cpu::ABX, 4 },{ "LDX", cpu::LDX, cpu::ABY, 4 },{ "UNO", cpu::UNO, cpu::IMP, 4 },
		{ "CPY", cpu::CPY, cpu::IMM, 2 },{ "CMP", cpu::CMP, cpu::INX, 6 },{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "CPY", cpu::CPY, cpu::ZPO, 3 },{ "CMP", cpu::CMP, cpu::ZPO, 3 },{ "DEC", cpu::DEC, cpu::ZPO, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "INY", cpu::INY, cpu::IMP, 2 },{ "CMP", cpu::CMP, cpu::IMM, 2 },{ "DEX", cpu::DEX, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "CPY", cpu::CPY, cpu::ABS, 4 },{ "CMP", cpu::CMP, cpu::ABS, 4 },{ "DEC", cpu::DEC, cpu::ABS, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },
		{ "BNE", cpu::BNE, cpu::REL, 2 },{ "CMP", cpu::CMP, cpu::INY, 5 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "CMP", cpu::CMP, cpu::ZPX, 4 },{ "DEC", cpu::DEC, cpu::ZPX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "CLD", cpu::CLD, cpu::IMP, 2 },{ "CMP", cpu::CMP, cpu::ABY, 4 },{ "NOP", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 7 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "CMP", cpu::CMP, cpu::ABX, 4 },{ "DEC", cpu::DEC, cpu::ABX, 7 },{ "UNO", cpu::UNO, cpu::IMP, 7 },
		{ "CPX", cpu::CPX, cpu::IMM, 2 },{ "SBC", cpu::SBC, cpu::INX, 6 },{ "UNO", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "CPX", cpu::CPX, cpu::ZPO, 3 },{ "SBC", cpu::SBC, cpu::ZPO, 3 },{ "INC", cpu::INC, cpu::ZPO, 5 },{ "UNO", cpu::UNO, cpu::IMP, 5 },{ "INX", cpu::INX, cpu::IMP, 2 },{ "SBC", cpu::SBC, cpu::IMM, 2 },{ "NOP", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::SBC, cpu::IMP, 2 },{ "CPX", cpu::CPX, cpu::ABS, 4 },{ "SBC", cpu::SBC, cpu::ABS, 4 },{ "INC", cpu::INC, cpu::ABS, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },
		{ "BEQ", cpu::BEQ, cpu::REL, 2 },{ "SBC", cpu::SBC, cpu::INY, 5 },{ "UNO", cpu::UNO, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 8 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "SBC", cpu::SBC, cpu::ZPX, 4 },{ "INC", cpu::INC, cpu::ZPX, 6 },{ "UNO", cpu::UNO, cpu::IMP, 6 },{ "SED", cpu::SED, cpu::IMP, 2 },{ "SBC", cpu::SBC, cpu::ABY, 4 },{ "NOP", cpu::NOP, cpu::IMP, 2 },{ "UNO", cpu::UNO, cpu::IMP, 7 },{ "UNO", cpu::NOP, cpu::IMP, 4 },{ "SBC", cpu::SBC, cpu::ABX, 4 },{ "INC", cpu::INC, cpu::ABX, 7 },{ "UNO", cpu::UNO, cpu::IMP, 7 },
	};
    
}

// interrupts
void cpu::reset(){
    // registers are set to 0x00, status cleared except unused flag, absolute address = 0xFFFC, PC = address at absolute address, then all registers reset, number of cycles taken = 8
    registers.a = 0x00;
    registers.x = 0x00;
    registers.y = 0x00;
	cycles = 8;

	effAddress = 0xFFFC;
	byte highbit = read(effAddress);
	byte lowbit = read(effAddress + 1);
	registers.pc = (highbit << 8) | (lowbit);

	registers.stack = 0xFD;
    registers.status = 0x00 | useless; //result of OR is 1 if any of the two bits is 1
	effAddress = 0x000; // absolute address = 0
	relAddress = 0x00; //relative address = 0
	dataFetched = 0x00;
}

//can happen if disable irq flag = 0, current instruction finishes b4 calling this irq, PC on stack, status register on stack, after this PC set to 0xFFFE 
void cpu::irq(){
	if(getFlag(interrupt_disable) == 0){
		cycles = 7;
		write(0x100 + registers.stack, (registers.pc >> 8) & 0xFF);
		registers.stack--; 
		// stack pointer changed after each write to it
		 // fixed at RAM address $100, so can address $100-$1ff
		write(0x100 + registers.stack, registers.pc & 0xFF);
		registers.stack--;
		/** since only 8 bytes can be written at a time in our function, pc is written twice
		 * to extract the first 8 bytes, first pc is pushed 8 bits to the right
		 * bit masking to reduce the range to 0-255/make sure the left bits are 0
		 **/

		// break and unused only change when pushing to stack, interrupt_disable = 1
		setFlag(interrupt_disable, 1);
		setFlag(bbreak, 0);
		setFlag(useless, 1);
		write(0x100 + registers.stack, registers.status); 
		registers.stack--;

		// read value that is in location 0xFFFE = pc value
		effAddress = 0xFFFE;
		//unint16_t to make sure shifting does not lose or change the bits
		byte2 lowAdd = read(effAddress);
		byte2 highAdd = read(effAddress + 1); 

		registers.pc = (highAdd << 8) | lowAdd;

		
	}
}

// same as irq, but reads from 0xFFFA and NMI cannot be ignored so flag checking not required
void cpu::nmi(){
	cycles = 8;

	//write PC to effAddress
	write(0x100 + registers.stack, (registers.pc >> 8) & 0xFF);
	write(0x100 + registers.stack, registers.pc & 0xFF); // stack pointer + 0x100 = actual location
	
	// hardware interrupt
	setFlag(interrupt_disable, 1);
	setFlag(bbreak, 0);
	setFlag(useless, 1);
	write(0x100 + registers.stack, registers.status);


	effAddress = 0xFFFA;
	byte2 lowAdd = read(effAddress);
	byte2 highAdd = read(effAddress + 1);

	registers.pc = (highAdd << 8) | lowAdd;

	cycles = 8;
	
}

// counts down a clock cycle, does nothing else
void cpu::sync(){
	if(cycles == 0){
		opcode = read(registers.pc);
		registers.pc++;
		cycles = lookupcode[opcode].cycle;
		//additional cycles will just update the cycles variable themselves
	}

	cycles--;
}

// addressing modes reference: https://www.pagetable.com/c64ref/6502/?tab=3
// https://www.nesdev.org/wiki/CPU_addressing_modes,k
void cpu::ACC() // implies an operation on the accumulator
{
	dataFetched = registers.a;
	registers.pc++;
}

void cpu::IMM() // EA = operand
{
	registers.pc++;
	effAddress = registers.pc;
}
void cpu::ZPO() // operand is of the form $FF as opposed to $00FF, high byte is assumed to be 0
{
	byte low = read(registers.pc);
	byte high = 0x00;
	effAddress = (high << 8) | low;
	registers.pc++;
}
void cpu::ZPX()// zero page operand + x register offset
{
	byte low = read(registers.pc);
	byte high = 0x00;
	effAddress = (high << 8) | low;
	registers.pc++;
	low += registers.x & 0xFF; 
	effAddress = (high << 8) | low;
	// offset changing the page requires additional clock cycles
	if (effAddress > (high << 8)){
		cycles++;
		high = (high + 1) & 0xFF;
		effAddress = (high << 8) | low;
	}
}
void cpu::ZPY()// indexed zero page (y) addressing
{ 
	byte low = read(registers.pc);
	byte high = 0x00;
	effAddress = (high << 8) | low;
	registers.pc++;
	low += registers.y & 0xFF; 
	effAddress = (high << 8) | low;
	// offset changing the page requires additional clock cycles
	if (effAddress > (high << 8)){
		cycles++;
		high = (high + 1) & 0xFF;
		effAddress = (high << 8) | low;
	}
}
void cpu::ABS() // EA = address specified in operand
{
	byte low = read(registers.pc);
	registers.pc++;
	byte high = read(registers.pc);
	registers.pc++;
	effAddress = (high << 8) | low;

}
void cpu::ABX() // EA = address in operand + X register 
{
	byte low = read(registers.pc);
	registers.pc++;
	byte high = read(registers.pc);
	registers.pc++;
	low += registers.x; 
	effAddress = (high << 8) | low;
	// offset changing the page requires additional clock cycles
	if (effAddress > (high << 8)){
		cycles++;
		high = (high + 1) & 0xFF;
		effAddress = (high << 8) | low;
	}
}
void cpu::ABY() // EA = address in operand + Y register
{
	byte low = read(registers.pc);
	registers.pc++;
	byte high = read(registers.pc);
	registers.pc++;
	low += registers.y;
	effAddress = (high << 8) | low;
	// offset changing the page requires additional clock cycles
	if (effAddress > (high << 8)){
		cycles++;
		high = (high + 1) & 0xFF;
		effAddress = (high << 8) | low;
	}
}
void cpu::IMP() // mostly just does something like change status bits
{
	dataFetched = registers.status;
}
void cpu::REL() // for branch instructions EA = pc + offset but offset can be -128 to +127
{
	relAddress = read(registers.pc);
	registers.pc++;
	if (relAddress & 0x80 != 0) // if the higher byte is set, it means our offset is negative
	{
		relAddress |= 0xFF00; // As a result, we append 1 to the MSB indicating it's a negative hex number
	}

}
void cpu::INX() // pc val -> holds address (add1) -> that address (add1) holds another address (add2)
// EA = add2 + x reg
{
	byte2 pcadd = read(registers.pc);
	registers.pc++;

	byte2 low = read((byte2)pcadd + (byte2)registers.x);
	byte2 high = read((byte2)pcadd + (byte2)registers.x + 1); 

	effAddress = (high << 8) | low;

	// adding y to EA could result in a page flip
	if((effAddress & 0xFF00 == high << 8) == 0){
		// EA & 0xFF gives high byte of EA and comparing it with the high byte before offset addition
		// will tell us if the page has changed. This requires a cycle++.
		cycles++;
	}

}
void cpu::INY() // pc val -> holds address (add1) -> that address (add1) holds another address (add2)
// EA = add2 + y reg
{
	byte2 pcadd = read(registers.pc);
	registers.pc++;

	byte2 low = read((byte2)pcadd & 0xFF);
	byte2 high = read((byte2)(pcadd + 1) & 0xFF); 

	effAddress = (high << 8) | low;
	effAddress += registers.y;

	
}

void cpu::ABI() // pc val -> holds address (add1) -> that address (add1) holds another address (add2)
// EA = add2 AKA pointers
{
	byte2 low = read(registers.pc);
	registers.pc++;
	byte2 high = read(registers.pc);
	registers.pc++;

	byte2 ptr = read((high << 8) | low);

	//hardware bug = if low byte is 0xFF, high byte is + 1 (page boundary)
	// instead, chip wraps around to same page

	if(low == 0xFF){ // 
		effAddress = (read(ptr & 0xFF00) << 8) | read(ptr);
		// 0x__FF & 0xFF00 will be 0
	} 
	else{
		effAddress = (read(ptr + 1) << 8) | read(ptr);
	}

}

void cpu::fetch(){
	if(lookupcode[opcode].address != cpu::IMP || lookupcode[opcode].address != cpu::ACC)
	dataFetched = read(effAddress);
}

// opcodes
void cpu::ADC(){
// Acc + [Memory] + Carry
// overflow happens during 
	fetch();
	byte final = dataFetched + registers.a + getFlag(carry);
	setFlag(carry, final > 255); //sets the carry flag when the sum of a binary add exceeds 255 or when the sum of a decimal add exceeds 99
	setFlag(zero, registers.a == 0);
	setFlag(negative, final >> 7);
	setFlag(o)



	

}
void cpu::AND(){

}
void cpu::ASL(){

}
void cpu::BCC(){

}
void cpu::BCS(){

}
void cpu::BEQ(){

}
void cpu::BIT(){
	
}
void cpu::BMI(){

}
void cpu::BNE(){

}
void cpu::BPL(){

}
void cpu::BRK(){

}
void cpu::BVC(){

}
void cpu::BVS(){

}


