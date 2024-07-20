#ifndef RESOURCE_IDENTIFIERS_H
#define RESOURCE_IDENTIFIERS_H
#include <SFML/Audio/SoundBuffer.hpp>
// Forward declaration of SFML classes
namespace sf
{
    class Texture;
    class Font;
    class Shader;
    class SoundBuffer;
}

namespace Textures
{
    enum ID
    {
        SFML_LOGO = 0,
        AvatorLogo,
        Buttons,
        Player,
        Background,
        Bullet,
        Zombie,
        Crosshair,
        COUNT
    };
}

namespace Fonts
{
    enum ID
    {
        Main,
    };
}

namespace SoundEffect
{
    enum ID
    {
        Shoot, Pop
    };
}

namespace Music
{
    enum ID
    {
        MenuTheme,
    };
}
// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	        TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			        FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;

#endif // RESOURCE_IDENTIFIERS_H
