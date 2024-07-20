#ifndef BULLET_H
#define BULLET_H
#include "entity.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Zombie;
class Bullet : public Entity {
public:
    Bullet(const sf::Texture& texture, float _angle = 0.0f, float _x = 0.0f, float _y = 0.0f);
    void update(sf::Time dt);
    void setDead(bool val);
    bool isDead() const;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    bool isCollidedWithZombie(Zombie* zombie, float distance);
private:
    sf::Sprite m_sprite;
    float m_originX, m_originY;
    bool  m_isDead;
};


#endif
