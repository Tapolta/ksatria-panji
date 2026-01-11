#include "../include/classes/Player.h"
#include "../include/classes/GameManager.h"
#include "../include/classes/Sound.h"
#include <string>

Player::Player(SDL_Renderer* _renderer, float _distance, GameManager* _gm) : GameObject(_renderer) {
  game_manager = _gm;
  move_distance = _distance;
  health = MAX_HEALTH;
  boost = MIN_BOOST;
  sound = new Sound();
}

Player::~Player() {
  delete sound;
}

void Player::update(float _dt) {
  GameObject::update(_dt);

  if (!soundStarted) {
    sound->playSoundLoop("assets/sound/running.wav");
    soundStarted = true;
  }

  sound->update(_dt);
}

void Player::takeDamage() {
  if (health > MIN_HEALTH) {
    sound->playSound("assets/sound/damage.wav");
    health--;
    d_object.x -= move_distance;
    setBoostText(18, "Boost ");
  }
  
  if (health == MIN_HEALTH)
    playerDead();
}

void Player::heal() {
  if (boost < MAX_BOOST) {
    sound->playSound("assets/sound/success.wav");
    boost++;
  }
  
  boostMove();
}

void Player::boostMove() {
  if (boost == MAX_BOOST && health < MAX_HEALTH) {
    health++;
    sound->playSound("assets/sound/swoop.wav");
    d_object.x += move_distance;
    boost = MIN_BOOST;
  }

  setBoostText(18, "Boost ");
}

void Player::playerDead() {
  if (game_manager) {
    sound->playSound("assets/sound/death.wav");
    game_manager->gameOver();
    health = MAX_HEALTH;
    boost = MIN_BOOST;
    setObjectD(d_object);
  }
}

void Player::setObjectD(SDL_FRect _d_object) {
  d_object = {
    _d_object.x + (move_distance * health),
    _d_object.y,
    _d_object.w,
    _d_object.h
  };

  setBoostText(18, "Boost ");
}

void Player::setBoostText(float _size, std::string _text) {
  getText()->setText(_text + std::to_string(boost));
  getText()->setFontSize(_size);
  getText()->setTextD({
    d_object.x + (d_object.w / 2) - (d_object.w / 6),
    d_object.y + (d_object.h / 6),
    d_object.w,
    d_object.h
  });
}