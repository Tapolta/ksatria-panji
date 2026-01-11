#ifndef LOOPSOUND_H
#define LOOPSOUND_H

#include <SDL3/SDL_audio.h>

struct LoopSound {
  SDL_AudioStream* stream;
  Uint8* buffer;
  Uint32 length;
  float duration;
  float timer;
};

#endif