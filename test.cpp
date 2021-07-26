
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <iostream>
using namespace std;
using namespace sf;

int main() {
  RenderWindow renderWindow(sf::VideoMode(640, 480), "SFML Demo", Style::Fullscreen);
  renderWindow.setFramerateLimit(60);
  RectangleShape circle(Vector2f(150, 150));
  circle.setFillColor(Color::Red);
  circle.setOrigin(75, 75);
  Event event;
  renderWindow.setKeyRepeatEnabled(true);
  unordered_map<int, bool> keys;
  vector<int> changedKeys;
  while (renderWindow.isOpen()){
    changedKeys.clear();
    while (renderWindow.pollEvent(event)){
      if (event.type == Event::EventType::Closed) renderWindow.close();
      if (event.type == Event::EventType::KeyPressed){
        if (keys.count(event.key.code) == 0){
          keys[event.key.code] = true;
          changedKeys.push_back(event.key.code);
        }
      }
      if (event.type == Event::EventType::KeyReleased){
        if (keys.count(event.key.code) == 1){
          keys.erase(event.key.code);
          changedKeys.push_back(event.key.code);
        }
      }
    }
    renderWindow.clear();
    renderWindow.draw(circle);
    cout << "Currently pressed keys: ";
    for (auto& keyValue : keys)
        cout << keyValue.first << " ";
    cout << endl;
    if (event.type == sf::Event::MouseMoved)
    {
        cout << "new mouse x: " << event.mouseMove.x << endl;
        cout << "new mouse y: " << event.mouseMove.y << endl;
        circle.setPosition(event.mouseMove.x, event.mouseMove.y);

    }
    renderWindow.display();
  }
}
