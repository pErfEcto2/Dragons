#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include <unistd.h>
#include "iostream"
using namespace std;
using namespace sf;

bool can_move(Sprite sprite1, Sprite sprite2, FloatRect hitbox1, FloatRect hitbox2, int speed_x, int speed_y) {
  int test_x1 = sprite1.getPosition().x + speed_x;
  int test_y1 = sprite1.getPosition().y + speed_y;
  int test_x2 = sprite2.getPosition().x + speed_x;
  int test_y2 = sprite2.getPosition().y + speed_y;
  if ((test_x1 < (test_x2 + hitbox2.width)) &&
     ((test_x1 + hitbox1.width) > test_x2) &&
     (test_y1 < (test_y2 + hitbox2.height)) &&
     ((hitbox1.height + test_y1) > test_y2)) {
        return false;
  }
  else return true;
};

Sprite move_sprite_back(Sprite sprite) {

};

/*
sprite1.getPosition().x + speed_x < sprite2.getPosition().x + speed_x + hitbox2.width &&
sprite1.getPosition().x + speed_x + hitbox1.width > sprite2.getPosition().x + speed_x &&
sprite1.getPosition().y + speed_y < sprite2.getPosition().y + speed_y + hitbox2.height &&
hitbox1.height + sprite1.getPosition().y + speed_y > sprite2.getPosition().y + speed_y
*/
class Dragon{
  public:
  float top_axe; // set x0 axe for sprite
  float left_axe; // set y0 axe for sprite
  float scale; // set in/decrease coefficient 
  sf::Texture texture; // set texture source
  sf::IntRect rectSourceSprite; // set right image for texture
  sf::Sprite sprite; // do texture
  sf::Clock clock; // just clock
  const char* image; // string with our image source
  sf::Keyboard key_right;
  int size; // len of a square side of texture
  // set source file with texture
  int setSourceSprite() {
    if (!texture.loadFromFile(image))
        return EXIT_FAILURE;
    this->texture = texture;
  }
  // set scale of sprite
  void setScale() {
    sprite.scale(scale, scale);
    this->sprite = sprite;
  }
  // set x0, y0 and size of texture square side
  void setRectSourceSprite() {
    sf::IntRect rectSourceSprite(top_axe, left_axe, size, size);
    this->rectSourceSprite = rectSourceSprite;
  }
  // do sprite
  void setSprite() {
    sf::Sprite sprite(texture, rectSourceSprite);
    this->sprite = sprite;
  }
  // set smoth of sprite
  void setSmoth(bool f) {
    texture.setSmooth(f);
    this->texture = texture;
  }
  // function to control a dragon sprite
  void controlDragon(sf::Event event, bool f, Sprite sprite1, Sprite sprite2, FloatRect hitbox1, FloatRect hitbox2) {
    float x_axe = sprite.getPosition().x;
    float y_axe = sprite.getPosition().y;
    // "if f == true" means that we want to control first sprite
    if (f == true) {
      if (event.type == event.KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
          speed_x = -20;
          if (can_move(sprite1, sprite2, hitbox1, hitbox2, speed_x, speed_y)) {
              sprite.setPosition(x_axe, y_axe);
              sprite.setRotation(-90.f); // left rotate 
          }
          else {
            speed_x = 0;
            cout << "cant move left" << endl;
          }
        }
        if (event.key.code == sf::Keyboard::D) {
          speed_x = 20;
          if (can_move(sprite1, sprite2, hitbox1, hitbox2, speed_x, speed_y)) {
            sprite.setPosition(x_axe, y_axe);
            sprite.setRotation(90.f); // right rotate
          }
          else {
            speed_x = 0;
            cout << "cant move right" << endl;
          }
        } 
        if (event.key.code == sf::Keyboard::W) {
          speed_y = -20;
          if (can_move(sprite1, sprite2, hitbox1, hitbox2, speed_x, speed_y)) {
            sprite.setPosition(x_axe, y_axe);
            sprite.setRotation(0.f); // up rotate
          }
          else {
            speed_y = 0;
            cout << "cant move up" << endl;
          }
        }
        if (event.key.code == sf::Keyboard::S) {
          speed_y = 20;
          if (can_move(sprite1, sprite2, hitbox1, hitbox2, speed_x, speed_y)) {
            sprite.setPosition(x_axe, y_axe);
            sprite.setRotation(180.f); // down rotate
          }
          else {
            speed_y = 0;
            cout << "cant move down" << endl;
          }
        }
      }
    }
    // "if f == false" means that we want to control second sprite
    else {
      if (event.type == event.KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
          speed_x = -20;
          if (can_move(sprite1, sprite2, hitbox1, hitbox2, speed_x, speed_y)) {
            sprite.setPosition(x_axe, y_axe);
            sprite.setRotation(-90.f); //left rotate
          }
          else {
            speed_x = 0;
            cout << "cant move left" << endl;
          }
        }
        if (event.key.code == sf::Keyboard::Right) {
          speed_x = 20;
          if (can_move(sprite1, sprite2, hitbox1, hitbox2, speed_x, speed_y)) {
            sprite.setPosition(x_axe, y_axe);
            sprite.setRotation(90); // right rotate
          }
          else {
            speed_x = 0;
            cout << "cant move right" << endl;
          }
        }
        if (event.key.code == sf::Keyboard::Up) {
          speed_y = -20;
          if (can_move(sprite1, sprite2, hitbox1, hitbox2, speed_x, speed_y)) {
            sprite.setPosition(x_axe, y_axe);
            sprite.setRotation(0.f); // up rotate
          }
          else {
            speed_y = 0;
            cout << "cant move up" << endl;
          }
        }
        if (event.key.code == sf::Keyboard::Down) {
          speed_y = 20;
          if (can_move(sprite1, sprite2, hitbox1, hitbox2, speed_x, speed_y)) {
            sprite.setPosition(x_axe, y_axe);
            sprite.setRotation(180.f); // down rotate
          }
          else {
            speed_y = 0;
            cout << "cant move down" << endl;
          }
        }
      }
    }
    x_axe += speed_x;
    y_axe += speed_y;
    this->sprite = sprite;
  }
};
// this fun initializes a dragon object
Dragon dragon_init(Dragon &dragon, bool f) {
  dragon.top_axe = 0;
  dragon.left_axe = 0;
  dragon.size = 9;
  dragon.scale = 10.f;
  dragon.image = "test_9_9.png";
  dragon.setSourceSprite();
  dragon.setRectSourceSprite();
  dragon.setSmoth(false);
  dragon.setSprite();
  dragon.setScale();
  dragon.sprite.setOrigin(4.5, 4.5);
  if (f == true) dragon.sprite.setPosition(256.f, 200.f);
  else dragon.sprite.setPosition(256.f, 100.f);
  return dragon;
};
//this fun initializes music
int music_init(sf::Music &main_theme, bool replay) {
  if (!main_theme.openFromFile("battleship.ogg")) return EXIT_FAILURE;
  main_theme.setLoop(replay);
  main_theme.play();
};

