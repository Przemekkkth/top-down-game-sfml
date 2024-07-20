#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include "entity.h"

class Player;

class Zombie : public Entity {
public:
    Zombie(const sf::Texture& texture, float _x = 0.0f, float _y = 0.0f);
    void update(sf::Time dt, Player* player);
    void setDead(bool val);
    bool isDead() const;
    void calculateAngleToPlayer(Player* player);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
    void move(sf::Time dt);
    sf::Sprite m_sprite;
    float m_originX, m_originY;
    bool  m_isDead;
};


#endif
