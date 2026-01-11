#include "../include/classes/ScoreManager.h"
#include "../include/classes/GameObject.h"

ScoreManager::ScoreManager(SDL_Renderer* _renderer, float _speed) {
  speed = _speed;
  renderer = _renderer;
  score = 0;
  text_go = new GameObject(_renderer);
  text_go->setGameStatus(GameStatus::Play);
  text_go->getText()->setFontSize(28);
  update_timer = 0.0f;
  update_interval = 0.5f;
}

void ScoreManager::update(float _dt) {
  text_go->update(_dt);

  update_timer += _dt;
  while (update_timer >= update_interval) {
    updateText();
    score++;
    update_timer = 0.0f;
  }
}

void ScoreManager::updateText() {
  main_text = "Score: " + std::to_string(score);
  text_go->getText()->setText(main_text);
  if (write_text_go) writeScoreText(write_text_go);
}

int* ScoreManager::getScore() {
  return &score;
}

void ScoreManager::writeScoreText(GameObject* _go) {
  write_text_go = _go;
  write_text_go->getText()->setText("Score diperoleh: " + std::to_string(score));
}

void ScoreManager::reset() {
  score = 0;
}