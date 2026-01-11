#ifndef INPUTTEXT_H
#define INPUTTEXT_H

#include "GameObject.h"
#include <string>

class InputText : public GameObject {
  private:
    char* clicked_char = nullptr;
    std::string current_text;
    const size_t MAX_LENGTH = 10;

    void processInput();

  public:
    InputText(SDL_Renderer*);
    void setClickedChar(char*);
    void update(float) override;
    std::string getTextInput();
};

#endif
