#ifndef CUBE_H
#define CUBE_H

#include "Object.h"

using Vec3 = glm::vec3;

class Cube : public Object
{
public:
	// Constructor
	Cube(Vec3 position = Vec3(0.0f, 0.0f, 0.0f), 
	  Vec3 rotation = Vec3(0.0f, 0.0f, 0.0f), 
	  Vec3 scale = Vec3(1.0f, 1.0f, 1.0f))
	: Object(position, rotation, scale)
	{
		// Define the vertices and indices for a cube
		vertices = {
			-0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f
		};

		indices = {
			0, 1, 2, 2, 3, 0, // Front
			4, 5, 6, 6, 7, 4, // Back
			0, 3, 7, 7, 4, 0, // Left
			1, 2, 6, 6, 5, 1, // Right
			3, 2, 6, 6, 7, 3, // Top
			0, 1, 5, 5, 4, 0  // Bottom
		};

		// Initialize the cube (setup VAO, VBO, EBO)
		init();
	}
};

#endif
