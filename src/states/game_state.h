#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "state.h"
#include "../objects/player.h"
#include "../objects/bullet.h"
#include "../objects/zombie.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Sound.hpp>
#include <vector>


class GameState : public State
{
    public:
                            GameState(StateStack& stack, Context context);

        virtual void		draw();
        virtual bool		update(sf::Time dt);
        virtual bool		handleEvent(const sf::Event& event);
    private:
        void                spawnZombie(sf::Time dt);
        void                makeShot();
        void                updateBullets(sf::Time dt);
        void                updateZombies(sf::Time dt);
        void                updateCrosshair(sf::Time dt);
        void                drawBullets(sf::RenderWindow&  window);
        void                drawZombies(sf::RenderWindow& window);
        void                drawScore(sf::RenderWindow& window);
        void                drawCrosshair(sf::RenderWindow& window);
        void                addScore(unsigned int val);
        void                gameOver();

        TextureHolder*      mTextures;
        sf::Sprite          mBgSprite;
        sf::Text            mScoreText;
        sf::Sprite          mCrosshairSprite;
        Player*             mPlayer;
        std::vector<Bullet> mBulets;
        std::vector<Zombie> mZombies;
        const float         mStartZombieSpawnValue;
        float               mCurrentZombieSpawnValue;
        sf::Time            mSpawnZombieTime;
        unsigned int        mScore;
        sf::Sound           mShootSound, mDeadSound;
};
#endif // GAME_STATE_H
