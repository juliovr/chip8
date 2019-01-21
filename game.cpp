#include "chip8.h"
#include <SFML/Graphics.hpp>

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
