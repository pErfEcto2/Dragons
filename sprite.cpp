#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include <unistd.h>
#include "iostream"
using namespace std;
using namespace sf;

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
    sf::IntRect rectSourceSprite(0, 0, size, size);
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

  void controlDragon(sf::Event event, bool f) {
    float x_axe = sprite.getPosition().x;
    float y_axe = sprite.getPosition().y;
    if (f == true) {
      if (event.type == event.KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
              rectSourceSprite.top = 106;
              x_axe -= 20;
              sprite.setPosition(x_axe, y_axe);
              sprite.setRotation(90.f);
          }
        if (event.key.code == sf::Keyboard::D) {
            rectSourceSprite.top = 212;
            x_axe += 20;
            sprite.setPosition(x_axe, y_axe);
            sprite.setRotation(-90.f);
        }
        if (event.key.code == sf::Keyboard::W) {
            rectSourceSprite.top = 318;
            y_axe -= 20;
            sprite.setPosition(x_axe, y_axe);
            sprite.setRotation(180.f);
        }
        if (event.key.code == sf::Keyboard::S) {
            rectSourceSprite.top = 0;
            y_axe += 20;
            sprite.setPosition(x_axe, y_axe);
            sprite.setRotation(0.f);
        }
      }
    }
    else {
      if (event.type == event.KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
              rectSourceSprite.top = 106;
              x_axe -= 20;
              sprite.setPosition(x_axe, y_axe);
              sprite.setRotation(90.f);
          }
        if (event.key.code == sf::Keyboard::Right) {
            rectSourceSprite.top = 212;
            x_axe += 20;
            sprite.setPosition(x_axe, y_axe);
            sprite.setRotation(-90);
        }
        if (event.key.code == sf::Keyboard::Up) {
            rectSourceSprite.top = 318;
            y_axe -= 20;
            sprite.setPosition(x_axe, y_axe);
            sprite.setRotation(180.f);
        }
        if (event.key.code == sf::Keyboard::Down) {
            rectSourceSprite.top = 0;
            y_axe += 20;
            sprite.setPosition(x_axe, y_axe);
            sprite.setRotation(0.f);
        }
      }
    }
    this->sprite = sprite;
    this->rectSourceSprite = rectSourceSprite;
  }
};

Dragon dragon_init(Dragon &dragon, bool f) {
  dragon.top_axe = 0;
  dragon.left_axe = 0;
  dragon.size = 106;
  dragon.scale = 2.f;
  dragon.image = "test_9_9.png";
  dragon.setSourceSprite();
  //dragon.setRectSourceSprite();
  dragon.setSmoth(false);
  dragon.setSprite();
  dragon.setScale();
  //dragon.setAnim(0.2);
  dragon.sprite.setOrigin(5.f, 5.f);
  if (f == true) dragon.sprite.setPosition(512.f, 256.f);
  else dragon.sprite.setPosition(256.f, 256.f);
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
  sf::RenderWindow window(sf::VideoMode(1024, 512), "Dragons", sf::Style::Fullscreen);
  //sf::RenderWindow window(sf::VideoMode(1024, 512), "Dragons");
  sf::Event event;
  sf::Music main_theme;
  music_init(main_theme, true);
  unsigned int microsecond = 1000;
  

  Dragon first_dragon;
  first_dragon = dragon_init(first_dragon, true);

  Dragon second_dragon;
  second_dragon = dragon_init(second_dragon, false);
  
  while (window.isOpen()) {
    while (window.pollEvent(event)){
      first_dragon.controlDragon(event, true);
      second_dragon.controlDragon(event, false);
      if (event.type == sf::Event::EventType::Closed) {
        window.close();
        return 0;
      }
    }

    sf::FloatRect hitbox1 = first_dragon.sprite.getGlobalBounds();
    sf::FloatRect hitbox2 = second_dragon.sprite.getGlobalBounds();

    if (first_dragon.sprite.getPosition().x < second_dragon.sprite.getPosition().x + hitbox2.width &&
			  first_dragon.sprite.getPosition().x + hitbox1.width > second_dragon.sprite.getPosition().x &&
			  first_dragon.sprite.getPosition().y < second_dragon.sprite.getPosition().y + hitbox2.height &&
			  hitbox1.height + first_dragon.sprite.getPosition().y > second_dragon.sprite.getPosition().y) {
          std::cout << "Collision Detected at " << std::endl;
          std::cout << first_dragon.sprite.getPosition().x << std::endl;
          std::cout << first_dragon.sprite.getPosition().y << std::endl;
          first_dragon.sprite.setPosition(sf::Vector2f(200, 200));
          second_dragon.sprite.setPosition(sf::Vector2f(1000, 500));
    }

    window.clear(sf::Color::Green);
    window.draw(first_dragon.sprite);
    window.draw(second_dragon.sprite);
    window.display();
    usleep(microsecond);
  }
  return 0;
};

int main(){
  run_game();
  return 0;
}