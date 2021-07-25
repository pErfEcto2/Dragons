#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include <unistd.h>
#include "iostream"
#include <cstdint>
#include <vector>

using namespace std;
using namespace sf;
// this fun returns "true" if rect2 crosses rect1
bool intersects(Sprite & rect1, const RectangleShape & rect2) {
    FloatRect r1 = rect1.getGlobalBounds();
    FloatRect r2 = rect2.getGlobalBounds();
    return r1.intersects(r2);
}
// like "intersects", but with sprites
bool intersectsSprites(Sprite & sprite1, Sprite & sprite2) {
    FloatRect r1 = sprite1.getGlobalBounds();
    FloatRect r2 = sprite2.getGlobalBounds();
    return r1.intersects(r2);
}
// 
int clamp (const int x, const int a, const int b) {
	return min(max(a, x), b);
}
// checks sprite crosses left or right wall
Sprite leftRightWallCollision(Sprite sprite, RectangleShape left, RectangleShape right) {
    if (intersects(sprite, left) || intersects(sprite, right)) {
		FloatRect leftWall = left.getGlobalBounds();
		FloatRect rightWall = right.getGlobalBounds();
		Vector2f d = sprite.getPosition();
		d.x = clamp(d.x, leftWall.left + leftWall.width + 28, rightWall.left - sprite.getGlobalBounds().width + 11);
		sprite.setPosition(d.x, d.y);
    }
    return sprite;
}
// checks sprites crosses top or bottom wall
Sprite topBottomWallCollision(Sprite sprite, RectangleShape top, RectangleShape bottom) {
    if (intersects(sprite, top) || intersects(sprite, bottom)) {
        FloatRect topWall = top.getGlobalBounds();
		FloatRect bottomWall = bottom.getGlobalBounds();
		Vector2f d = sprite.getPosition();
        d.y = clamp(d.y, topWall.top + topWall.width - 1328, bottomWall.top - sprite.getGlobalBounds().height + 14);
        sprite.setPosition(d.x, d.y);
    }
    return sprite;
}
// struct with all dragon actions
struct Controls {
    Keyboard::Key left, right, up, down;
};


class Dragon {
    public:
        float top_axe; // set x0 axe for sprite
        float left_axe; // set y0 axe for sprite
        float scale; // set in/decrease coefficient 
        Texture texture; // set texture source
        IntRect rectSourceSprite; // set right image for texture
        Sprite sprite; // do sprite using texture
        const char* image; // string with our image source
        int size; // len of a square side of texture
        int speed_x = 0;
        int speed_y = 0;
        uint32_t index; // dragon index
        int speed; // moving in pixels
        // vector with controll buttons
        std::vector<Controls> controlButtons = {
            {
                Keyboard::A, Keyboard::D, Keyboard::W, Keyboard::S
            },
            {
                Keyboard::Left, Keyboard::Right, Keyboard::Up, Keyboard::Down
            }
        };
        
    // set dragon index
    Dragon (uint32_t index_) : index{index_} {
    }

    // set source file with texture
    int setSourceSprite() {
        if (!texture.loadFromFile(image))
            cout << "Failed to load image" << endl;
        this->texture = texture;
    }
    // set scale of sprite
    void setScale() {
        sprite.scale(scale, scale);
        this->sprite = sprite;
    }
    // set x0, y0 and size of texture square side
    void setRectSourceSprite() {
        IntRect rectSourceSprite(top_axe, left_axe, size, size);
        this->rectSourceSprite = rectSourceSprite;
    }
    // do sprite
    void setSprite() {
        Sprite sprite(texture, rectSourceSprite);
        this->sprite = sprite;
    }
    // set smoth of sprite
    void setSmoth(bool f) {
        texture.setSmooth(f);
        this->texture = texture;
    }
    void control(Event event, Sprite sprite2, RectangleShape shape1, RectangleShape shape2, RectangleShape shape3, RectangleShape shape4, RectangleShape shape5) {
        if (event.key.code == controlButtons[index - 1].left) {
            speed_x = -1 * speed;
            sprite.setRotation(-90);
        }
        else if (event.key.code == controlButtons[index - 1].right) {
            speed_x = speed;
            sprite.setRotation(90);
        }
        else if (event.key.code == controlButtons[index - 1].up) {
            speed_y = -1 * speed;
            sprite.setRotation(0);
        }
        else if (event.key.code == controlButtons[index - 1].down) {
            speed_y = speed;
            sprite.setRotation(180);
        }
        
        float last_coor_x = sprite.getPosition().x;
        float last_coor_y = sprite.getPosition().y;
        float new_coor_x = last_coor_x + speed_x;
        float new_coor_y = last_coor_y + speed_y;
        sprite.setPosition(new_coor_x, new_coor_y);
        // if sprite crosses another sprite or obstacle sprite moves back
        if (intersectsSprites(sprite, sprite2) || \
            intersects(sprite, shape1) || \
            intersects(sprite, shape2) || \
            intersects(sprite, shape3) || \
            intersects(sprite, shape4) || \
            intersects(sprite, shape5)) {
            sprite.setPosition(last_coor_x, last_coor_y);
        }
        speed_x = 0;
        speed_y = 0;
        this->sprite = sprite;
    }
};

