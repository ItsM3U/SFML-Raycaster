#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <memory>

#include "Global.hpp"
#include "Resources.hpp"
#include "Level.hpp"
#include "Player.hpp"

namespace UI {
    class BaseText {
        sf::Text Text;
    public:
        BaseText(const std::string &Name, sf::Font &Font, const sf::Vector2f &Position, int CharacterSize, float OutlineThickness, const sf::Color &FillColor, const sf::Color &OutlineColor);
        ~BaseText();

        void SetString(const std::string &String);
        void Render(sf::RenderWindow &Window);
    };

    extern std::map<std::string, std::shared_ptr<BaseText>> TextObjects;

    void Initialize();

    void RenderTextObjects(sf::RenderWindow &Window);
    void RenderMinimap(sf::RenderWindow &Window);

    void Render(sf::RenderWindow &Window);
}

#endif // UI_H
