#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include <unistd.h>
#include "iostream"
using namespace std;

class Dragon{
  public:
  float top_axe;
  float left_axe;
  float scale;
  sf::Texture texture;
  sf::IntRect rectSourceSprite;
  sf::Sprite sprite;
  sf::Clock clock;
  const char* image;
  int size;

  int setSourceSprite() {
    if (!texture.loadFromFile(image))
        return EXIT_FAILURE;
    this->texture = texture;
  }

  void setScale() {
    sprite.scale(scale, scale);
    this->sprite = sprite;
  }

  void setRectSourceSprite() {
    sf::IntRect rectSourceSprite(top_axe, left_axe, size, size);
    this->rectSourceSprite = rectSourceSprite;
  }
  
  void setSprite() {
    sf::Sprite sprite(texture, rectSourceSprite);
    this->sprite = sprite;
  }

  void setSmoth(bool f) {
    texture.setSmooth(f);
    this->texture = texture;
  }

  void controlDragon(sf::Event event) {
    float x_axe = sprite.getPosition().x;
    float y_axe = sprite.getPosition().y;
    if (event.type == event.KeyPressed) {
      if (event.key.code == sf::Keyboard::A) {
            rectSourceSprite.top = 106;
            x_axe -= 53;
            sprite.setPosition(x_axe, y_axe);

        }
      if (event.key.code == sf::Keyboard::D) {
          rectSourceSprite.top = 212;
          x_axe += 53;
          sprite.setPosition(x_axe, y_axe);

      }
      if (event.key.code == sf::Keyboard::W) {
          rectSourceSprite.top = 318;
          y_axe -= 53;
          sprite.setPosition(x_axe, y_axe);
      }
      if (event.key.code == sf::Keyboard::S) {
          rectSourceSprite.top = 0;
          y_axe += 53;
          sprite.setPosition(x_axe, y_axe);
      }
    this->sprite = sprite;
    this->rectSourceSprite = rectSourceSprite;
    }
  }
    
  void setAnim(float seconds) {
    if (clock.getElapsedTime().asSeconds() > seconds){
      if (rectSourceSprite.left == 212)
        rectSourceSprite.left = 0;
      else
        rectSourceSprite.left += 106;
      sprite.setTextureRect(rectSourceSprite);
      clock.restart();
      this->sprite = sprite;
    }
  }
};

Dragon dragon_init(Dragon &dragon) {
  dragon.top_axe = 0;
  dragon.left_axe = 0;
  dragon.size = 106;
  dragon.scale = 2.f;
  dragon.image = "dragon.png";
  dragon.setSourceSprite();
  dragon.setRectSourceSprite();
  dragon.setSmoth(false);
  dragon.setSprite();
  dragon.setScale();
  dragon.setAnim(0.2);
  return dragon;
};

int music_init(sf::Music &main_theme, bool replay) {
  if (!main_theme.openFromFile("battleship.ogg")) {
    return EXIT_FAILURE;
  }
  main_theme.setLoop(replay);
  main_theme.play();
};

int run_game() {
  //sf::RenderWindow window(sf::VideoMode(1024, 512), "Dragons", sf::Style::Fullscreen);
  sf::RenderWindow window(sf::VideoMode(1024, 512), "Dragons");
  sf::Event event;
  sf::Music main_theme;
  music_init(main_theme, true);
  unsigned int microsecond = 10000;
  

  Dragon first_dragon;
  first_dragon = dragon_init(first_dragon);
  
  while (window.isOpen()) {
    while (window.pollEvent(event)){
      first_dragon.controlDragon(event);
      if (event.type == sf::Event::EventType::Closed) {
        window.close();
        return 0;
      }
    }

    

    window.clear(sf::Color::Green);
    window.draw(first_dragon.sprite);
    window.display();
    usleep(microsecond);
  }
  return 0;
};

int main(){
  run_game();
  return 0;
}