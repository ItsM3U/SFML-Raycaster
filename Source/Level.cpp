#include "Include/Level.hpp"

Global::Map::Array GameMap;
std::vector<Tile> Tiles;

void LoadLevel(const std::string &Path) {
    std::ifstream File(Path);
    Tile *Reference;

    if (File.is_open()) {
        for (auto & i : GameMap) {
            std::string Line;
            if (std::getline(File, Line)) {
                for (int j = 0; j < Global::Map::Width; j++) {
                    i[j] = Line[j];
                }
            } else {
                sf::err() << "Error: Insufficient lines in the level file." << std::endl;
                break;
            }
        }
        File.close();
    } else {
        sf::err() << "Error: Unable to open file. Path: " << Path << std::endl;
    }

    for (int y = 0; y < Global::Map::Height; y++) {
        for (int x = 0; x < Global::Map::Width; x++) {
            if (GetTileReference(GetTile(x, y)) != nullptr) {
                Reference = GetTileReference(GetTile(x, y));
            } else {
                if (GetTile(x, y) == '#') {
                    m_Player.SetPosition(float(x) + 0.5f, float(y) + 0.5f);
                    GameMap[y][x] = '.';
                }
                Reference = GetTileReference('.');
            }
        }
    }               
}

char GetTile(int x, int y) {
    return GameMap[y][x];
}

bool CanMove(sf::Vector2f Position, float Radius) {
    sf::Vector2f Size(Radius, Radius);
    sf::Vector2i UpperLeft(Position - Size / 2.0f);
    sf::Vector2i LowerRight(Position + Size / 2.0f);

    for (int y = UpperLeft.y; y <= LowerRight.y; y++) {
        for (int x = UpperLeft.x; x <= LowerRight.x; x++) {
            if (GetTileReference(GetTile(x, y))->Collideable) return false;
        }
    }

    if (Position.x >= 0 && Position.x <= Global::Map::Width && Position.y >= 0 && Position.y <= Global::Map::Width) return true;

    return false;
}

void CreateTile(const std::string &Name, char Symbol, bool Collideable, bool IsSprite) {
    Tile Reference;
    Reference.Name = Name;
    Reference.Symbol = Symbol;
    Reference.Collideable = Collideable;
    Reference.IsSprite = IsSprite;

    sf::Image Image;
    Image.loadFromFile(Global::Path + (IsSprite ? "Images/Textures/Sprites/" : "Images/Textures/") + Name + ".png");
    Reference.Texture = Image;

    Tiles.push_back(Reference);
}

Tile *GetTileReference(char Symbol) {
    for (auto &Tile : Tiles) {
        if (Tile.Symbol == Symbol) {
            return &Tile;
        }
    }
    return nullptr;
}

bool SpriteExists(char Symbol) {
    std::vector<char> SpritesVector = {'T', 'P'}; // Add all of the sprite symbols here.
    for (char & x : SpritesVector) {
        if (x == Symbol) return true;
    }
    return false;
}

void GenerateTiles() {
    Tile Empty;
    Empty.Name = " ";
    Empty.Symbol = '.';
    Empty.Collideable = false;
    Tiles.push_back(Empty);

    // Name, Symbol, Collideable, IsSprite

    CreateTile("Concrete", 'c', true, false);
    CreateTile("Gray", 'g', true, false);
    CreateTile("Planks", 'p', true, false);
    CreateTile("Red", 'r', true, false);
    CreateTile("Portrait", 't', true, false);

    CreateTile("Table", 'T', true, true);
    CreateTile("Plant", 'P', false, true);
}

void GenerateSprites() {
    for (int y = 0; y < Global::Map::Height; y++) {
        for (int x = 0; x < Global::Map::Width; x++){
            Tile* Reference = GetTileReference(GetTile(x, y));
            if (Reference != nullptr) {
                if (Reference->IsSprite && SpriteExists(Reference->Symbol)) {
                    Sprite Object(Reference);
                    Object.SetPosition(float(x) + 0.5f, float(y) + 0.5f);
                    Sprites.push_back(Object);
                }
            } else {
                sf::err() << "nullptr reference found at (" << x << ", " << y << ")" << std::endl;
            }
        }
    }
}
