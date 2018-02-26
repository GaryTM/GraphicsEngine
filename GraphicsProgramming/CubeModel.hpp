#pragma once

#include "Model.hpp"

class CubeModel : public Model
{
public:
	CubeModel(Input& input);
	~CubeModel();

	void update();

private:
	Input& _input;
	vec3 _velocity;
	float _movement;
};