int music_init(sf::Music &main_theme, bool replay) {
    if (!main_theme.openFromFile("battleship.ogg")) return EXIT_FAILURE;
    main_theme.setLoop(replay);
    main_theme.play();
};

RectangleShape top_init(RectangleShape top) {
    top.setPosition(0, 0);
    top.setSize(Vector2f(VideoMode::getDesktopMode().width, 10));
    return top;
};

RectangleShape left_init(RectangleShape left) {
    left.setPosition(0, 0);
    left.setSize(Vector2f(10, VideoMode::getDesktopMode().height));
    return left;
};

RectangleShape right_init(RectangleShape right) {
    right.setPosition(VideoMode::getDesktopMode().width - 10, 0);
	right.setSize(Vector2f(10, VideoMode::getDesktopMode().height));
    return right;
};

RectangleShape bottom_init(RectangleShape bottom) {
    bottom.setPosition(0, VideoMode::getDesktopMode().height - 10);
	bottom.setSize(Vector2f(VideoMode::getDesktopMode().width, 10));
    return bottom;
};

RectangleShape doSquare(int sideLen, int x, int y) {
    RectangleShape rect(Vector2f(sideLen, sideLen));
    rect.setPosition(Vector2f(x, y));
    rect.setOrigin(Vector2f(sideLen / 2, sideLen / 2));
    return rect;
}

Dragon dragonInit(Dragon dragon) {
    dragon.speed = 10;
    dragon.top_axe = 0;
    dragon.scale = 0.08;
    dragon.setScale();
    return dragon;
}

int main() {
    // define window resolution
    uint32_t display_width = VideoMode::getDesktopMode().width;
    uint32_t display_height = VideoMode::getDesktopMode().height;
    VideoMode resolution(display_width, display_height);
    RenderWindow window(resolution, "Dragons", Style::Fullscreen);
    Event event;
    Music main_theme;
    music_init(main_theme, true);
    uint32_t microsecond = 1000; // time in microseconds of delay
    Texture backTexture; // background texture
    Sprite back; // background

    RectangleShape square1;
    RectangleShape square2;
    RectangleShape square3;
    RectangleShape square4;
    RectangleShape square5;
    RectangleShape top;
    RectangleShape right;
    RectangleShape left;
    RectangleShape bottom;
    square1 = doSquare(91, 171, 160);
    square1.setFillColor(Color(114, 80, 12));
    square2 = doSquare(91, 171, 590);
    square2.setFillColor(Color(114, 80, 12));
    square3 = doSquare(91, 1181, 160);
    square3.setFillColor(Color(114, 80, 12));
    square4 = doSquare(91, 1181, 590);
    square4.setFillColor(Color(114, 80, 12));
    square5 = doSquare(180, 676, 375);
    square5.setFillColor(Color(114, 80, 12));
    top = top_init(top);
    left = left_init(left);
    right = right_init(right);
    bottom = bottom_init(bottom);
    // background initializes 
    if (!backTexture.loadFromFile("background.png")) return EXIT_FAILURE;
    backTexture.setSmooth(true);
    back.setTexture(backTexture);
    back.setScale(2.f, 2.f);
    // make first dragon
    auto first_dragon = Dragon(1);
    first_dragon = dragonInit(first_dragon);
    first_dragon.sprite.setPosition(70, 50);
    first_dragon.sprite.setOrigin(633.5, 553.5);
    first_dragon.sprite.setRotation(-90);
    // do second dragon
    auto second_dragon = Dragon(2);
    second_dragon = dragonInit(second_dragon);
    second_dragon.sprite.setPosition(1294, 738);
    second_dragon.sprite.setOrigin(633.5, 553.5);
    second_dragon.sprite.setRotation(90);

    Texture texture;
    if (!texture.loadFromFile("dragon.png", IntRect(0, 0, 1200, 1100))) {
        cout << "Failed" << endl;
    }
    first_dragon.sprite.setTexture(texture);
    second_dragon.sprite.setTexture(texture);

    while (window.isOpen()) {
        while (window.pollEvent(event)){ // push action like key pressed to "event"
            if (event.KeyPressed) {
                first_dragon.control(event, second_dragon.sprite, square1, square2, square3, square4, square5);
                second_dragon.control(event, first_dragon.sprite, square1, square2, square3, square4, square5);
            }
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
                return 0;
            }
        }
        first_dragon.sprite = leftRightWallCollision(first_dragon.sprite, left, right);
        first_dragon.sprite = topBottomWallCollision(first_dragon.sprite, top, bottom);
        second_dragon.sprite = leftRightWallCollision(second_dragon.sprite, left, right);
        second_dragon.sprite = topBottomWallCollision(second_dragon.sprite, top, bottom);
        //draw all
        window.clear();
        window.draw(back);
        window.draw(square1);
        window.draw(square2);
        window.draw(square3);
        window.draw(square4);
        window.draw(square5);
        window.draw(first_dragon.sprite);
        window.draw(second_dragon.sprite);
        window.display();
        usleep(microsecond);
    }
}