#define MEMORY_ADDRESS_START 0x200
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

#ifndef CHIP8_H
#define CHIP8_H

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

  // 64x32 pixels
  unsigned char screen[SCREEN_WIDTH * SCREEN_HEIGHT];

  // delay and sound timer registers that count at 60 hz
  unsigned char delayTimer;
  unsigned char soundTimer;

  // stack and stack pointer
  unsigned short stack[16];
  unsigned short sp;

  // HEX keyboard that has 16 keys which range from 0 to F
  unsigned char keys[16];

  
 public:
  Chip8();
  ~Chip8();

  bool drawFlag;
  
  unsigned char* getScreen() {
    return screen;
  }
  
  void initialize();
  void emulateCycle();

  
};

#endif