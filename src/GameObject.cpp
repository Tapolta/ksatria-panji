#include "../include/classes/GameObject.h"
#include <SDL3_image/SDL_image.h>

GameObject::GameObject(SDL_Renderer* _renderer) {
  renderer = _renderer;
  current_img = 0;
  anim_speed = 0.1f;
  anim_timer = 0.0f;
  d_object = {0, 0, 0, 0};
  bg_set = false;
  game_status = GameStatus::None;
}

GameObject::~GameObject() {
  if (text) delete text;
  clearImgList();
}

void GameObject::update(float _dt) {
  if (bg_set) renderBg();
  if (!img_list.empty()) renderImg(_dt);
  if (text) text->update(_dt);
}

void GameObject::renderBg() {
  const SDL_FRect rect = d_object;

  SDL_SetRenderDrawColor(
    renderer,
    bg_color.r,
    bg_color.g,
    bg_color.b,
    bg_color.a
  );

  SDL_RenderFillRect(renderer, &rect);
}

void GameObject::renderImg(float _dt) {
  anim_timer += _dt;

  while (anim_timer >= anim_speed) {
    anim_timer -= anim_speed;
    current_img++;
    if (current_img >= img_list.size()) current_img = 0;
  }

  SDL_RenderTexture(renderer, img_list[current_img], NULL, &d_object);
}

void GameObject::setObjectD(SDL_FRect _d_object) {
  d_object = _d_object;
}

SDL_FRect GameObject::getObjectD() {
  return d_object;
}

void GameObject::setBgColor(SDL_Color _color) {
  bg_set = true;
  bg_color = _color;
}

SDL_Color GameObject::getBgColor() {
  return bg_color;
}

void GameObject::setImgPaths(std::vector<std::string> _paths) {
  clearImgList();

  for (std::string path : _paths) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture) {
      SDL_Log("Cannot get image: %s", SDL_GetError());
    } else {
      SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
      SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
      img_list.push_back(texture);
    }
  }
}

void GameObject::setGameStatus(GameStatus _game_status) {
  game_status = _game_status;
}

GameStatus GameObject::getGameStatus() {
  return game_status;
}

Text* GameObject::getText() {
  if (!text) text = new Text(renderer);
  return text;
}

void GameObject::clearImgList() {
  for (SDL_Texture* tex : img_list) SDL_DestroyTexture(tex);
  img_list.clear();
}