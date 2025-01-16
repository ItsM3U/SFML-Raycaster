#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <vector>
#include <algorithm>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "Utils.hpp"
#include "Level.hpp"
#include "Player.hpp"

int GetTextureX(int x);
sf::Color GetFogColor(const sf::Color &TextureColor, float Distance);

class Raycaster {
    sf::Uint32 Buffer[Global::Window::Height / Global::Window::Resize][Global::Window::Width / Global::Window::Resize];
    double BufferZ[Global::Window::Width / Global::Window::Resize];

    std::vector<int> SpriteOrder;
    std::vector<double> SpriteDistance;

    sf::Uint8 *BufferPixels;
    sf::Texture BufferTexture;
    sf::Sprite BufferSprite;

    int Width, Height;
public:
    Raycaster();
    ~Raycaster();

    void FloorAndCeilingCast();
    void WallCast();
    void SpriteCast();

    void SortSprites();

    void Raycast();
    void Render(sf::RenderWindow& Window);
};

#endif // RAYCASTER_H
