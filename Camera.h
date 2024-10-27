#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float ROLL        =  0.0f;
const float SPEED       =  10.0f;
const float SENSITIVITY =  0.1f;
const float FOV         =  90.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors, and Matrices for use in OpenGL
class Camera
{
public:
    // Camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float fov;

    // Euler angles
    float yaw;
    float pitch;
    float roll;

    // Camera options
    float moveSpeed;
    float mouseSensitivity;

    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float fov = FOV, float yaw = YAW, float pitch = PITCH, float roll = ROLL)
        : front(glm::vec3(0.0f, 0.0f, -1.0f)), moveSpeed(SPEED), mouseSensitivity(SENSITIVITY)
    {
        this->position = position;
        this->worldUp = up;
		this->fov = fov;
        this->yaw = yaw;
        this->pitch = pitch;
        this->roll = roll;
        updateCameraVectors();
    }

    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float roll = ROLL)
        : front(glm::vec3(0.0f, 0.0f, -1.0f)), moveSpeed(SPEED), mouseSensitivity(SENSITIVITY)
    {
        this->position = glm::vec3(posX, posY, posZ);
        this->worldUp = glm::vec3(upX, upY, upZ);
        this->yaw = yaw;
        this->pitch = pitch;
        this->roll = roll;
        updateCameraVectors();
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt matrix
    glm::mat4 getViewMatrix()
    {
        return glm::lookAt(position, position + front, up);
    }

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void processKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = moveSpeed * deltaTime;
        if (direction == FORWARD)
            position += front * velocity;
        if (direction == BACKWARD)
            position -= front * velocity;
        if (direction == LEFT)
            position -= right * velocity;
        if (direction == RIGHT)
            position += right * velocity;
    }

    // Processes input received from a mouse input system. Expects the offset value in both the x and y directions.
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        // Constrain pitch
        if (constrainPitch)
        {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        // Update Front, Right, and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // Calculate the new front vector
        glm::vec3 frontVec;
        frontVec.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        frontVec.y = sin(glm::radians(pitch));
        frontVec.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(frontVec);

        // Calculate the new right and up vectors considering roll
        glm::vec3 rightVec = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(rightVec, front));

        // Apply roll to the right and up vectors
        glm::mat4 rollMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(roll), front);
        right = glm::vec3(rollMatrix * glm::vec4(rightVec, 1.0f));
        up = glm::vec3(rollMatrix * glm::vec4(up, 1.0f));
    }
};

#endif
