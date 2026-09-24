#include "Game.h"

namespace game {

void OnEvent(Game &game, core::Event &event) {
}

void OnUpdate(float deltaTime, Game &game) {
    switch (game.state) {
    case GameState::Menu:
        break;

    case GameState::Level:
        break;
    case GameState::Paused:
        break;
    }
}

void OnRender(Game &game) {
}

} // namespace game
