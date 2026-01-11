#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <ctime>
#include "include/structs/WindowProps.h"
#include "include/classes/GameManager.h"
#include "include/classes/GameObject.h"
#include "include/enums/GameStatus.h"
#include "include/classes/GroundManager.h"
#include "include/classes/ObstacleManager.h"
#include "include/classes/Player.h"
#include "include/classes/InputText.h"
#include "include/classes/ScoreManager.h"
#include "include/classes/ObjectManager.h"

bool initLibrary();
void loop();
void clear();
void game();

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
GameManager* game_manager = nullptr;
const WindowProps window_props = {"Window 1", 1000.0f, 600.0f};

int main() {
  if (!initLibrary()) return 1;

  window = SDL_CreateWindow(
    window_props.name.c_str(), 
    window_props.width, 
    window_props.height,
    SDL_WINDOW_BORDERLESS 
  );
  if (!window) return 1;

  renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) return 1;

  game();

  loop();

  clear();

  return 0;
}

bool initLibrary() {
  bool isInit = SDL_Init(SDL_INIT_VIDEO) && TTF_Init() && SDL_Init(SDL_INIT_AUDIO);
  return isInit;
}

void loop() {
  bool running = true;
  SDL_Event event;
  uint64_t last_time = SDL_GetTicksNS();

  while (running) {
    while(SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) running = false;
      if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_ESCAPE) {
          running = false;
        }

        game_manager->inputHandle(&event, &running);
      }
    }

    uint64_t current_time = SDL_GetTicksNS();
    float dt = (current_time - last_time) / 1e9f;
    last_time = current_time;
    
    SDL_SetRenderDrawColor(renderer, 13, 180, 185, 255);
    SDL_RenderClear(renderer);

    game_manager->update(dt);
    
    SDL_RenderPresent(renderer);
  }
}

