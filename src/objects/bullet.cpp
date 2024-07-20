#include "bullet.h"
#include "../application.h"
#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>
#include "zombie.h"
#include <iostream>

Bullet::Bullet(const sf::Texture &texture, float _angle, float _x, float _y)
    : Entity(texture, _x, _y)
{
    setAngle(_angle);
    setX(_x);
    setY(_y);
    setSpeed(300.0f);
    setWidth(texture.getSize().x);
    setHeight(texture.getSize().y);

    m_sprite.setTexture(texture);
    m_sprite.setPosition(x(), y());

    m_originX = width() / 2.0f;
    m_originY = height() / 2.0f;
    m_isDead = false;
}

void Bullet::update(sf::Time dt)
{
    float radiansValue = angle() * (M_PI / 180);
    setX(x() + cos(radiansValue) * speed() * dt.asSeconds() );
    setY(y() + sin(radiansValue) * speed() * dt.asSeconds() );

    if (y() < m_originY) {
        m_isDead = true;
    }
    if (x() + m_originX > Application::SCREEN_WIDTH ) {
        m_isDead = true;
    }
    if (y() + m_originY > Application::SCREEN_HEIGHT ) {
        m_isDead = true;
    }
    if (x() < m_originX) {
        m_isDead = true;
    }

    m_sprite.setOrigin(m_originX, m_originY);
    m_sprite.setPosition(x(), y());
    m_sprite.setRotation(angle());
}

void Bullet::setDead(bool val)
{
    m_isDead = val;
}

bool Bullet::isDead() const
{
    return m_isDead;
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}

bool Bullet::isCollidedWithZombie(Zombie *zombie, float distance)
{
    if( std::sqrt( std::pow(zombie->x() - x(), 2) + std::pow(zombie->y() - y(), 2)) < distance ) {
        zombie->setDead(true);
        setDead(true);
        return true;
    }
    return false;
}
