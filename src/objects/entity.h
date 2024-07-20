#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>

class Entity : public sf::Drawable
{
public:
    Entity(const sf::Texture& texture, const float _x, const float _y);
    void setX(const float _x);
    void setY(const float _y);
    void setAngle(const float _angle);
    void setWidth(const int _width);
    void setHeight(const int _height);
    void setSpeed(const float _speed);

    float x() const;
    float y() const;
    float angle() const;
    float speed() const;
    int width() const;
    int height() const;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
    float m_x, m_y, m_angle, m_speed;
    int m_width, m_height;
    sf::Texture m_texture;
};

#endif
