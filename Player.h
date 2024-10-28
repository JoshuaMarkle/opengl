#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

using Vec2 = glm::vec2;
using Vec3 = glm::vec3;

class Player
{
public:
    // Attributes
    Vec3 position;
    Vec3 rotation;
    Camera* camera;

	float yVelocity;
	bool grounded;
	const float gravity = -30.0f;
	const float jumpSpeed = 10.0f;

	float moveSpeed = 6.0f;

    // Constructor
    Player(Vec3 position = Vec3(0.0f, 0.0f, 0.0f), 
           Camera* camera = nullptr)
    {
        this->position = position;
        this->rotation = Vec3(0.0f, 0.0f, 0.0f);
        this->camera = camera;

		this->yVelocity = 0.0f;
		this->grounded = true;
    }

	// Update the player position
	void move(const Vec2& direction, float deltaTime) {
		if (camera) {
			// Calculate the forward and right vectors
			Vec3 forward = glm::normalize(Vec3(camera->front.x, 0.0f, camera->front.z));
			Vec3 right = glm::normalize(glm::cross(forward, camera->worldUp));

			// Move in the direction specified by the input
			position += (forward * direction.y + right * direction.x) * moveSpeed * deltaTime;

			// Update the camera's position
			camera->position = position;
		}
	}

	// Make the player jump
    void jump() {
        if (grounded) {
            yVelocity = jumpSpeed;
            grounded = false;
        }
    }

	// Update the player's vertical position (gravity and jumping)
	void updateVertical(float deltaTime) {
        if (!grounded) {
            // Apply gravity to the vertical velocity
            yVelocity += gravity * deltaTime;

            // Update the player's Y position
            position.y += yVelocity * deltaTime;

            // Check if the player has landed on the ground
            if (position.y <= 0.0f) {
                position.y = 0.0f;
                yVelocity = 0.0f;
                grounded = true;
            }
        }
    }
};

#endif
