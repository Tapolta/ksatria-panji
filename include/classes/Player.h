#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include "GameObject.h"

class GameManager;
class Sound;

class Player : public GameObject {
  private:
    GameManager* game_manager = nullptr;
    Sound* sound = nullptr;
    const int MAX_HEALTH = 3, MIN_HEALTH = 0, MAX_BOOST = 3, MIN_BOOST = 0;
    int health, boost;
    float move_distance;
    bool soundStarted = false;

    void playerDead();
    void boostMove();
    void setBoostText(float, std::string);
  
  public:
    Player(SDL_Renderer*, float, GameManager*);
    ~Player();
    void update(float) override;
    void setObjectD(SDL_FRect) override;
    void takeDamage();
    void heal();
};

#endif