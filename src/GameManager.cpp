#include "../include/classes/GameManager.h"
#include "../include/classes/GameObject.h"
#include "../include/classes/GroundManager.h"
#include "../include/classes/ObstacleManager.h"
#include "../include/classes/ScoreManager.h"
#include "../include/classes/ObjectManager.h"

GameManager::GameManager(SDL_Renderer* _renderer) {
  renderer = _renderer;
  game_status = GameStatus::Menu;
  is_pause = true;
  clicked_char = new char;
}

GameManager::~GameManager() {
  if (!go_list.empty()) 
    for (GameObject* go : go_list)
      delete go;

  if (ground_manager) delete ground_manager;
  if (obs_manager) delete obs_manager;
  if (score_manager) delete score_manager;
}

void GameManager::update(float _dt) {
  float dt = is_pause ? 0.0f : _dt;

  switch (game_status) {
    case GameStatus::Play:
      if (obs_manager) obs_manager->update(dt);
      if (score_manager) score_manager->update(dt);
      if (object_manager) object_manager->update(dt);
      break;
    default:
    break;
  }

  for (GameObject* go : go_list) {
    if (go->getGameStatus() == game_status) go->update(dt);

    if (is_pause)
      if (go->getGameStatus() == GameStatus::Pause) go->update(_dt);
  }
  
  if (ground_manager) ground_manager->update(dt);
}

void GameManager::addGameObject(GameObject* _go) {
  go_list.push_back(_go);
}

void GameManager::inputHandle(const SDL_Event* _event, bool* _running) {
  SDL_Keycode key = SDL_GetKeyFromScancode(_event->key.scancode, SDL_KMOD_NONE, true);
  char c = (char)key;

  if (game_status == GameStatus::Menu) {
    if (_event->key.key == SDLK_1) {
      startGame();
    }

    if (_event->key.key == SDLK_2) {
      // showLeaderboard();
    }

    if (_event->key.key == SDLK_3) {
      *_running = false;
    }
  } else if (game_status == GameStatus::Play) {
    if (_event->key.key == SDLK_SPACE) {
      is_pause = !is_pause;
    }
  } else if (game_status == GameStatus::GameOver) {
    if (_event->key.key == SDLK_RETURN) {
      game_status = GameStatus::Menu;
    }
  }

  if (c >= 'A' && c <= 'Z') c = c + 32;
  if (c >= 'a' && c <= 'z' || c == '\b') {
    *clicked_char = c;
  }
}

void GameManager::startGame() {
  game_status = GameStatus::Play;
  is_pause = false;
  if (score_manager) score_manager->reset();
  *clicked_char = '\0';
}

void GameManager::addGround(GroundManager* _ground_manager) {
  ground_manager = _ground_manager;
}

void GameManager::addObstacle(ObstacleManager* _obs_manager) {
  obs_manager = _obs_manager;
}

void GameManager::addScore(ScoreManager* _score_manager) {
  score_manager = _score_manager;
}

void GameManager::addObjectManager(ObjectManager* _object_manager) {
  object_manager = _object_manager;
}

void GameManager::gameOver() {
  is_pause = true;
  game_status = GameStatus::GameOver;
}

char* GameManager::getClickedChar() {
  return clicked_char;
}