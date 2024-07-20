#include "zombie.h"
#include "player.h"
#include <SFML/Graphics/RenderWindow.hpp>

Zombie::Zombie(const sf::Texture &texture, float _x, float _y)
    : Entity(texture, _x, _y)
{
    setX(_x);
    setY(_y);
    setWidth(texture.getSize().x);
    setHeight(texture.getSize().y);
    setSpeed(200.0f);

    m_sprite.setTexture(texture);
    m_sprite.setPosition(x(), y());
    m_originX = width() / 2.0f;
    m_originY = height() / 2.0f;
}

void Zombie::update(sf::Time dt, Player *player)
{
    calculateAngleToPlayer(player);
    move(dt);

    m_sprite.setOrigin(m_originX, m_originY);
    m_sprite.setPosition(x(), y());
    m_sprite.setRotation(angle());
}

void Zombie::setDead(bool val)
{
    m_isDead = val;
}

bool Zombie::isDead() const
{
    return m_isDead;
}

void Zombie::calculateAngleToPlayer(Player *player)
{
    float angleRadians = std::atan2(player->y() - y(), player->x() - x());
    float angleDegrees = angleRadians * (180.0f / M_PI);
    setAngle(angleDegrees);
}

void Zombie::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}

void Zombie::move(sf::Time dt)
{
    float radiansValue = angle() * (M_PI / 180);
    setX(x() + cos(radiansValue) * speed() * dt.asSeconds() );
    setY(y() + sin(radiansValue) * speed() * dt.asSeconds() );
}
