#include "entity.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

Entity::Entity(const sf::Texture &texture, const float _x, const float _y)
{
    m_x = m_y = m_angle = 0.0f;
    m_width = m_height = 0;
    m_texture = texture;
}

void Entity::setX(const float _x)
{
    m_x = _x;
}

void Entity::setY(const float _y)
{
    m_y = _y;
}

void Entity::setAngle(const float _angle)
{
    m_angle = _angle;
}

void Entity::setWidth(const int _width)
{
    m_width = _width;
}

void Entity::setHeight(const int _height)
{
    m_height = _height;
}

void Entity::setSpeed(const float _speed)
{
    m_speed = _speed;
}

float Entity::x() const
{
    return m_x;
}

float Entity::y() const
{
    return m_y;
}

float Entity::angle() const
{
    return m_angle;
}

float Entity::speed() const
{
    return m_speed;
}

int Entity::width() const
{
    return m_width;
}

int Entity::height() const
{
    return m_height;
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape rectangle(sf::Vector2f(m_width, m_height));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setPosition(m_x, m_y);
    target.draw(rectangle);
}
