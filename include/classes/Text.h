#ifndef TEXT_H
#define TEXT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class Text {
  private:
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* text_texture;
    TTF_Font* font;
    SDL_FRect d_object;
    SDL_Color color;
    std::string main_text;
    float font_size;
    std::string font_path;

    void renderText();
    void setFont();
    
  public:
    Text(SDL_Renderer* _renderer);
    void update(float _dt);
    void setText(std::string _text);
    void setFontSize(float _size);
    void setTextColor(SDL_Color _color);
    SDL_Color getTextColor();
    void setTextD(SDL_FRect _d_object);
    SDL_FRect getTextD();
};

#endif