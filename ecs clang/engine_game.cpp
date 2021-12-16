#include "engine_game.h"

EngineGame EngineGame::instance;
EngineGame::EngineGame() {}
EngineGame &EngineGame::Get() { return instance; };

void EngineGame::Awake() {}
void EngineGame::Start() {}
void EngineGame::Update() {}
void EngineGame::Fixed() {}
void EngineGame::Quit() {}
