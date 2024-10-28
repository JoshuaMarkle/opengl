#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
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
        : position(position), rotation(rotation), scale(scale), VAO(0), VBO(0), EBO(0) {}

    // Initializes the object by setting up VAO, VBO, and EBO
    virtual void init()
    {
        // Ensure vertices and indices are populated
        if (vertices.empty() || indices.empty()) {
            std::cerr << "Error: Vertices or indices are empty. Object initialization failed." << std::endl;
            return;
        }

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

        // Set vertex attribute pointers (assuming 3D positions)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind VAO
        glBindVertexArray(0);
    }

    // Returns the model matrix based on position, rotation, and scale
    glm::mat4 getModelMatrix() const
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
    virtual void draw() const
    {
        if (VAO != 0) {
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        } else {
            std::cerr << "Error: VAO is not initialized. Cannot draw object." << std::endl;
        }
    }

    // Destructor to clean up OpenGL resources
    virtual ~Object()
    {
        if (VAO != 0) glDeleteVertexArrays(1, &VAO);
        if (VBO != 0) glDeleteBuffers(1, &VBO);
        if (EBO != 0) glDeleteBuffers(1, &EBO);
    }
};

#endif
