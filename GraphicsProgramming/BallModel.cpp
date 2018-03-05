#include "BallModel.hpp"

BallModel::BallModel(Input& input) :
	_input(input),
	_velocity(0.1, 0.1, 0.1),
	_movement(1)
{
}

BallModel::~BallModel()
{
}

//The update method would pretty much be used exclusively to move objects. Not neccessary for Graphics programming handin
void BallModel::update()
{
	if (_input.wasDown(SDLK_w))
	{
		transform.SetRotation(vec3(-45, 0, 0));
	}
	if (_input.wasDown(SDLK_s))
	{
		transform.SetRotation(vec3(45, 0, 0));
	}
	if (_input.wasDown(SDLK_a))
	{
		transform.SetRotation(vec3(0, 45, 0));
	}
	if (_input.wasDown(SDLK_d))
	{
		transform.SetRotation(vec3(0, -45, 0));
	}
	//_velocity.x += _movement;

	//transform.SetPosition(transform.GetPosition() + _velocity.x);
	
}
