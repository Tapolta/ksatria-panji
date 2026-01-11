#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <vector>
#include <SDL3/SDL_audio.h>
#include "../structs/LoopSound.h"
#include "../structs/ActiveSound.h"

class Sound {
  private:
    std::vector<ActiveSound> activeSounds;
    std::vector<LoopSound> loopSounds;
    bool paused = false;

  public:
    Sound();
    ~Sound();
    void playSound(const std::string& path);
    void update(float);
    void playSoundLoop(const std::string& path);
};
#endif