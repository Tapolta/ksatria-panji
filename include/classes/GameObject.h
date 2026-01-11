#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include <SDL3_ttf/SDL_textengine.h>
#include "../enums/GameStatus.h"
#include "Text.h"

class GameObject {
  private:
    SDL_Renderer* renderer = nullptr;
    Text* text = nullptr;
    std::vector<SDL_Texture*> img_list;
    SDL_Color bg_color;
    GameStatus game_status;
    float anim_speed, anim_timer;
    int current_img;
    bool bg_set;
  
    void renderImg(float);
    void clearImgList();
    void renderBg();

  protected:
    SDL_FRect d_object;

  public:
    GameObject(SDL_Renderer*);
    ~GameObject();
    virtual void update(float);
    virtual void setObjectD(SDL_FRect);
    SDL_FRect getObjectD();
    void setBgColor(SDL_Color);
    SDL_Color getBgColor();
    void setImgPaths(std::vector<std::string>);
    void setGameStatus(GameStatus);
    GameStatus getGameStatus();
    Text* getText();
};

#endif