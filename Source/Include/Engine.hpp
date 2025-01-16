#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Global.hpp"
#include "Resources.hpp"
#include "UI.hpp"
#include "Utils.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "Raycaster.hpp"

class Engine {
    sf::RenderWindow Window;
    sf::Event Event;

    sf::Clock Clock;
    float DeltaTime;

    float UpdateInterval;
    bool Focused;

    Raycaster m_Raycaster;
    std::string FPS;

public:
    Engine();
    ~Engine();

    void Initialize();
    bool IsRunning() const;

    void HandleEvents();
    void HandleInput();

    void Update();
    void Render();
};

#endif // ENGINE_H
