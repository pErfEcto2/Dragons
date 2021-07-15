#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

int main(int argc, char ** argv){
  sf::RenderWindow window(sf::VideoMode(1024, 512), "Demo Game", sf::Style::Fullscreen);
  sf::Event event;
  sf::IntRect first_rectSourceSprite(0, 0, 106, 106);
  sf::IntRect second_rectSourceSprite(0, 0, 106, 106);
  sf::Texture first_texture;
  sf::Texture second_texture;
  if (!first_texture.loadFromFile("dragon.png"))
        return EXIT_FAILURE;
  if (!second_texture.loadFromFile("dragon.png"))
        return EXIT_FAILURE;
  sf::Sprite first_sprite(first_texture, first_rectSourceSprite);
  sf::Sprite second_sprite(second_texture, second_rectSourceSprite);
  sf::Clock clock;
  first_texture.setSmooth(false);
  second_texture.setSmooth(false);
  first_sprite.scale(sf::Vector2f(2.f, 2.f));
  second_sprite.scale(sf::Vector2f(2.f, 2.f));
  sf::Music main_theme;
  if (!main_theme.openFromFile("battleship.ogg")) {
    return EXIT_FAILURE;
  }
  main_theme.setLoop(true);
  main_theme.play();

  while (window.isOpen()){
    while (window.pollEvent(event)){
      if (event.type == sf::Event::EventType::Closed) {
        window.close();
      }
      else if (event.type == event.KeyPressed) {
      float first_y_axe = first_sprite.getPosition().y;
      float first_x_axe = first_sprite.getPosition().x;
      float second_y_axe = second_sprite.getPosition().y;
      float second_x_axe = second_sprite.getPosition().x;
        if (event.key.code == sf::Keyboard::A) {
            first_rectSourceSprite.top = 106;
            first_x_axe = first_x_axe - 106;
            first_sprite.setPosition(first_x_axe, first_y_axe);
        }
        else if (event.key.code == sf::Keyboard::D) {
            first_rectSourceSprite.top = 212;
            first_x_axe = first_x_axe + 106;
            first_sprite.setPosition(first_x_axe, first_y_axe);
        }
        else if (event.key.code == sf::Keyboard::W) {
            first_rectSourceSprite.top = 318;
            first_y_axe = first_y_axe - 106;
            first_sprite.setPosition(first_x_axe, first_y_axe);
        }
        else if (event.key.code == sf::Keyboard::S) {
            first_rectSourceSprite.top = 0;
            first_y_axe = first_y_axe + 106;
            first_sprite.setPosition(first_x_axe, first_y_axe);
        }

        else if (event.key.code == sf::Keyboard::Left) {
            second_rectSourceSprite.top = 106;
            second_x_axe = second_x_axe - 106;
            second_sprite.setPosition(second_x_axe, second_y_axe);
        }
        else if (event.key.code == sf::Keyboard::Right) {
            second_rectSourceSprite.top = 212;
            second_x_axe = second_x_axe + 106;
            second_sprite.setPosition(second_x_axe, second_y_axe);
        }
        else if (event.key.code == sf::Keyboard::Up) {
            second_rectSourceSprite.top = 318;
            second_y_axe = second_y_axe - 106;
            second_sprite.setPosition(second_x_axe, second_y_axe);
        }
        else if (event.key.code == sf::Keyboard::Down) {
            second_rectSourceSprite.top = 0;
            second_y_axe = second_y_axe + 106;
            second_sprite.setPosition(second_x_axe, second_y_axe);
        }
      }
    }
   if (clock.getElapsedTime().asSeconds() > 0.2f){
      if (first_rectSourceSprite.left == 212)
        first_rectSourceSprite.left = 0;
      else if (second_rectSourceSprite.left == 212)
        second_rectSourceSprite.left = 0;
      else
        first_rectSourceSprite.left += 106;
        second_rectSourceSprite.left += 106;

      first_sprite.setTextureRect(first_rectSourceSprite);
      clock.restart();
    }
    
    window.clear(sf::Color::Green);
    window.draw(first_sprite);
    window.draw(second_sprite);
    window.display();
  }
}
