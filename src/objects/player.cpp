#include "../application.h"
#include "player.h"
#include "zombie.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <cassert>
#include <cmath>

Player::Player(const sf::Texture &texture, float _x, float _y)
    : Entity(texture, _x, _y)
{
    setX(_x);
    setY(_y);
    setWidth(texture.getSize().x);
    setHeight(texture.getSize().y);
    setSpeed(200.0f);

    m_sprite.setTexture(texture);
    m_sprite.setPosition(x(), y());
    m_direction = "stop";
    m_originX = width() / 2.0f;
    m_originY = height() / 2.0f;
}

void Player::setDirection(sf::String &_direction)
{
    m_direction = _direction;
}

sf::String Player::direction() const
{
    return m_direction;
}

void Player::update(sf::Time dt)
{
    move(dt);
    calculateAngleToMousePos();

    m_sprite.setOrigin(m_originX, m_originY);
    m_sprite.setPosition(x(), y());
    m_sprite.setRotation(angle());
}

void Player::proccessEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyReleased) {
        m_pressedKeys.erase(event.key.code);
    }
    else if (event.type == sf::Event::KeyPressed) {
        m_pressedKeys.insert(event.key.code);
    }

    bool isLeft = (m_pressedKeys.find(sf::Keyboard::A) != m_pressedKeys.end()) || (m_pressedKeys.find(sf::Keyboard::Left) != m_pressedKeys.end());
    bool isUp   = (m_pressedKeys.find(sf::Keyboard::W) != m_pressedKeys.end()) || (m_pressedKeys.find(sf::Keyboard::Up) != m_pressedKeys.end());
    bool isRight = (m_pressedKeys.find(sf::Keyboard::D) != m_pressedKeys.end()) || (m_pressedKeys.find(sf::Keyboard::Right) != m_pressedKeys.end());
    bool isDown = (m_pressedKeys.find(sf::Keyboard::S) != m_pressedKeys.end()) || (m_pressedKeys.find(sf::Keyboard::Down) != m_pressedKeys.end());

    if (isUp && isLeft) {
        m_direction = "up-left";
    }
    else if (isUp && isRight) {
        m_direction = "up-right";
    }
    else if (isDown && isLeft) {
        m_direction = "down-left";
    }
    else if (isDown && isRight) {
        m_direction = "down-right";
    }
    else if (isUp) {
        m_direction = "up";
    }
    else if (isRight) {
        m_direction = "right";
    }
    else if (isDown) {
        m_direction = "down";
    }
    else if (isLeft) {
        m_direction = "left";
    }
    else {
        m_direction = "stop";
    }
}

void Player::calculateAngleToMousePos()
{
    float angleRadians = std::atan2(Application::mousePos.y - y(), Application::mousePos.x - x());
    float angleDegrees = angleRadians * (180.0f / M_PI);
    setAngle(angleDegrees);
}

bool Player::isCollidedWithZombie(Zombie *zombie, float distance)
{
    if( std::sqrt( std::pow(zombie->x() - x(), 2) + std::pow(zombie->y() - y(), 2)) < distance ) {
        return true;
    }
    return false;
}

void Player::move(sf::Time dt)
{
    if (m_direction == "up-left") {
        moveUp(dt);
        moveLeft(dt);
    }
    else if (m_direction == "up-right") {
        moveUp(dt);
        moveRight(dt);
    }
    else if (m_direction == "down-left") {
        moveDown(dt);
        moveLeft(dt);
    }
    else if (m_direction == "down-right") {
        moveDown(dt);
        moveRight(dt);
    }
    else if (m_direction == "up") {
        moveUp(dt);
    }
    else if (m_direction == "down") {
        moveDown(dt);
    }
    else if (m_direction == "left") {
        moveLeft(dt);
    }
    else if (m_direction == "right") {
        moveRight(dt);
    }
    else if (m_direction == "stop") {

    }
    else {
        std::cout << "Invalid Player movement" << std::endl;
        assert(true);
    }
}

void Player::moveUp(sf::Time dt)
{
    setY(y() - speed() * dt.asSeconds());
    if (y() < m_originY) {
        setY(m_originY);
    }
}

void Player::moveRight(sf::Time dt)
{
    setX(x() + speed() * dt.asSeconds());
    if (x() + m_originX > Application::SCREEN_WIDTH ) {
        setX(Application::SCREEN_WIDTH - m_originX);
    }
}

void Player::moveDown(sf::Time dt)
{
    setY(y() + speed() * dt.asSeconds());
    if (y() + m_originY > Application::SCREEN_HEIGHT ) {
        setY(Application::SCREEN_HEIGHT - m_originY);
    }
}

void Player::moveLeft(sf::Time dt)
{
    setX(x() - speed() * dt.asSeconds());
    if (x() < 0.0f + m_originX) {
        setX(m_originX);
    }
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}
