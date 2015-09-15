//Example code from http://www.sfml-dev.org/tutorials/2.3/start-linux.php
#include <cassert>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>


int main()
{
  sf::RenderWindow window(sf::VideoMode(1000,600), "SFML example 5");
  sf::RectangleShape shape(sf::Vector2f(500.0,250.0));
  shape.setFillColor(sf::Color::Green);
  shape.setOrigin(250.0,125.0);
  double x = 500.0;
  double y = 300.0;
  double angle = 0.0;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { x += 1.0; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { x -= 1.0; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { y -= 1.0; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { y += 1.0; }

    window.clear();
    window.draw(shape);
    shape.setPosition(x,y);
    shape.setRotation(angle);
    window.display();
  }
}
