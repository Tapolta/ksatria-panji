#ifndef ACTIVESOUND_H
#define ACTIVESOUND_H

#include <SDL3/SDL_audio.h>

struct ActiveSound {
  SDL_AudioStream* stream;
};

#endif