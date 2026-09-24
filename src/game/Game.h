#pragma once

#include "core/events/Event.h"
namespace game {

enum class GameState {
    Menu,
    Level,
    Paused,
};

struct Game {
    GameState state = GameState::Menu;
};

void OnEvent(Game &, core::Event &);
void OnUpdate(float deltaTime, Game &game);
void OnRender(Game &game);

} // namespace game
