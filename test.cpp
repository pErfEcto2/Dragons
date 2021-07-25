#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <iostream>
using namespace std;
using namespace sf;

int main() {
  RenderWindow renderWindow(sf::VideoMode(640, 480), "SFML Demo");
  Event event;
  renderWindow.setKeyRepeatEnabled(false);
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
    cout << "Currently pressed keys: ";
    for (auto& keyValue : keys)
        cout << keyValue.first << " ";
    cout << endl;
  }
}