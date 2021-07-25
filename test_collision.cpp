#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>
using namespace sf;
using namespace std;
 
bool intersects (const RectangleShape & rect1, const RectangleShape & rect2) {
    FloatRect r1 = rect1.getGlobalBounds();
    FloatRect r2 = rect2.getGlobalBounds();
    return r1.intersects (r2);
}
 
int clamp (const int x, const int a, const int b) {
	return min(max(a, x), b);
}
 
int main() {
  	const int width = 640;
  	const int height= 480;
  	unsigned int microsecond = 500;
 
	Font font;
	if(!font.loadFromFile("font.ttf"))
		cout << "ERROR" << endl;
	Texture redball;
	if(!redball.loadFromFile("ball.png"))
		return -1;
 
  	VideoMode videoMode(width, height);
  	RenderWindow window(videoMode,"Rectangle Collision", Style::Default);

	//walls
  	RectangleShape top;
  	RectangleShape left;
  	RectangleShape right;
	RectangleShape bottom;
	//bricks
	RectangleShape brick1;
	brick1.setSize(Vector2f(60, 12));
	brick1.setPosition(40, 40);
	brick1.setFillColor(Color::Blue);
 
	//paddle
	RectangleShape paddle;
	paddle.setPosition(width / 2 - 45, height - 62);
	paddle.setSize(Vector2f(90, 12));
	paddle.setFillColor(Color::Red);
		
	//ball
	RectangleShape ball;
	ball.setPosition(width / 2, height / 2);
	ball.setSize(Vector2f(20, 20));
	ball.setTexture(&redball);
	Vector2<float> ballSpeed(0.15, 0.15);

  	top.setPosition(0, 0);
  	top.setSize(Vector2f(width, 5));
	top.setFillColor(Color::Yellow);
 
	bottom.setPosition(0, height - 5);
  	bottom.setSize(Vector2f(width, 5));
	bottom.setFillColor(Color::Yellow);
 
  	left.setPosition(0, 0);
  	left.setSize(Vector2f(5, height));
	left.setFillColor(Color::Yellow);
 
	right.setPosition(width - 5, 0);
	right.setSize(Vector2f(5, height));
	right.setFillColor(Color::Yellow);
	
	Text gamename, start, won, lost;
	gamename.setFont(font);
	gamename.setString("Arkanoid");
	gamename.setCharacterSize(48);
	gamename.setColor(Color::Red);
	gamename.setPosition(210, 100);
	//start
	start.setFont(font);
	start.setString("Press SPACE to start");
	start.setCharacterSize(32);
	start.setColor(Color::Green);
	start.setPosition(165, 200);
	//won
	won.setFont(font);
	won.setString("You won!");
	won.setCharacterSize(32);
	won.setStyle(Text::Bold);
	won.setColor(Color::Green);
	won.setPosition(250, 200);
	//lost
	lost.setFont(font);
	lost.setString("Game Over!");
	lost.setCharacterSize(24);
	lost.setStyle(Text::Bold);
	lost.setColor(Color::Red);
	lost.setPosition(250, 200);
	//GameStates
	enum GameStates {STARTSCREEN, GAME, WIN, GAMEOVER};
	int gameState = STARTSCREEN;
    while (window.isOpen()) {
      	window.clear(Color::White);
			switch(gameState) {
				case STARTSCREEN:
					window.draw(gamename);
					window.draw(start);
					break;
				case GAME:
					window.draw(top);
					window.draw(left);
					window.draw(right);
					window.draw(brick1);
					window.draw(paddle);
					window.draw(ball);
					break;
				case WIN:
					window.draw(won);
					break;
				case GAMEOVER:
					window.draw(lost);
					break;
			}
    	window.display();
    	Event event;
    	while (window.pollEvent(event)) {
    	  	if ((event.type == Event::Closed) || ((event.type == Event::KeyPressed) && (event.key.code==Keyboard::Escape)))
    	      	window.close();
			else if((event.type == Event::KeyPressed) && (event.key.code==Keyboard::Space) && (gameState == STARTSCREEN))
				gameState = GAME;
    	}
			if(gameState!=GAME)
				continue;
			ball.move(ballSpeed.x, ballSpeed.y);
			//move paddle
			if(Keyboard::isKeyPressed(Keyboard::Left)) {
				paddle.move(-0.3, 0);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right)) {
				paddle.move(0.3, 0);
			}
			//keep paddle inside the window
			if (intersects(paddle, left) || intersects(paddle, right)) {
				FloatRect leftWall = left.getGlobalBounds();
				FloatRect rightWall = right.getGlobalBounds();
				Vector2f p = paddle.getPosition();
				p.x = clamp(p.x, leftWall.left + leftWall.width + 1, rightWall.left-paddle.getGlobalBounds().width - 1);
				paddle.setPosition(p.x, p.y);
			}
			//ball collides with walls
			if(intersects(ball, top)) {
				ballSpeed.y = -ballSpeed.y;
			}
			if(intersects(ball, left) || intersects(ball, right)) {
				ballSpeed.x = -ballSpeed.x;
			}
	
			//ball collides with paddle
			if(intersects(ball, paddle)) {
				ballSpeed.y= -ballSpeed.y;
			}
	
			//ball collides with bricks
			if(intersects(ball, brick1)) {
				FloatRect b1 = brick1.getGlobalBounds();
				FloatRect bBall = ball.getGlobalBounds();
				brick1.move(width+1, height+1);
				ballSpeed.y= -ballSpeed.y;
			}

			//Game won
			if(brick1.getPosition().x > width) {
				gameState = WIN;
			}
			//game over
			if(ball.getPosition().y > height) {
				gameState = GAMEOVER;
			}
    	usleep(microsecond);
  	}
  return EXIT_SUCCESS;
}