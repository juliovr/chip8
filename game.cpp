#include "chip8.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#define SCALE 20

const unsigned int A = 2048;

Chip8 chip8;

int main() {
  chip8.initialize();

  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE), "Chip8 emulator");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
	window.close();
      }

      if (event.type == sf::Event::KeyPressed) {
          if      (event.key.code == sf::Keyboard::Num1) chip8.keys[0x1] = 1;
          else if (event.key.code == sf::Keyboard::Num2) chip8.keys[0x2] = 1;
          else if (event.key.code == sf::Keyboard::Num3) chip8.keys[0x3] = 1;
          else if (event.key.code == sf::Keyboard::Num4) chip8.keys[0xC] = 1;
          else if (event.key.code == sf::Keyboard::Q)    chip8.keys[0x4] = 1;
          else if (event.key.code == sf::Keyboard::W)    chip8.keys[0x5] = 1;
          else if (event.key.code == sf::Keyboard::E)    chip8.keys[0x6] = 1;
          else if (event.key.code == sf::Keyboard::R)    chip8.keys[0xD] = 1;
          else if (event.key.code == sf::Keyboard::A)    chip8.keys[0x7] = 1;
          else if (event.key.code == sf::Keyboard::S)    chip8.keys[0x8] = 1;
          else if (event.key.code == sf::Keyboard::D)    chip8.keys[0x9] = 1;
          else if (event.key.code == sf::Keyboard::F)    chip8.keys[0xE] = 1;
          else if (event.key.code == sf::Keyboard::Z)    chip8.keys[0xA] = 1;
          else if (event.key.code == sf::Keyboard::X)    chip8.keys[0x0] = 1;
          else if (event.key.code == sf::Keyboard::C)    chip8.keys[0xB] = 1;
          else if (event.key.code == sf::Keyboard::V)    chip8.keys[0xF] = 1;  
      }

      if (event.type == sf::Event::KeyReleased) {
          if      (event.key.code == sf::Keyboard::Num1) chip8.keys[0x1] = 0;
          else if (event.key.code == sf::Keyboard::Num2) chip8.keys[0x2] = 0;
          else if (event.key.code == sf::Keyboard::Num3) chip8.keys[0x3] = 0;
          else if (event.key.code == sf::Keyboard::Num4) chip8.keys[0xC] = 0;
          else if (event.key.code == sf::Keyboard::Q)    chip8.keys[0x4] = 0;
          else if (event.key.code == sf::Keyboard::W)    chip8.keys[0x5] = 0;
          else if (event.key.code == sf::Keyboard::E)    chip8.keys[0x6] = 0;
          else if (event.key.code == sf::Keyboard::R)    chip8.keys[0xD] = 0;
          else if (event.key.code == sf::Keyboard::A)    chip8.keys[0x7] = 0;
          else if (event.key.code == sf::Keyboard::S)    chip8.keys[0x8] = 0;
          else if (event.key.code == sf::Keyboard::D)    chip8.keys[0x9] = 0;
          else if (event.key.code == sf::Keyboard::F)    chip8.keys[0xE] = 0;
          else if (event.key.code == sf::Keyboard::Z)    chip8.keys[0xA] = 0;
          else if (event.key.code == sf::Keyboard::X)    chip8.keys[0x0] = 0;
          else if (event.key.code == sf::Keyboard::C)    chip8.keys[0xB] = 0;
          else if (event.key.code == sf::Keyboard::V)    chip8.keys[0xF] = 0;  
      }
      
    }

    chip8.emulateCycle();
    
    if (chip8.drawFlag) {
      window.clear();
      
      for (int y = 0; y < SCREEN_HEIGHT; y++) {
	for (int x = 0; x < SCREEN_WIDTH; x++) {
          if (chip8.screen[(y * SCREEN_WIDTH) + x] != 0 ) {      
            sf::RectangleShape rectangle(sf::Vector2f(SCALE, SCALE));
            rectangle.setPosition(x * SCALE, y * SCALE);
            rectangle.setFillColor(sf::Color::White);
            
            window.draw(rectangle);
          }
        }
      }
      
      window.display();
    }
    
  }


  return 0;
}