RectangleShape top_init(RectangleShape top) {
  top.setPosition(0, 0);
  top.setSize(Vector2f(VideoMode::getDesktopMode().width, 5));
	top.setFillColor(Color::Yellow);
  return top;
};

RectangleShape left_init(RectangleShape left) {
  left.setPosition(0, 0);
  left.setSize(Vector2f(5, VideoMode::getDesktopMode().height));
	left.setFillColor(Color::Yellow);
  return left;
};

RectangleShape right_init(RectangleShape right) {
  right.setPosition(VideoMode::getDesktopMode().width - 5, 0);
	right.setSize(Vector2f(5, VideoMode::getDesktopMode().height));
	right.setFillColor(Color::Yellow);
  return right;
};

RectangleShape bottom_init(RectangleShape bottom) {
  bottom.setPosition(0, VideoMode::getDesktopMode().height - 5);
	bottom.setSize(Vector2f(VideoMode::getDesktopMode().width, 5));
	bottom.setFillColor(Color::Yellow);
  return bottom;
};

int run_game() {
  sf::VideoMode VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
  RenderWindow window(VideoMode, "Dragons");
  sf::Event event;
  sf::Music main_theme; // main music theme
  music_init(main_theme, true);
  unsigned int microsecond = 1000; // time in microseconds of delay
  

  Dragon first_dragon;
  first_dragon = dragon_init(first_dragon, true);

  Dragon second_dragon;
  second_dragon = dragon_init(second_dragon, false);

  RectangleShape top;
  RectangleShape left;
  RectangleShape right;
	RectangleShape bottom;

  top = top_init(top);
  left = left_init(left);
  right = right_init(right);
  bottom = bottom_init(bottom);

  // make hitboxes for first and second object
  sf::FloatRect hitbox1 = first_dragon.sprite.getGlobalBounds();
  sf::FloatRect hitbox2 = second_dragon.sprite.getGlobalBounds();

  while (window.isOpen()) {
    while (window.pollEvent(event)){ // push action like key pressed to "event"
      first_dragon.controlDragon(event, true, first_dragon.sprite, second_dragon.sprite, hitbox1, hitbox2);
      second_dragon.controlDragon(event, false, first_dragon.sprite, second_dragon.sprite, hitbox1, hitbox2);
      if (event.type == sf::Event::EventType::Closed) {
        window.close();
        return 0;
      }
    }
    /*
    // check if one hitbox touches second hitbox
    if (first_dragon.sprite.getPosition().x < second_dragon.sprite.getPosition().x + hitbox2.width &&
			  first_dragon.sprite.getPosition().x + hitbox1.width > second_dragon.sprite.getPosition().x &&
			  first_dragon.sprite.getPosition().y < second_dragon.sprite.getPosition().y + hitbox2.height &&
			  hitbox1.height + first_dragon.sprite.getPosition().y > second_dragon.sprite.getPosition().y) {
          first_dragon.sprite.setPosition(sf::Vector2f(200, 200));
          second_dragon.sprite.setPosition(sf::Vector2f(1000, 500));
    }
    */
    window.clear(Color::Green); // set screen color to green
    window.draw(top);
    window.draw(left);
    window.draw(right);
    window.draw(bottom);
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