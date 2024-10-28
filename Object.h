#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

using Vec3 = glm::vec3;

// A generic Object class for 3D objects
class Object
{
public:
    // Object attributes
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    // OpenGL attributes
    unsigned int VAO, VBO, EBO;

    // Constructor with default values
    Object(Vec3 position = Vec3(0.0f, 0.0f, 0.0f), 
           Vec3 rotation = Vec3(0.0f, 0.0f, 0.0f), 
           Vec3 scale = Vec3(1.0f, 1.0f, 1.0f))
    {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
        VAO = 0;
        VBO = 0;
        EBO = 0;
    }

    // Initializes the object by setting up VAO, VBO, and EBO
    virtual void init()
    {
        // Generate VAO, VBO, and EBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind VAO
        glBindVertexArray(VAO);

        // Bind VBO and buffer data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        // Bind EBO and buffer data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // Set vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind VAO
        glBindVertexArray(0);
    }

    // Returns the model matrix based on position, rotation, and scale
    glm::mat4 getModelMatrix()
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation.x), Vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), Vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), Vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, scale);
        return model;
    }

    // Draw the object
    virtual void draw()
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    // Destructor to clean up OpenGL resources
    virtual ~Object()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
};

#endif
