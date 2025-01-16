#ifndef RESOURCES_H
#define RESOURCES_H

#include <SFML/Graphics.hpp>
#include <map>

#include "Global.hpp"

namespace Resources {
    extern std::map<std::string, sf::Font> Fonts;
    extern std::map<std::string, sf::Image> Images;
    extern std::map<std::string, sf::Texture> Textures;

    void LoadFont(const std::string &FilePath, const std::string &Name, bool Smooth);
    void LoadImage(const std::string &FilePath, const std::string &Name);
    void LoadTexture(const std::string &FilePath, const std::string &Name, bool Smooth);

    void Load();
}

#endif // RESOURCES_H
