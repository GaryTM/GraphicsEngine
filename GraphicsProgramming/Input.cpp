#include "Input.hpp"

	void Input::EventHandler(vector<SDL_Event> events)
	{
		_previousKeys = _currentKeys;
		_previousButton = _currentButton;

		for (auto e : events)
		{
			switch (e.type)
			{
			case SDL_KEYDOWN:
				_currentKeys.push_back(e.key.keysym.sym);
				break;

			case SDL_KEYUP:
				_currentKeys.remove(e.key.keysym.sym);
				break;

			case SDL_MOUSEBUTTONDOWN:
				_currentButton.push_back(e.button.button);
				break;

			case SDL_MOUSEBUTTONUP:
				_currentButton.remove(e.button.button);
				break;

			case SDL_MOUSEMOTION:
				_previousMousePosition = _mousePosition;
				_mousePosition = { e.motion.x, e.motion.y };
				break;
			}
		}
	}

	bool Input::isDown(SDL_Keycode key) const
	{
		for (auto it = _currentKeys.rbegin(); it != _currentKeys.rend(); ++it)
		{
			if ((*it) == key)
			{
				return true;
			}
		}

		return false;
	}

	bool Input::isButDown(Uint8 button) const
	{
		for (auto it = _currentButton.rbegin(); it != _currentButton.rend(); ++it)
		{
			if ((*it) == button)
			{
				return true;
			}
		}

		return false;
	}

	bool Input::wasDown(SDL_Keycode key) const
	{
		for (auto it = _previousKeys.rbegin(); it != _previousKeys.rend(); ++it)
		{
			if ((*it) == key)
			{
				return true;
			}
		}

		return false;
	}

	bool Input::wasButDown(Uint8 button) const
	{
		for (auto it = _previousButton.rbegin(); it != _previousButton.rend(); ++it)
		{
			if ((*it) == button)
			{
				return true;
			}
		}
		return false;
	}
