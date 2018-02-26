#pragma once

#include "Model.hpp"

class BallModel : public Model
{
public:
	BallModel(Input& input);
	~BallModel();

	void update();

private:
	Input& _input;
	vec3 _velocity;
	float _movement;
};

