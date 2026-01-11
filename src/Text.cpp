#include "../include/classes/Text.h"

Text::Text(SDL_Renderer* _renderer) {
  renderer = _renderer;
  font_size = 24.0f;

  font_path = "assets/font/LoveDays-2v7Oe.ttf";
  font = TTF_OpenFont(font_path.c_str(), font_size);
  color = {255, 255, 255, 255};
}

void Text::setFont() {
  if (text_texture) SDL_DestroyTexture(text_texture);
  
  SDL_Surface* text_surface = TTF_RenderText_Blended(
    font,
    main_text.c_str(), 
    SDL_strlen(main_text.c_str()), 
    color
  );

  if (!text_surface) {
    SDL_Log("Render text error: %s", SDL_GetError());
    return;
  }

  text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
  SDL_DestroySurface(text_surface);
}

void Text::update(float _dt) {
  renderText();
}

void Text::renderText() {
  if (!text_texture || !font) return;
  SDL_GetTextureSize(text_texture, &d_object.w, &d_object.h);
  SDL_RenderTexture(renderer, text_texture, nullptr, &d_object);
}

void Text::setText(std::string _text) {
  main_text = _text;
  setFont();
}

void Text::setFontSize(float _size) {
  if (_size < 0) return;
  font_size = _size;
  TTF_CloseFont(font);
  font = TTF_OpenFont(font_path.c_str(), font_size);
  setText(main_text);
}

SDL_FRect Text::getTextD() {
  return d_object;
}

void Text::setTextD(SDL_FRect _d_object) {
  d_object = _d_object;
}

void Text::setTextColor(SDL_Color _color) {
  color = _color;
  setText(main_text);
}