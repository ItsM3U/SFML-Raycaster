#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>

#include "Global.hpp"
#include "Level.hpp"

struct Tile;

sf::Vector2f Rotate(sf::Vector2f Vector, float Value);
std::string Format(float Value);
float Clamp(float Number, float Lower, float Upper);

class Sprite {
    sf::Vector2f Position;
    Tile *Reference;
public:
    Sprite(Tile *Reference);
    ~Sprite();

    void SetPosition(float x, float y);
    sf::Vector2f& GetPosition();

    char GetSymbol();
};

extern std::vector<Sprite> Sprites;

#endif // UTILS_H
