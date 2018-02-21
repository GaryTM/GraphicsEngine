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
	//The EventHandler allows for events to be processed using one simple call
	void EventHandler(vector<SDL_Event> events);
	//isDown is used to check if a key is currently being held down by the user
	bool isDown(SDL_Keycode key) const;
	//isButDown is used to check if a mouse button is currently being held down by the user
	bool isButDown(Uint8 button) const;
	//wasDown is used to check if a key was being held down by the user
	bool wasDown(SDL_Keycode key) const;
	//wasDown is used to check if a mouse button was being held down by the user
	bool wasButDown(Uint8 button) const;
	//The following just take a combination of the above which allows the checks and code to be more concise
	bool isJustPressed(SDL_Keycode key) const { return isDown(key) && !wasDown(key); }
	bool isButJustPressed(Uint8 button) const { return isButDown(button) && !wasButDown(button); }

	bool isJustReleased(SDL_Keycode key) const { return !isDown(key) && wasDown(key); }
	bool isButJustReleased(Uint8 button) const { return !isButDown(button) && wasButDown(button); }

	vec2 GetMousePosition() const { return _mousePosition; }

private:
	//Lists to hold the currentkeys and previously used keys
	list<SDL_Keycode> _currentKeys;
	list<SDL_Keycode> _previousKeys;
	//Same as above, but for mouse buttons
	list<Uint8> _currentButton;
	list<Uint8> _previousButton;

	vec2 _mousePosition;
	vec2 _previousMousePosition;
};
