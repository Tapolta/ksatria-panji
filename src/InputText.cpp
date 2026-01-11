#include "../include/classes/InputText.h"

InputText::InputText(SDL_Renderer* _renderer) : GameObject(_renderer) {
  current_text = "";
  getText()->setText("_");
}

void InputText::setClickedChar(char* _char) {
  clicked_char = _char;
}

void InputText::update(float _dt) {
  GameObject::update(_dt);
  processInput();
}

void InputText::processInput() {
  if (!clicked_char || *clicked_char == '\0') return;

  if (*clicked_char == '\b') {
    if (!current_text.empty()) {
      current_text.pop_back();
    }
  } else if (*clicked_char >= 'a' && *clicked_char <= 'z') {
    if (current_text.size() < MAX_LENGTH) {
      current_text.push_back(*clicked_char);
    }
  }

  getText()->setText(current_text + "_");
  *clicked_char = '\0';
}

std::string InputText::getTextInput() {
  return current_text;
}
