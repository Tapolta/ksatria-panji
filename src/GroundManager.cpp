#include "../include/classes/GroundManager.h"
#include "../include/enums/GameStatus.h"

GroundManager::GroundManager(SDL_Renderer* _renderer, const WindowProps* _window_props) {
  renderer = _renderer;
  window_props = *_window_props;
}

GroundManager::~GroundManager() {
  deleteGround();  
}

void GroundManager::update(float _dt) {
  if (ground_list.empty()) return;

  for (GameObject* go : ground_list) go->update(_dt);
  moveGround(_dt);
}

void GroundManager::addGround(std::string _path) {
  deleteGround();

  for (int i = 0; i < MAX_GROUND; ++i) {
    GameObject* go = new GameObject(renderer);
    go->setImgPaths({_path});
    go->setObjectD({
      i * (window_props.width), window_props.height - 150.0f, window_props.width, 150.0f
    });
    go->setGameStatus(GameStatus::None);
    ground_list.push_back(go);
  }
}

void GroundManager::moveGround(float _dt) {
  GameObject* rightMostGround = ground_list[0];

  for (GameObject* g : ground_list) {
    if (g->getObjectD().x > rightMostGround->getObjectD().x) {
      rightMostGround = g;
    }
  }

  for (GameObject* i : ground_list) {
    SDL_FRect d = i->getObjectD();
    d.x -= speed * _dt;
    i->setObjectD(d);

    if (d.x < -d.w) {
      SDL_FRect newD = d;
      newD.x = rightMostGround->getObjectD().x + rightMostGround->getObjectD().w - 1.0f;
      i->setObjectD(newD);

      rightMostGround = i;
    }
  }
}

void GroundManager::deleteGround() {
  for (GameObject* gl : ground_list) delete gl;
  ground_list.clear();
}

void GroundManager::setGroundSpeed(float _speed) {
  speed = _speed;
}