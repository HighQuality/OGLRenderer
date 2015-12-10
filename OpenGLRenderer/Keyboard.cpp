#include "Keyboard.h"

Keyboard::Keyboard()
{
}

bool Keyboard::IsKeyPressed(SDL_Keycode code) const
{
	return true;
}
bool Keyboard::IsKeyDown(SDL_Keycode code) const
{
	return true;
}
bool Keyboard::IsKeyReleased(SDL_Keycode code) const
{
	return true;
}

void Keyboard::KeyDown(SDL_Keycode code)
{
}
void Keyboard::KeyUp(SDL_Keycode code)
{
}

Keyboard::~Keyboard()
{

}
