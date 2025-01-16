#ifndef GLOBAL_H
#define GLOBAL_H

#include <SFML/Graphics.hpp>

#include <string>
#include <array>

namespace Global {
    const std::string Path = "../Resources/";
    const float PI = 3.141592653589793f;

    namespace Window {
        const int Width = 800;
        const int Height = 600;

        const std::string Title = "Raycaster";
        const int Style = sf::Style::Close;

        const int FrameLimit = 60;
        const bool VSync = true;

        const int Resize = 2;
    }

    namespace Map {
        const int Width = 12;
        const int Height = 12; 

        typedef char Array[Height][Width];

        const int TextureSize = 32;
    }

    namespace Player {
        const float MoveSpeed = 4.5f;
        const float RotateSpeed = 3.75f;

        const float Radius = 0.375f;

        const float RenderDistance = 10.0f;
        const float FogDensity = 0.25f;
    }

    namespace UI {
        const float UpdateInterval = 0.25f;

        const float CellSize = 15.0f;
        const float LineLength = 15.0f;

        namespace Text {
            const int CharacterSize = 20;
            const float OutlineThickness = 2.25f;

            const sf::Color FillColor = sf::Color(sf::Color::White);
            const sf::Color OutlineColor = sf::Color(sf::Color::Black);
        }
    }
}

#endif // GLOBAL_H
