#pragma once

#include <SDL.h>

class Keyboard
{
public:

	Keyboard();

	bool IsKeyPressed(SDL_Keycode code) const;
	bool IsKeyDown(SDL_Keycode code) const;
	bool IsKeyReleased(SDL_Keycode code) const;

	void KeyDown(SDL_Keycode code);
	void KeyUp(SDL_Keycode code);

	~Keyboard();
private:
};
