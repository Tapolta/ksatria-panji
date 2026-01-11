#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"
#include <string>
#include <SDL3/SDL.h>

class Obstacle : public GameObject  {
  private:
    SDL_Renderer* renderer = nullptr;
    float speed;
    char main_char;
    bool interactable;

    void movement(float);
    void generateChar();
    void interactableCondition();

  public:
    Obstacle(SDL_Renderer*);
    void update(float) override;
    void setSpeed(float);
    float getSpeed();
    void setInteractable(bool);
    bool getInteractable();
    char getChar();
};

#endif