#include "Include/Resources.hpp"

namespace Resources {
    std::map<std::string, sf::Font> Fonts;
    std::map<std::string, sf::Image> Images;
    std::map<std::string, sf::Texture> Textures;
}

void Resources::LoadFont(const std::string &FilePath, const std::string &Name, bool Smooth) {
    sf::Font Font;
    if (!Font.loadFromFile(FilePath))
        sf::err() << "Cannot load font: " + Name << std::endl;
    Fonts[Name] = Font;
    Fonts[Name].setSmooth(Smooth);
}

void Resources::LoadImage(const std::string &FilePath, const std::string &Name) {
    sf::Image Image;
    if (!Image.loadFromFile(FilePath))
        sf::err() << "Cannot load Image: " + Name << std::endl;
    Images[Name] = Image;
}

void Resources::LoadTexture(const std::string &FilePath, const std::string &Name, bool Smooth) {
    sf::Texture Texture;
    if (!Texture.loadFromFile(FilePath))
        sf::err() << "Cannot load Texture: " + Name << std::endl;
    Textures[Name] = Texture;
    Textures[Name].setSmooth(Smooth);
}

void Resources::Load() {
    LoadFont(Global::Path + "Fonts/RetroFont.ttf", "RetroFont", false);
    LoadImage(Global::Path + "Images/Icon.png", "Icon");
}
