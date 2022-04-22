# uwuNES

uwuNES is a Nintendo Entertainment System emulator written in C++. It's named uwuNES because I saw someone call theirs NESchan and I found it funny. 

# CPU
## MOS 6502
The 6502 has: 
- an 8-bit accumulator, 
- 2 8-bit index registers (X and Y), 
- one status register where bit 0 to bit 7 all represent different flags (like Negative, Overflow, Reserved etc.), 
- one 8-bit stack pointer, 
- one 16-bit PC register.

- Zero page addressing kind of "makes up" for the lack of registers. The CPU doesn't have to spend an additional cycle to fetch another high byte. Instead, it accesses the first 256 bytes of the memory map. For example, $65 will imply 0x65.

- The CPU is little-endian i.e. the least significant byte is placed at the beginning.

- There are also are a few functions: Reset, Sync, NM
I (Non-Maskable INterrupt), IRQ (Interrupt Request). 

## Addressing Modes
The 6502 has 151 opcodes. But they are grouped into 56 actual operations or functions. They differ solely by their addressing modes or how the operands/data is fetched. 

- Immediate
- Zero Page
- Zero Page X-Indexed
- Zero Page Y-Indexed
- Indirect X-Indexed
- Indirect Y-Indexed
- Absolute 
- Absolute X-Indexed
- Absolute Y-Indexed

## Executing an instruction
I chose to create a lookup table. Each item in it is an opcode. Within the struct, it has a function pointer to the operation, a function pointer to the addressing mode, and the number of cycles required to execute the instruction.

## Unofficial Opcodes
Usually, most unofficial opcodes execute the equivalent of a NOP (no operation) or they freeze until the Reset button is pressed.

Some have useful effects that games have made use of, but I have not implemented them yet. This is a good page to look at the usable unofficial opcodes: [NESdev](https://www.nesdev.org/wiki/Programming_with_unofficial_opcodes)

# PPU

# APU

# Mappers

# Display

# To-Do
- PPU
- APU
- Mappers
- Literally everything at this point, I'm barely done with the CPU as is.

# References
[NESdev Wiki](https://www.nesdev.org/wiki/Nesdev_Wiki) 

[emudev.de](https://emudev.de)

[Ultimate 6502 Reference](https://www.pagetable.com/c64ref/6502/?tab=3)

[6502 Datasheet](http://archive.6502.org/datasheets/mos_6500_mpu_preliminary_may_1976.pdf)

[NES Mastersheet](https://github.com/xem/nes/blob/gh-pages/cheat%20sheet.txt)

[PPU Emulation](https://www.nesdev.com/NES%20emulator%20development%20guide.txt)


