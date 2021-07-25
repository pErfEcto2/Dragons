#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include <unistd.h>
#include "iostream"
#include <cstdint>
#include <vector>

using namespace std;
using namespace sf;
// 
bool intersects(Sprite & rect1, const RectangleShape & rect2) {
    FloatRect r1 = rect1.getGlobalBounds();
    FloatRect r2 = rect2.getGlobalBounds();
    return r1.intersects(r2);
}

bool intersectsSprites(Sprite & sprite1, Sprite & sprite2) {
    FloatRect r1 = sprite1.getGlobalBounds();
    FloatRect r2 = sprite2.getGlobalBounds();
    return r1.intersects(r2);
}

int clamp (const int x, const int a, const int b) {
	return min(max(a, x), b);
}
/*
void enemyCollision(Sprite sprite1, Sprite sprite2) {
    if (intersectsSprites(sprite1, sprite2)) {
		FloatRect hitbox1 = sprite1.getGlobalBounds();
		FloatRect hitbox2 = sprite2.getGlobalBounds();
		d.x = clamp(d.x, leftWall.left + leftWall.width + 53, rightWall.left - sprite.getGlobalBounds().width + 25);
		sprite.setPosition(d.x, d.y);
    }
}
*/
Sprite leftRightWallCollision(Sprite sprite, RectangleShape left, RectangleShape right) {
    if (intersects(sprite, left) || intersects(sprite, right)) {
		FloatRect leftWall = left.getGlobalBounds();
		FloatRect rightWall = right.getGlobalBounds();
		Vector2f d = sprite.getPosition();
		d.x = clamp(d.x, leftWall.left + leftWall.width + 33, rightWall.left - sprite.getGlobalBounds().width + 5);
		sprite.setPosition(d.x, d.y);
    }
    return sprite;
}

Sprite topBottomWallCollision(Sprite sprite, RectangleShape top, RectangleShape bottom) {
    if (intersects(sprite, top) || intersects(sprite, bottom)) {
        FloatRect topWall = top.getGlobalBounds();
		FloatRect bottomWall = bottom.getGlobalBounds();
		Vector2f d = sprite.getPosition();
        d.y = clamp(d.y, topWall.top + topWall.width - 1328, bottomWall.top - sprite.getGlobalBounds().height + 9);
        sprite.setPosition(d.x, d.y);
    }
    return sprite;
}

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
        uint32_t index;
        std::vector<Controls> controlButtons = {
            {
                Keyboard::A, Keyboard::D, Keyboard::W, Keyboard::S
            },
            {
                Keyboard::Left, Keyboard::Right, Keyboard::Up, Keyboard::Down
            }
        };
        
    
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

    void set_origin() {
        sprite.setOrigin(size / 2, size / 2);
        this->sprite = sprite;
    }

    void control(Event event, Sprite sprite2) {
        if (event.key.code == controlButtons[index - 1].left) {
            speed_x = -20;
        }
        else if (event.key.code == controlButtons[index - 1].right) {
            speed_x = 20;
        }
        else if (event.key.code == controlButtons[index - 1].up) {
            speed_y = -20;
        }
        else if (event.key.code == controlButtons[index - 1].down) {
            speed_y = 20;
        }
        
        float last_coor_x = sprite.getPosition().x;
        float last_coor_y = sprite.getPosition().y;
        float new_coor_x = last_coor_x + speed_x;
        float new_coor_y = last_coor_y + speed_y;
        sprite.setPosition(new_coor_x, new_coor_y);
        if (intersectsSprites(sprite, sprite2)) {
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
    top.setSize(Vector2f(VideoMode::getDesktopMode().width, 5));
    return top;
};

RectangleShape left_init(RectangleShape left) {
    left.setPosition(0, 0);
    left.setSize(Vector2f(5, VideoMode::getDesktopMode().height));
    return left;
};

RectangleShape right_init(RectangleShape right) {
    right.setPosition(VideoMode::getDesktopMode().width - 5, 0);
	right.setSize(Vector2f(5, VideoMode::getDesktopMode().height));
    return right;
};

RectangleShape bottom_init(RectangleShape bottom) {
    bottom.setPosition(0, VideoMode::getDesktopMode().height - 5);
	bottom.setSize(Vector2f(VideoMode::getDesktopMode().width, 5));
    return bottom;
};

Dragon dragonInit(Dragon dragon) {  
    dragon.top_axe = 0;
    dragon.left_axe = 0;
    dragon.size = 9;
    dragon.scale = 5.f;
    dragon.image = "test_9_9.png";
    dragon.setSourceSprite();
    dragon.setRectSourceSprite();
    dragon.setSmoth(false);
    dragon.setSprite();
    dragon.setScale();
    dragon.set_origin();
    return dragon;
}

int main() {
    std::uint32_t display_width = VideoMode::getDesktopMode().width;
    std::uint32_t display_height = VideoMode::getDesktopMode().height;
    VideoMode resolution(display_width, display_height);
    RenderWindow window(resolution, "Dragons", Style::Fullscreen);
    sf::Event event;
    sf::Music main_theme; // main music theme
    music_init(main_theme, true);
    std::uint32_t microsecond = 1000; // time in microseconds of delay
    Texture backTexture;
    Sprite back;
    
    if (!backTexture.loadFromFile("background.png")) return EXIT_FAILURE;
    else back.setTexture(backTexture);
    back.setScale(2.f, 2.f);

    auto first_dragon = Dragon(1);
    first_dragon = dragonInit(first_dragon);
    first_dragon.sprite.setPosition(256.f, 100.f);

    auto second_dragon = Dragon(2);
    second_dragon = dragonInit(second_dragon);
    second_dragon.sprite.setPosition(400.f, 400.f);

    RectangleShape top;
    RectangleShape left;
    RectangleShape right;
	RectangleShape bottom;

    top = top_init(top);
    left = left_init(left);
    right = right_init(right);
    bottom = bottom_init(bottom);

    while (window.isOpen()) {
        while (window.pollEvent(event)){ // push action like key pressed to "event"
            if (event.KeyPressed) {
                first_dragon.control(event, second_dragon.sprite);
                second_dragon.control(event, first_dragon.sprite);
            }
            //second_dragon.control(event);
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
                return 0;
            }
        }
        first_dragon.sprite = leftRightWallCollision(first_dragon.sprite, left, right);
        first_dragon.sprite = topBottomWallCollision(first_dragon.sprite, top, bottom);
        second_dragon.sprite = leftRightWallCollision(second_dragon.sprite, left, right);
        second_dragon.sprite = topBottomWallCollision(second_dragon.sprite, top, bottom);
        //enemyCollision(first_dragon.sprite, second_dragon.sprite);

        window.clear();
        window.draw(back);
        window.draw(first_dragon.sprite);
        window.draw(second_dragon.sprite);
        window.display();
        usleep(microsecond);
    }
    return 0;
}