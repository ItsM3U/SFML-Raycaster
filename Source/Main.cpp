#include <SFML/Graphics.hpp>

#include "Include/Global.hpp"
#include "Include/Resources.hpp"
#include "Include/Engine.hpp"

int main() {
    Resources::Load();
    Engine Game;

    while (Game.IsRunning()) {
        Game.HandleEvents();
        Game.Update();
        Game.Render();
    }

    return 0;
}
