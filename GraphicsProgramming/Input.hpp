#pragma once
#include <SDL\SDL.h>
#include <glm/glm.hpp>
#include <vector>
#include <list>

using namespace std;
using namespace glm;

class Input
{
public:
	void EventHandler(vector<SDL_Event> events);

	bool isDown(SDL_Keycode key) const;
	bool isButDown(Uint8 button) const;

	bool wasDown(SDL_Keycode key) const;
	bool wasButDown(Uint8 button) const;

	bool isJustPressed(SDL_Keycode key) const { return isDown(key) && !wasDown(key); }
	bool isButJustPressed(Uint8 button) const { return isButDown(button) && !wasButDown(button); }

	bool isJustReleased(SDL_Keycode key) const { return !isDown(key) && wasDown(key); }
	bool isButJustReleased(Uint8 button) const { return !isButDown(button) && wasButDown(button); }

	vec2 GetMousePos() const { return _mousePosition; }

private:
	list<SDL_Keycode> _currentKeys;
	list<SDL_Keycode> _previousKeys;

	list<Uint8> _currentButton;
	list<Uint8> _previousButton;

	vec2 _mousePosition;
	vec2 _previousMousePosition;
};
