#include "../include/classes/ObstacleManager.h"
#include <algorithm>
#include "../include/enums/GameStatus.h"

ObstacleManager::ObstacleManager(SDL_Renderer* _renderer, const WindowProps* _window_props){
  renderer = _renderer;
  window_props = *_window_props;
  interact_offset = 0.0f;
  hit_location = 0;
  spawn_timer = 0.0f;
  spawn_interval = 2.0f;
  spawn_min = 1.0f;
  spawn_max = 5.0f;
  speed_min = 400.0f;
  speed_max = 800.0f;
}

void ObstacleManager::update(float _dt) {
  spawnManager(_dt);

  for (Obstacle* obs : obs_list) {
    obs->update(_dt);

    if (hit_location > 0 && obs->getObjectD().x < (hit_location + interact_offset)) {
      obs->setInteractable(true);
    }
  }

  deleteManager();

  if (player)
    hit_location = player->getObjectD().x;
}

void ObstacleManager::spawnManager(float _dt) {
  spawn_timer += _dt;

  if (spawn_timer >= spawn_interval) {
    spawn_timer = 0.0f;
    spawnObstacle();

    spawn_interval = randomFloat(spawn_min, spawn_max);
  }
}

void ObstacleManager::deleteManager() {
  bool has_input = false;

  obs_list.erase(
    std::remove_if(
      obs_list.begin(),
      obs_list.end(),
      [&](Obstacle* obs) {
        if (clicked_char && *clicked_char != '\0') {
          if (obs->getInteractable()) {
            if (*clicked_char == obs->getChar()) {
              player->heal();
            } else {
              player->takeDamage();
            }
            
            destroyObstacle(obs);
            *clicked_char = '\0';
            has_input = true;
            return true;
          } else {
            if (player) player->takeDamage();
            *clicked_char = '\0';
            return false;
          }
        }

        if (obs->getObjectD().x < 0 || obs->getObjectD().x < hit_location) {
          if (player) player->takeDamage();
          destroyObstacle(obs);
          return true;
        }

        return false;
      }
    ),
    obs_list.end()
  );
}

void ObstacleManager::spawnObstacle() {
  Obstacle* obs = new Obstacle(renderer);

  obs->setGameStatus(GameStatus::Play);
  obs->setObjectD({window_props.width, window_props.height - 350.0f, 100.0f, 100.0f});
  obs->setSpeed(randomFloat(speed_min, speed_max));

  obs_list.push_back(obs);
}

void ObstacleManager::destroyObstacle(Obstacle* obs) {
  delete obs;
}

float ObstacleManager::randomFloat(float _min, float _max) {
  float t = (float)rand() / RAND_MAX;
  return _min + t * (_max - _min);
}

void ObstacleManager::setInteractOffset(float _offset) {
  interact_offset = _offset;
}

void ObstacleManager::setPlayer(Player* _p) {
  player = _p;
}

void ObstacleManager::setClickedChar(char* _char) {
  clicked_char = _char;
}