void clear() {
  if (game_manager) delete game_manager;
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void game() {
  srand(time(NULL));

  game_manager = new GameManager(renderer);
  
  ScoreManager* score_manager = new ScoreManager(renderer, 300.0f);
  game_manager->addScore(score_manager);

  Player* player = new Player(renderer, window_props.width / 8, game_manager);
  player->setImgPaths({
    "assets/panji/RUN1.png",
    "assets/panji/RUN2.png",
    "assets/panji/RUN3.png",
    "assets/panji/RUN4.png",
    "assets/panji/RUN5.png",
    "assets/panji/RUN6.png",
    "assets/panji/RUN7.png"
  });
  player->setObjectD({-75.0f, window_props.height - 325.0f, 300.0f, 300.0f});
  player->setGameStatus(GameStatus::Play);
  game_manager->addGameObject(player);

  GameObject* musuh = new GameObject(renderer);
  musuh->setImgPaths({
    "assets/musuh/musuh1.png",
    "assets/musuh/musuh2.png",
    "assets/musuh/musuh3.png",
    "assets/musuh/musuh4.png",
    "assets/musuh/musuh5.png",
    "assets/musuh/musuh6.png",
  });
  musuh->setGameStatus(GameStatus::Play);
  musuh->setObjectD({-75.0f, window_props.height - 400.0f, 300.0f, 300.0f});
  game_manager->addGameObject(musuh);

  GroundManager* gm = new GroundManager(renderer, &window_props);
  gm->addGround("assets/ground/grass.png");
  gm->setGroundSpeed(300.0f);
  game_manager->addGround(gm);

  GameObject* title = new GameObject(renderer);
  title->getText()->setText("Ksatria Panji");
  title->getText()->setFontSize(72);
  title->getText()->setTextColor({255, 0, 0, 255});
  title->getText()->setTextD({50.0f, 0.0f, 0.0f, 0.0f});
  title->setGameStatus(GameStatus::Menu);
  game_manager->addGameObject(title);

  GameObject* start_text = new GameObject(renderer);
  start_text->getText()->setText("1. Mulai!");
  start_text->getText()->setFontSize(48);
  start_text->getText()->setTextD({50.0f,(window_props.height / 2) - 100.0f, 0.0f, 0.0f});
  start_text->setGameStatus(GameStatus::Menu);
  game_manager->addGameObject(start_text);

  GameObject* leaderboard_text = new GameObject(renderer);
  leaderboard_text->getText()->setText("2. Leaderboard");
  leaderboard_text->getText()->setFontSize(48);
  leaderboard_text->getText()->setTextD({50.0f, (window_props.height / 2), 0.0f, 0.0f});
  leaderboard_text->setGameStatus(GameStatus::Menu);
  game_manager->addGameObject(leaderboard_text);

  GameObject* exit_text = new GameObject(renderer);
  exit_text->getText()->setText("3. Keluar");
  exit_text->getText()->setFontSize(48);
  exit_text->getText()->setTextD({50.0f, (window_props.height / 2) + 100.0f, 0.0f, 0.0f});
  exit_text->setGameStatus(GameStatus::Menu);
  game_manager->addGameObject(exit_text);

  GameObject* pause_text = new GameObject(renderer);
  pause_text->setGameStatus(GameStatus::Pause);
  pause_text->getText()->setText("Permainan di pause");
  pause_text->getText()->setFontSize(48);
  pause_text->getText()->setTextD({
    window_props.width / 2,
    0.0f,
    0.0f,
    0.0f
  });
  game_manager->addGameObject(pause_text);

  GameObject* game_over_text = new GameObject(renderer);
  game_over_text->getText()->setText("Permainan Berakhir!");
  game_over_text->getText()->setFontSize(72);
  game_over_text->getText()->setTextD({50.0f, 0.0f, 0.0f, 0.0f});
  game_over_text->setGameStatus(GameStatus::GameOver);
  game_manager->addGameObject(game_over_text);

  ObstacleManager* obs_manager = new ObstacleManager(renderer, &window_props);
  obs_manager->setInteractOffset(300.0f);
  obs_manager->setPlayer(player);
  obs_manager->setClickedChar(game_manager->getClickedChar());
  game_manager->addObstacle(obs_manager);

  InputText* input_text = new InputText(renderer);
  input_text->setGameStatus(GameStatus::GameOver);
  input_text->setClickedChar(game_manager->getClickedChar());
  input_text->setBgColor({0,0,0,225});
  input_text->setObjectD({
    50.0f,
    window_props.height - 400.0f,
    200.0f,
    40.0f
  });
  input_text->getText()->setTextD(input_text->getObjectD());
  game_manager->addGameObject(input_text);

  GameObject* simpan_text = new GameObject(renderer);
  simpan_text->getText()->setText("Simpan");
  simpan_text->getText()->setFontSize(24);
  simpan_text->getText()->setTextD({50.0f, input_text->getObjectD().y + 60.0f, 0.0f, 0.0f});
  simpan_text->setGameStatus(GameStatus::GameOver);
  game_manager->addGameObject(simpan_text);

  GameObject* masukkan_nama_text = new GameObject(renderer);
  masukkan_nama_text->getText()->setText("Masukkan nama");
  masukkan_nama_text->getText()->setFontSize(36);
  masukkan_nama_text->getText()->setTextD({50.0f, input_text->getObjectD().y - 60.0f, 0.0f, 0.0f});
  masukkan_nama_text->setGameStatus(GameStatus::GameOver);
  game_manager->addGameObject(masukkan_nama_text);

  GameObject* total_score = new GameObject(renderer);
  total_score->getText()->setFontSize(36);
  total_score->getText()->setTextD({50.0f, input_text->getObjectD().y - 120.0f, 0.0f, 0.0f});
  total_score->getText()->setTextColor({255, 0, 0, 255});;
  total_score->setGameStatus(GameStatus::GameOver);
  score_manager->writeScoreText(total_score);
  game_manager->addGameObject(total_score);

  ObjectManager* obj_manager = new ObjectManager(renderer, 200.0f, window_props);
  game_manager->addObjectManager(obj_manager);
}
