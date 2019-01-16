#include "chip8.h"
#include <SFML/Graphics.hpp>

#include <iostream>

#define SCALE 20

Chip8 chip8;

int main() {
  chip8.initialize();

  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH * SCALE, SCREEN_HEIGHT * SCALE), "Chip8 emulator");

  sf::RectangleShape rectangle(sf::Vector2f(100.0f, 100.0f));
  rectangle.setPosition(10.0f, 10.0f);
  rectangle.setFillColor(sf::Color::White);
  
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
	window.close();
      }
    }

    chip8.emulateCycle();
    
    window.clear();
    std::cout << chip8.getScreen() << std::endl;

    if (chip8.drawFlag) {
      std::cout << "imprimir\n";
    }
    //window.draw(rectangle);
    window.display();

  }


  return 0;
}
