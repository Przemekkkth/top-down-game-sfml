#include "application.h"

#include "const/state_identifiers.h"
#include "states/state.h"
#include "states/game_state.h"
#include "states/title_state.h"
#include <iostream>


const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);
const int Application::SCREEN_WIDTH  = 800;
const int Application::SCREEN_HEIGHT = 600;
const int Application::HALF_WIDTH    = SCREEN_WIDTH/2;
const int Application::HALF_HEIGHT   = SCREEN_HEIGHT/2;
sf::Vector2i Application::mousePos   = sf::Vector2i();

Application::Application()
 : mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Top Down Shooter SFML", sf::Style::Close)
, mTextures()
, mStateStack(State::Context(mWindow, mTextures, mFonts, mSounds))
{
    mWindow.setKeyRepeatEnabled(false);
    mWindow.setMouseCursorVisible(false);
    registerStates();
    mStateStack.pushState(States::Title);
    mTextures.load(Textures::SFML_LOGO,  "assets/sprites/sfml-logo-small.png");
    mTextures.load(Textures::AvatorLogo, "assets/sprites/avatar.png");
    mTextures.load(Textures::Player, "assets/sprites/player.png");
    mTextures.load(Textures::Background, "assets/sprites/background.png");
    mTextures.load(Textures::Bullet, "assets/sprites/bullet.png");
    mTextures.load(Textures::Zombie, "assets/sprites/zombie.png");
    mTextures.load(Textures::Crosshair, "assets/sprites/crosshair.png");

    mFonts.load(Fonts::Main, "assets/fonts/juniory.ttf");

    mSounds.load(SoundEffect::Shoot, "assets/sounds/pistol.wav");
    mSounds.load(SoundEffect::Pop,   "assets/sounds/pop1.wav");
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);

            // Check inside this loop, because stack might be empty before update() call
            if (mStateStack.isEmpty())
                mWindow.close();
        }

        render();
    }
}

void Application::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);

        if (event.type == sf::Event::Closed)
            mWindow.close();
        if (event.type == sf::Event::KeyReleased)
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                mWindow.close();
            }
            //Uncomment if you want to make screenshots
                if(event.key.code == sf::Keyboard::O)
                {
                    static int index = 0;
                    sf::Texture texture;
                    texture.create(mWindow.getSize().x, mWindow.getSize().y);
                    texture.update(mWindow);
                    std::string filename = "app" + std::to_string(index) + ".png";
                    if (texture.copyToImage().saveToFile(filename))
                    {
                        index++;
                    }
                }
        }
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
    mousePos = sf::Mouse::getPosition(mWindow);
}

void Application::render()
{
    mWindow.clear();
    mStateStack.draw();
    mWindow.setView(mWindow.getDefaultView());
    mWindow.display();
}

void Application::registerStates()
{
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<GameState>(States::Game);
}
