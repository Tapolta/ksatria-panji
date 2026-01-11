#ifndef GROUNDMANAGER_H
#define GROUNDMANAGER_H

#include "GameObject.h"
#include "../structs/WindowProps.h"
#include <string>
#include <vector>

class GroundManager {
  private:
    SDL_Renderer* renderer;
    WindowProps window_props;
    std::vector<GameObject*> ground_list;
    const int MAX_GROUND = 3;
    float speed;

    void moveGround(float _dt);

  public:
    GroundManager(SDL_Renderer*, const WindowProps*);
    ~GroundManager();
    void update(float);
    void addGround(std::string);
    void deleteGround();
    void setGroundSpeed(float);
};

#endif