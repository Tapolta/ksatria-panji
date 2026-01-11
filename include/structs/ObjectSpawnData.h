#ifndef OBJECTSPAWNDATA_H
#define OBJECTSPAWNDATA_H

#include <string>

class GameObject;

struct ObjectSpawnData
{
  GameObject* go;
  float max_spawn_speed;
  float min_spawn_speed;
  float speed;
};

#endif