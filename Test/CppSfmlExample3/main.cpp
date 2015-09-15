//Example code from http://www.sfml-dev.org/tutorials/2.3/start-linux.php
#include <cassert>
#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(1000,600), "SFML example 3");
  sf::RectangleShape shape(sf::Vector2f(500.0,250.0));
  shape.setFillColor(sf::Color::Green);
  shape.setOrigin(250.0,125.0);
  double x = 500.0;
  double y = 300.0;
  double angle = 0.0;

  while (window.isOpen())
  {
    bool connected = sf::Joystick::isConnected(0);
    if (connected)
    {
      const int n_buttons = sf::Joystick::getButtonCount(0);

      for (int i=0; i!=n_buttons; ++i)
      {
        const bool pressed1 = sf::Joystick::isButtonPressed(0, i);
        angle += pressed1 ? 1.0 : 0.0;
      }

      if (sf::Joystick::hasAxis(0, sf::Joystick::X))
      {
        const double dx{sf::Joystick::getAxisPosition(0, sf::Joystick::X)};
        x += (dx / 100.0);
      }
      if (sf::Joystick::hasAxis(0, sf::Joystick::Y))
      {
        const double dy{sf::Joystick::getAxisPosition(0, sf::Joystick::Y)};
        y += (dy / 100.0);
      }
    }

    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(shape);
    shape.setPosition(x,y);
    shape.setRotation(angle);
    window.display();
  }
}
