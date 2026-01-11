#ifndef OBSTACLEMANAGER_H
#define OBSTACLEMANAGER_H

#include <vector>
#include <SDL3/SDL.h>
#include "Obstacle.h"
#include <functional>
#include "Player.h"
#include "../structs/WindowProps.h"

class ObstacleManager {
  private:
    SDL_Renderer* renderer = nullptr;
    Player* player = nullptr;
    char* clicked_char;
    WindowProps window_props;
    std::vector<Obstacle*> obs_list;
    float spawn_timer, spawn_interval, spawn_min, spawn_max, speed_min, speed_max, hit_location, interact_offset;

    void spawnObstacle();
    void destroyObstacle(Obstacle*);
    void spawnManager(float);
    void deleteManager();
    float randomFloat(float, float);

  public:
    ObstacleManager(SDL_Renderer*, const WindowProps*);
    void update(float);
    void setInteractOffset(float);
    void setPlayer(Player*);
    void setClickedChar(char*);
};

#endif