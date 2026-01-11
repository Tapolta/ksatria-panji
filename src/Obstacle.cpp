#include "../include/classes/Obstacle.h"

Obstacle::Obstacle(SDL_Renderer* _renderer): GameObject(_renderer) {
  generateChar();
  getText()->setText(std::string(1, main_char));
  getText()->setFontSize(60);
  setBgColor({0, 0, 0, 255});
  interactable = false;
}

void Obstacle::generateChar() {
  main_char = 'a' + (rand() % 26);
}

void Obstacle::update(float _dt) {
  GameObject::update(_dt);
  movement(_dt);
  interactableCondition();
}

void Obstacle::setSpeed(float _speed) {
  speed = _speed;
}

float Obstacle::getSpeed() {
  return speed;
}

void Obstacle::movement(float _dt) {
  d_object.x -= speed * _dt;

  getText()->setTextD({
    d_object.x + (d_object.w / 2) - (getText()->getTextD().w / 2),
    d_object.y + (d_object.h / 2) - (getText()->getTextD().h / 2),
    d_object.w,
    d_object.h
  });
}

void Obstacle::setInteractable(bool _interact) {
  interactable = _interact;
}

void Obstacle::interactableCondition() {
  if (interactable) {
    setBgColor({178, 222, 39, 255});
  } else {
    setBgColor({0, 0, 0, 255});
  };
}

char Obstacle::getChar() {
  return main_char;
}

bool Obstacle::getInteractable() {
  return interactable;
}