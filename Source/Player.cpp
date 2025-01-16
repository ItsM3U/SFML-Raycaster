#include "Include/Player.hpp"

Player m_Player;

Player::Player() {
    SetDirection(-1.0f, 0.0f);
    SetPlane(0.0f, -0.66f);
    SetSize(Global::Player::Radius);
}

Player::~Player() = default;

void Player::SetPosition(float x, float y) {
    Position = sf::Vector2f(x, y);
}

sf::Vector2f& Player::GetPosition() {
    return Position;
}

void Player::SetDirection(float x, float y) {
    Direction = sf::Vector2f(x, y);
}

sf::Vector2f& Player::GetDirection() {
    return Direction;
}

void Player::SetPlane(float x, float y) {
    Plane = sf::Vector2f(x, y);
}

sf::Vector2f& Player::GetPlane() {
    return Plane;
}

void Player::SetSize(float Radius) {
    Size = Radius;
}

float Player::GetSize() {
    return Size;
}

void Player::Update(bool Focused, float DeltaTime) {
    sf::Vector2f MoveVector(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && Focused) MoveVector += Direction;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && Focused) MoveVector -= Direction;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && Focused) MoveVector += Rotate(Direction, -Global::PI / 2);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Focused) MoveVector += Rotate(Direction, Global::PI / 2);

    float MoveLength = std::sqrt(MoveVector.x * MoveVector.x + MoveVector.y * MoveVector.y);
    if (MoveLength > 0) {
        MoveVector = (1.0f / MoveLength) * MoveVector;
        MoveVector *= Global::Player::MoveSpeed * DeltaTime;
    }

    sf::Vector2f SlideX(Position.x + MoveVector.x, Position.y);
    sf::Vector2f SlideY(Position.x, Position.y + MoveVector.y);

    if (CanMove(SlideX, Size)) Position.x = SlideX.x;
    if (CanMove(SlideY, Size)) Position.y = SlideY.y;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && Focused) {
        float Rotation = Global::Player::RotateSpeed * -1.0f * DeltaTime;
        Direction = Rotate(Direction, Rotation);
        Plane = Rotate(Plane, Rotation);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && Focused) {
        float Rotation = Global::Player::RotateSpeed * 1.0f * DeltaTime;
        Direction = Rotate(Direction, Rotation);
        Plane = Rotate(Plane, Rotation);
    }
}
