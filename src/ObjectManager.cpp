#include "../include/classes/ObjectManager.h"
#include <algorithm>
#include <cstdlib>

ObjectManager::ObjectManager(SDL_Renderer* _renderer, float _speed, WindowProps _window_props) {
  renderer = _renderer;
  speed = _speed;
  timer = 0.0f;
  next_time = randomFloat(2.0f, 5.0f);
  obj_path = "assets/pohon/pohon.png";
  window_props = _window_props;
}

ObjectManager::~ObjectManager() {
  for (GameObject* obj : obj_list) delete obj;
  obj_list.clear();
}

void ObjectManager::update(float _dt) {
  timer += _dt;
  if (timer >= next_time) {
    timer = 0.0f;
    next_time = randomFloat(2.0f, 5.0f);

    GameObject* obj = new GameObject(renderer);
    obj->setImgPaths({ obj_path });
    obj->setObjectD({ window_props.width, window_props.height - 530.0f, 400.0f, 500.0f });
    obj_list.push_back(obj);
  }

  for (GameObject* go : obj_list) {
    SDL_FRect d = go->getObjectD();
    d.x -= speed * _dt;
    go->setObjectD(d);
    go->update(_dt);
  }

  auto it = obj_list.begin();
  while (it != obj_list.end()) {
    SDL_FRect d = (*it)->getObjectD();
    if (d.x + d.w < 0.0f) {
      delete *it;
      it = obj_list.erase(it);
    } else {
      ++it;
    }
  }
}

float ObjectManager::randomFloat(float _min, float _max) {
  float t = (float)rand() / RAND_MAX;
  return _min + t * (_max - _min);
}
