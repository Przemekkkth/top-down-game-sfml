#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <set>

class Zombie;
class Player : public Entity
{
public:
    Player(const sf::Texture& texture, float _x = 0.0f, float _y = 0.0f);
    void setDirection(sf::String& _direction);
    sf::String direction() const;
    void update(sf::Time dt);
    void proccessEvent(const sf::Event& event);
    void calculateAngleToMousePos();
    bool isCollidedWithZombie(Zombie* zombie, float distance);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
    void move(sf::Time dt);
    void moveUp(sf::Time dt);
    void moveRight(sf::Time dt);
    void moveDown(sf::Time dt);
    void moveLeft(sf::Time dt);
    sf::Sprite m_sprite;
    sf::String m_direction;
    float m_originX, m_originY;

    std::set<int> m_pressedKeys;
};

#endif
