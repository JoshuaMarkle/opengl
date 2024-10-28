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

	Vec3 velocity;
	bool grounded;

	const float maxSpeed = 1000.0f;
	const float moveSpeed = 2.0f;
	const float jumpSpeed = 10.0f;
	const float gravity = -25.0f;

	const float dragForce = 12.0f;
	const float frictionForce = 15.0f;

    // Constructor
    Player(Vec3 position = Vec3(0.0f, 0.0f, 0.0f), 
           Camera* camera = nullptr)
    {
        this->position = position;
        this->rotation = Vec3(0.0f, 0.0f, 0.0f);
        this->camera = camera;

		this->velocity = Vec3(0.0f, 0.0f, 0.0f);
		this->grounded = true;
    }

	// Player movement
	void move(const Vec2& direction, float deltaTime) {
		if (camera) {
			// Calculate the forward and right vectors
			Vec3 forward = glm::normalize(Vec3(camera->front.x, 0.0f, camera->front.z));
			Vec3 right = glm::normalize(glm::cross(forward, camera->worldUp));

			// Calculate target velocity
			velocity += (forward * direction.y + right * direction.x) * moveSpeed;

			// Apply friction or drag to reduce velocity
			float damping = grounded ? frictionForce : dragForce;
			velocity.x *= 1.0f - (damping * deltaTime);
			velocity.z *= 1.0f - (damping * deltaTime);

			// Update the player's position
			position += velocity * deltaTime;

			// Update the camera's position
			camera->position = position;
		}
	}

	// Make the player jump
    void jump() {
        if (grounded) {
            velocity.y = jumpSpeed;
            grounded = false;
        }
    }

	// Update the player's vertical position (gravity and jumping)
	void updateVertical(float deltaTime) {
        if (!grounded) {
            // Apply gravity to the vertical velocity
            velocity.y += gravity * deltaTime;

            // Update the player's Y position
            position.y += velocity.y * deltaTime;

            // Check if the player has landed on the ground
            if (position.y <= 0.0f) {
                position.y = 0.0f;
                velocity.y = 0.0f;
                grounded = true;
            }
        }
    }
};

#endif
