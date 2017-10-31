#pragma once

#include <glm\glm.hpp>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>

struct vertices
{
	float x, y, z;

	vertices(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
	vertices(const vertices &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
};