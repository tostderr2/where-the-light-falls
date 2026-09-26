#pragma once

#include "core/events/Event.h"

namespace InGame {
enum class GameState {
    Menu,
    Level,
    Paused,
};

struct Game {
    GameState state = GameState::Menu;
};

void OnEvent(Game &, Core::Event &);
void OnUpdate(float deltaTime, Game &game);
void OnRender(Game &game);
} // namespace InGame
