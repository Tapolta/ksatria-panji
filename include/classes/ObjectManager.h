#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include "GameObject.h"
#include "../structs/WindowProps.h"

class ObjectManager {
private:
    SDL_Renderer* renderer;
    std::vector<GameObject*> obj_list;
    std::string obj_path;
    WindowProps window_props;

    float timer = 0.0f;
    float next_time = 0.0f;
    float speed;

public:
    ObjectManager(SDL_Renderer*, float, WindowProps);
    ~ObjectManager();

    void update(float dt);
    float randomFloat(float min, float max);
};

#endif
