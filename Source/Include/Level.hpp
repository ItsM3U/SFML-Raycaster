#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>

#include "Global.hpp"
#include "Utils.hpp"
#include "Player.hpp"

class Player;

extern Global::Map::Array GameMap;

struct Tile {
    std::string Name;
    sf::Image Texture;
    char Symbol;
    bool Collideable;
    bool IsSprite;
};

extern std::vector<Tile> Tiles;

void LoadLevel(const std::string &Path);

char GetTile(int x, int y);
bool CanMove(sf::Vector2f Position, float Radius);

void CreateTile(const std::string &Name, char Symbol, bool Collideable, bool IsSprite);
Tile *GetTileReference(char Symbol);

bool SpriteExists(char Symbol);

void GenerateTiles();
void GenerateSprites();

#endif // LEVEL_H
