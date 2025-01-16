#include "Include/UI.hpp"

UI::BaseText::BaseText(const std::string &Name, sf::Font &Font, const sf::Vector2f &Position, int CharacterSize, float OutlineThickness, const sf::Color &FillColor, const sf::Color &OutlineColor) {
    this->Text.setFont(Font);
    this->Text.setPosition(Position);
    this->Text.setCharacterSize(CharacterSize);
    this->Text.setOutlineThickness(OutlineThickness);
    this->Text.setFillColor(FillColor);
    this->Text.setOutlineColor(OutlineColor);

    TextObjects[Name] = std::make_shared<BaseText>(*this); 
}

UI::BaseText::~BaseText() = default;

void UI::BaseText::SetString(const std::string &String) {
    this->Text.setString(String);
}

void UI::BaseText::Render(sf::RenderWindow &Window) {
    Window.draw(this->Text);
}

namespace UI {
    std::map<std::string, std::shared_ptr<BaseText>> TextObjects;

    void Initialize() {
        TextObjects["Status"] = std::make_shared<BaseText>(
            "Status",
            Resources::Fonts["RetroFont"],
            sf::Vector2f(10.0f, 10.0f),
            Global::UI::Text::CharacterSize,
            Global::UI::Text::OutlineThickness,
            Global::UI::Text::FillColor,
            Global::UI::Text::OutlineColor
        ); 
    }

    void RenderTextObjects(sf::RenderWindow& Window) {
        for (const auto& Pair : TextObjects) {
            Pair.second->Render(Window);
        }
    }

    void RenderMinimap(sf::RenderWindow &Window) {
        sf::RectangleShape Cell(sf::Vector2f(Global::UI::CellSize, Global::UI::CellSize));
        sf::RectangleShape Point(sf::Vector2f(6.0f, 6.0f));

        for (int y = 0; y < Global::Map::Height; y++) {
            for (int x = 0; x < Global::Map::Width; x++) {
                Cell.setPosition(sf::Vector2f(
                    float(Global::Window::Width - (Global::UI::CellSize * Global::Map::Width) + float(x) * Global::UI::CellSize) - Global::UI::CellSize,
                    float(y) * Global::UI::CellSize + Global::UI::CellSize)
                );

                if (GetTile(x, y) == '.') {
                    Cell.setFillColor(sf::Color(50, 50, 50, 175));
                } else if (islower(GetTile(x, y))) {
                    Cell.setFillColor(sf::Color(40, 40, 40, 175));
                } else {
                    Cell.setFillColor(sf::Color(30, 30, 30, 175));
                }

                Window.draw(Cell);
            }
        }

        Point.setFillColor(sf::Color(255, 255, 255, 175));
        Point.setPosition(sf::Vector2f(
            float(Global::Window::Width - (Global::UI::CellSize * Global::Map::Width) + float(m_Player.GetPosition().x) * Global::UI::CellSize) - Global::UI::CellSize - 2.75f,
            float(m_Player.GetPosition().y) * Global::UI::CellSize + Global::UI::CellSize - 2.75f)
        );

        float Radians = std::atan2(m_Player.GetDirection().y, m_Player.GetDirection().x);
        if (Radians < 0) Radians += 2 * Global::PI;
        float Degrees = Radians * (180.0f / Global::PI) - 90.0f;

        

        sf::VertexArray DirectionLine(sf::Lines, 2);
        sf::Vector2f PlayerCenter(float(Global::Window::Width - (Global::UI::CellSize * Global::Map::Width) + m_Player.GetPosition().x * Global::UI::CellSize) - Global::UI::CellSize, m_Player.GetPosition().y * Global::UI::CellSize + Global::UI::CellSize);

        sf::Vector2f Direction = m_Player.GetDirection();
        float Length = std::sqrt(Direction.x * Direction.x + Direction.y * Direction.y);
        if (Length != 0.0f) {
            Direction.x /= Length;
            Direction.y /= Length;
        }

        sf::Vector2f OffsetStart(PlayerCenter.x + Direction.x * 4.75f, PlayerCenter.y + Direction.y * 4.75f);
        sf::Vector2f EndPoint(OffsetStart.x + Direction.x * (Global::UI::LineLength - 4.75f), OffsetStart.y + Direction.y * (Global::UI::LineLength - 4.75f));

        DirectionLine[0].position = OffsetStart;
        DirectionLine[0].color = sf::Color(255, 255, 255, 150);
        DirectionLine[1].position = EndPoint;
        DirectionLine[1].color = sf::Color(255, 255, 255, 150);

        Window.draw(DirectionLine);
        Window.draw(Point);
    }

    void Render(sf::RenderWindow &Window) {
        RenderTextObjects(Window);
        RenderMinimap(Window);
    }
}
