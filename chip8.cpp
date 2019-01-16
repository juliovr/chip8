#include <iostream>
#include <fstream>

#include "chip8.h"

Chip8::Chip8() {
  // empty
}

Chip8::~Chip8() {
  // empty
}

void Chip8::initialize() {
  pc     = MEMORY_ADDRESS_START; // Program counter starts at 0x200 memory location.
  opcode = 0; // Reset current opcode
  I      = 0; // Reset index register
  sp     = 0; // Reset stack pointer

  drawFlag = false;
  
  // load program
  std::ifstream ifs("/home/julio/Downloads/BMP Viewer - Hello (C8 example) [Hap, 2005].ch8", std::ifstream::in | std::ifstream::binary | std::ifstream::ate);

  int length = ifs.tellg();
  ifs.seekg(0, ifs.beg);
  
  std::cout << "Reading " << length << " characters..." << std::endl;

  char *buffer = new char[length];
  
  ifs.read(buffer, length);

  if (!ifs) {
    std::cout << "Error: only " << ifs.gcount() << " could be read" << std::endl;
    delete[] buffer;
    return;
  }
  
  std::cout << "All characters read successfully." << std::endl;
  
  ifs.close();
  
  for (int i = 0; i < length; ++i) {
    memory[i + MEMORY_ADDRESS_START] = buffer[i];
  }

  delete[] buffer;
}

void Chip8::emulateCycle() {
  // Reset drawFlag
  drawFlag = false;
  
  // Fetch opcode
  opcode = memory[pc] << 8 | memory[pc + 1];

  std::cout << "Opcode to execute: " << std::hex << opcode << std::endl;

  // Decode opcode
  switch (opcode & 0xF000) {

  case 0x0000: // 0NNN, 00E0, 00EE
    switch (opcode & 0x000F) {
    case 0x0000: // 00E0
      // TODO
      pc += 2;
      break;

    case 0x000E: // 00EE
      pc = stack[--sp];
      break;

    default:
      std::cout << "Unknown opcode: " << std::hex << opcode << std::endl;
      break;
    }
    break;

  case 0x1000: // 1NNN
    pc = opcode & 0x0FFF;
    break;

  case 0x2000: // 2NNN
    stack[sp++] = pc;
    pc = opcode & 0x0FFF;
    break;

  case 0x3000: // 3XNN
    if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)) {
      pc += 2;
    }

    pc += 2;
    break;

  case 0x4000: // 4XNN
    if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)) {
      pc += 2;
    }

    pc += 2;
    break;

  case 0x5000: // 5XY0
    if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4]) {
      pc += 2;
    }

    pc += 2;
    break;

  case 0x6000: // 6XNN
    V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
    pc += 2;
    break;

  case 0x7000: // 7XNN
    V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
    pc += 2;
    break;

  case 0x8000: // 8XY0, 8XY1, 8XY2, 8XY3, 8XY4, 8XY5, 8XY6, 8XY7, 8XYE
    switch (opcode & 0x000F) {
    case 0x0000: // 8XY0
      V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
      pc += 2;
      break;

    case 0x0001: // 8XY1
      V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
      pc += 2;
      break;

    case 0x0002: // 8XY2
      V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];
      pc += 2;
      break;

    case 0x0003: // 8XY3
      V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
      pc += 2;
      break;

    case 0x0004: // 8XY4
      if (V[(opcode & 0x0F00) >> 8] > (0xFF - V[(opcode & 0x00F0) >> 4]))
	V[0xF] = 1;
      else
	V[0xF] = 0;

      V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
      pc += 2;
      break;

    case 0x0005: // 8XY5
      if (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4])
	V[0xF] = 1;
      else
	V[0xF] = 0;

      V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
      pc += 2;
      break;

    case 0x0006: // 8XY6
      V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x1;
      V[(opcode & 0x0F00) >> 8] >>= 1;
      pc += 2;
      break;

    case 0x0007: // 8XY7
      if (V[(opcode & 0x00F0) >> 4] > V[(opcode & 0x0F00) >> 8])
	V[0xF] = 1;
      else
	V[0xF] = 0;

      pc += 2;
      break;

    case 0x000E: // 8XYE
      V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x80;
      V[(opcode & 0x0F00) >> 8] <<= 1;
      pc += 2;
      break;
      
      default:
	std::cout << "Unknown opcode: " << std::hex << opcode << std::endl;
	break;
    }
    break;

  case 0x9000: // 9XY0
    if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4]) {
      pc += 4;
    }
    break;
    
  case 0xA000: // ANNN
    I = opcode & 0x0FFF;
    pc += 2;
    break;

  case 0xB000: // BNNN
    pc = V[0] + (opcode & 0x0FFF);
    break;

  case 0xC000: // CXNN
    // TODO
    break;

  case 0xD000: // DXYN
    {
      unsigned char width = 8;
      unsigned char height = opcode & 0x000F;

      drawFlag = true;
      
      // TODO implement draw function
    }
    break;

  case 0xE000: // EX9E, EXA1
    switch (opcode & 0x000F) {
    case 0x000E: // EX9E
      // TODO
      break;

    case 0x0001: // EXA1
      // TODO
      break;

    default:
      std::cout << "Unknown opcode: " << std::hex << opcode << std::endl;
      break;
    }
    break;

  case 0xF000:
    switch (opcode & 0x00FF) {
    case 0x0007: // FX07
      // TODO
      break;

    case 0x000A: // FX0A
      // TODO
      break;

    case 0x0015: // FX15
      // TODO
      break;

    case 0x0018: //FX18
      // TODO
      break;

    case 0x001E: // FX1E
      // TODO
      break;

    case 0x0029: // FX29
      // TODO
      break;

    case 0x0033: // FX33
      // TODO
      break;

    case 0x0055: // FX55
      // TODO
      break;

    case 0x0065: // FX65
      {
	unsigned char X = (opcode & 0x0F00) >> 8;
	for (int i = 0; i <= X; i++) {
	  V[i] = memory[I + i];
	}

	pc += 2;
      }
      break;
      
    default:
      std::cout << "Unknown opcode: " << std::hex << opcode << std::endl;
      break;
    }
    break;
    
  default:
    std::cout << "Unknown opcode: " << std::hex << opcode << std::endl;
    break;
  }

  // Update timers
  
}
