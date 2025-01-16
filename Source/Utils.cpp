#include "Include/Utils.hpp"

sf::Vector2f Rotate(sf::Vector2f Vector, float Value) {
    return {Vector.x * cos(Value) - Vector.y * sin(Value), Vector.x * sin(Value) + Vector.y * cos(Value)};
}

std::string Format(float Value) {
    std::ostringstream Stream;
    Stream << std::fixed << std::setprecision(2) << Value;
    return Stream.str();
}

float Clamp(float Number, float Lower, float Upper) {
    return std::max(Lower, std::min(Number, Upper));
}

std::vector<Sprite> Sprites;

Sprite::Sprite(Tile *Reference) {
    this->Reference = Reference;
}

Sprite::~Sprite() = default;

void Sprite::SetPosition(float x, float y) {
    this->Position = sf::Vector2f(x, y);
}

sf::Vector2f& Sprite::GetPosition() {
    return this->Position;
}

char Sprite::GetSymbol() {
    return this->Reference->Symbol;
}
