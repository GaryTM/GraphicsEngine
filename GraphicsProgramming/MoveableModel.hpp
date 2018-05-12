#pragma once

#include "Model.hpp"
/*Aserived class that would be used for moving models*/
class MoveableModel : public Model
{
public:
	MoveableModel(Input& input);
	~MoveableModel();

	void update();

private:
	Input& _input;
	vec3 _velocity;
	float _movement;
};

