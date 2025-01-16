#include "Include/Engine.hpp"

Engine::Engine() {
    Window.create(sf::VideoMode(Global::Window::Width, Global::Window::Height), Global::Window::Title, Global::Window::Style);
    Window.setFramerateLimit(Global::Window::FrameLimit);
    Window.setVerticalSyncEnabled(Global::Window::VSync);

    DeltaTime = 0.0f;
    UpdateInterval = 0.0f;
    Focused = true;

    Initialize();
}

Engine::~Engine() = default;

void Engine::Initialize() {
    sf::Image Icon = Resources::Images["Icon"];
    Window.setIcon(Icon.getSize().x, Icon.getSize().y, Icon.getPixelsPtr());

    UI::Initialize();
    GenerateTiles();
    LoadLevel(Global::Path + "Test.lvl");
    GenerateSprites();

    std::cout << "GAME MAP" << std::endl;
    for (auto & y : GameMap) {
        for (char x : y) {
            std::cout << x;
        }
        std::cout << std::endl;
    }
    std::cout << "Sprites: " << Sprites.size() << std::endl;
}

bool Engine::IsRunning() const {
    return Window.isOpen();
}

void Engine::HandleEvents() {
    while (Window.pollEvent(Event)) {
        switch (Event.type) {
        case sf::Event::Closed: Window.close(); break;
        case sf::Event::GainedFocus: Focused = true; break;
        case sf::Event::LostFocus: Focused = false; break;
        case sf::Event::KeyPressed: HandleInput(); break;
        default: break;
        }
    }
}

void Engine::HandleInput() {
    switch (Event.key.code) {
        case sf::Keyboard::Escape: Window.close(); break;
        default: break;
    }
}

void Engine::Update() {
    DeltaTime = Clock.restart().asSeconds();
    m_Player.Update(Focused, DeltaTime);

    if (!Focused) return;

    UpdateInterval -= DeltaTime;

    if (UpdateInterval <= 0) {
        FPS = std::to_string(int(1.0f / DeltaTime));
        UpdateInterval = Global::UI::UpdateInterval;
    }

    UI::TextObjects["Status"]->SetString(
        "Position: (" + Format(m_Player.GetPosition().x) + ", " + Format(m_Player.GetPosition().y) + ")\n" +
        "Direction: (" + Format(m_Player.GetDirection().x) + ", " + Format(m_Player.GetDirection().y) + ")\n" +
        "Plane: (" + Format(m_Player.GetPlane().x) + ", " + Format(m_Player.GetPlane().y) + ")\n" +
        "FPS: " + FPS
    );
}

void Engine::Render() {
    Window.clear();
    m_Raycaster.Render(Window);
    UI::Render(Window);
    Window.display();
}
