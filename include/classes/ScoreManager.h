#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <SDL3/SDL.h>
#include <string>

class GameObject;

class ScoreManager {
  private:
    SDL_Renderer* renderer = nullptr;
    GameObject* text_go = nullptr;
    GameObject* write_text_go = nullptr;
    float speed, update_timer, update_interval;
    int score;
    std::string main_text;

    void updateText();

  public:
    ScoreManager(SDL_Renderer*, float);
    void update(float);
    int* getScore();
    void writeScoreText(GameObject*);
    void reset();
};

#endif