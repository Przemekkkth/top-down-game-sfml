#include "state.h"
#include "state_stack.h"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder &fonts, SoundBufferHolder &sounds)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, sounds(&sounds)
{
}

State::State(StateStack& stack, Context context)
: mStack(&stack)
, mContext(context)
{

}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
    mStack->pushState(stateID);
}

void State::requestStackPop()
{
    mStack->popState();
}

void State::requestStateClear()
{
    mStack->clearStates();
}

State::Context State::getContext() const
{
    return mContext;
}
