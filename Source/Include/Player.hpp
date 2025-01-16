#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "Utils.hpp"
#include "Level.hpp"

class Player {
    sf::Vector2f Position;
    sf::Vector2f Direction;
    sf::Vector2f Plane;
    float Size;
public:
    Player();
    ~Player();

    void SetPosition(float x, float y);
    sf::Vector2f& GetPosition();

    void SetDirection(float x, float y);
    sf::Vector2f& GetDirection();

    void SetPlane(float x, float y);
    sf::Vector2f& GetPlane();

    void SetSize(float Radius);
    float GetSize();

    void Update(bool Focused, float DeltaTime);
};

extern Player m_Player;

#endif // PLAYER_H
