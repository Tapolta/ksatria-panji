#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SDL3/SDL.h>
#include <vector>
#include "../enums/GameStatus.h"

class ObstacleManager;
class GroundManager;
class GameObject;
class ScoreManager;
class ObjectManager;

class GameManager {
  private:
    SDL_Renderer* renderer = nullptr;
    GroundManager* ground_manager = nullptr;
    ObstacleManager* obs_manager = nullptr;
    ScoreManager* score_manager = nullptr;
    ObjectManager* object_manager = nullptr;
    char* clicked_char = nullptr;
    std::vector<GameObject*> go_list;
    GameStatus game_status;
    bool is_pause;

  public:
    GameManager(SDL_Renderer*);
    ~GameManager();
    void update(float);
    void addGameObject(GameObject*);
    void inputHandle(const SDL_Event*, bool*);
    void startGame();
    void addGround(GroundManager*);
    void addObstacle(ObstacleManager*);
    void addScore(ScoreManager*);
    void addObjectManager(ObjectManager*);
    void gameOver();
    char* getClickedChar();
};

#endif