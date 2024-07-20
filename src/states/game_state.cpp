#include "game_state.h"
#include "../utils/resource_holder.h"
#include "../application.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

GameState::GameState(StateStack& stack, Context context)
    : State(stack, context), mStartZombieSpawnValue(1.0f), mCurrentZombieSpawnValue(mStartZombieSpawnValue),
    mSpawnZombieTime(sf::Time::Zero), mScore(0u)
{
    mTextures = getContext().textures;
    mBgSprite.setTexture(mTextures->get(Textures::Background));
    mTextures->get(Textures::Player).setSmooth(true);
    mCrosshairSprite.setTexture(mTextures->get(Textures::Crosshair));
    mCrosshairSprite.setOrigin(mCrosshairSprite.getLocalBounds().width / 2.0f, mCrosshairSprite.getLocalBounds().height / 2.0f);

    mPlayer = new Player(mTextures->get(Textures::Player), Application::HALF_WIDTH, Application::HALF_HEIGHT);
    srand(time(0));

    mScoreText.setFont(getContext().fonts->get(Fonts::Main));
    mScoreText.setCharacterSize(38);
    mScoreText.setFillColor(sf::Color::Red);

    mShootSound.setBuffer(getContext().sounds->get(SoundEffect::Shoot));
    mShootSound.setVolume(75.0f);
    mDeadSound.setBuffer(getContext().sounds->get(SoundEffect::Pop));
    mDeadSound.setVolume(100.0f);
}

void GameState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.clear();
    window.draw(mBgSprite);
    mPlayer->draw(window, sf::RenderStates());
    drawBullets(window);
    drawZombies(window);
    drawScore(window);
    drawCrosshair(window);
}

bool GameState::update(sf::Time dt)
{
    mPlayer->update(dt);
    updateCrosshair(dt);
    updateBullets(dt);
    updateZombies(dt);
    spawnZombie(dt);
    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyReleased)
    {       
        if(event.key.code == sf::Keyboard::Backspace)
        {
            requestStackPop();
            requestStackPush(States::Title);
        }
        else if (event.key.code == sf::Keyboard::Space) {
            makeShot();
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            makeShot();
        }
    }
    mPlayer->proccessEvent(event);

    return true;
}

void GameState::spawnZombie(sf::Time dt)
{
    mSpawnZombieTime += dt;
    if (mSpawnZombieTime > sf::seconds(mCurrentZombieSpawnValue)) {
        int side = std::rand() % 4;
        int hRandomVal = rand() % Application::SCREEN_HEIGHT;
        int wRandomVal = rand() % Application::SCREEN_WIDTH;
        switch (side) {
        case 0: // left
            mZombies.push_back(Zombie(mTextures->get(Textures::Zombie), -50, hRandomVal));
            break;
        case 1: // right
            mZombies.push_back(Zombie(mTextures->get(Textures::Zombie), Application::SCREEN_WIDTH + 50, hRandomVal));
            break;
        case 2: // up
            mZombies.push_back(Zombie(mTextures->get(Textures::Zombie), wRandomVal, -50));
            break;
        case 3: // down
            mZombies.push_back(Zombie(mTextures->get(Textures::Zombie), wRandomVal, Application::SCREEN_HEIGHT + 50));
            break;
        }

        mCurrentZombieSpawnValue = mStartZombieSpawnValue - mScore * 0.01f;
        if (mCurrentZombieSpawnValue < 0.1f) {
            mCurrentZombieSpawnValue = 0.1f;
        }
        mSpawnZombieTime = sf::Time::Zero;
    }
}

void GameState::makeShot()
{
    mBulets.push_back(Bullet(mTextures->get(Textures::Bullet), mPlayer->angle(), mPlayer->x(), mPlayer->y()));
    mShootSound.play();
}

void GameState::updateBullets(sf::Time dt)
{
    for (int i = mBulets.size() - 1; i >= 0; --i) {
        if (mBulets[i].isDead()) {
            mBulets.erase(mBulets.begin() + i);
        }
        else {
            for (int j = mZombies.size() - 1; j >= 0 ; --j) {
                if (mBulets[i].isCollidedWithZombie(&mZombies[j], 15.0f) ) {
                    mDeadSound.play();
                    addScore(1);
                }
            }
        }
    }

    for (int i = mBulets.size() - 1; i >= 0 ; --i) {
        mBulets[i].update(dt);
    }
}

void GameState::updateZombies(sf::Time dt)
{
    for (int i = mZombies.size() - 1; i >= 0; --i) {
        mZombies[i].update(dt, mPlayer);
        if(mPlayer->isCollidedWithZombie(&mZombies[i], 20.0)) {
            gameOver();
            break;
        }
        if (mZombies[i].isDead()) {
            mZombies.erase(mZombies.begin() + i);
        }
    }
}

void GameState::updateCrosshair(sf::Time dt)
{
    mCrosshairSprite.setPosition(Application::mousePos.x, Application::mousePos.y);
}

void GameState::drawBullets(sf::RenderWindow &window)
{
    for (int i = mBulets.size() - 1; i >= 0; --i) {
        mBulets[i].draw(window, sf::RenderStates());
    }
}

void GameState::drawZombies(sf::RenderWindow &window)
{
    for (int i = mZombies.size() - 1; i >= 0; --i) {
        mZombies[i].draw(window, sf::RenderStates());
    }
}

void GameState::drawScore(sf::RenderWindow &window)
{
    sf::String scoreString = sf::String("Score :") + sf::String(std::to_string(mScore));
    mScoreText.setString(scoreString);
    mScoreText.setOrigin( mScoreText.getLocalBounds().width + 10, 0);
    mScoreText.setPosition(Application::SCREEN_WIDTH, 0);
    window.draw(mScoreText);
}

void GameState::drawCrosshair(sf::RenderWindow &window)
{
    window.draw(mCrosshairSprite);
}

void GameState::addScore(unsigned int val)
{
    mScore += val;
}

void GameState::gameOver()
{
    mDeadSound.play();
    mBulets.clear();
    mZombies.clear();
    mPlayer->setX(Application::HALF_WIDTH);
    mPlayer->setY(Application::HALF_HEIGHT);
    mScore = 0;
    mCurrentZombieSpawnValue = mStartZombieSpawnValue;
}
