//Example code from http://www.sfml-dev.org/tutorials/2.3/start-linux.php

#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(1000,600), "SFML example 2");
  sf::RectangleShape shape(sf::Vector2f(500.0,250.0));
  shape.setFillColor(sf::Color::Green);
  shape.setOrigin(250.0,125.0);
  shape.setPosition(500,300);
  double angle = 0.0;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(shape);
    shape.setRotation(angle);
    window.display();
    angle += 1.0;
  }
}
