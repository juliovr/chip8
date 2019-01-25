#ifndef CHIP8_H
#define CHIP8_H

#define MEMORY_ADDRESS_START 0x200

const unsigned short FONT_SET_LENGTH = 80;
const unsigned short KEYS_LENGTH = 16;
const unsigned int SCREEN_WIDTH = 64;
const unsigned int SCREEN_HEIGHT = 32;
const unsigned int SCREEN_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT;

class Chip8 {
 private:
  // opcode of 2 bytes long
  unsigned short opcode;

  // 4K total of memory. System reserves first 512 bytes (0x200)
  unsigned char memory[4096];

  // registers, going from V0 to VF
  unsigned char V[16];

  // register for memory address
  unsigned short I;

  // program counter
  unsigned short pc;

  // delay and sound timer registers that count at 60 hz
  unsigned char delayTimer;
  unsigned char soundTimer;

  // stack and stack pointer
  unsigned short stack[16];
  unsigned short sp;


  
  unsigned char fontSet[FONT_SET_LENGTH] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
  };
  
 public:
  Chip8();
  ~Chip8();

  unsigned char screen[SCREEN_SIZE];
  
  // HEX keyboard that has 16 keys which range from 0 to F
  unsigned char keys[KEYS_LENGTH];

  bool drawFlag;

  void initialize();
  void emulateCycle();

  
};

#endif // CHIP8_H
