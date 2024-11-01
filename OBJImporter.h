#ifndef OBJIMPORTER_H
#define OBJIMPORTER_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <cstdio>
#include <cstring>
#include <iostream>

class OBJImporter {
public:
    // Loads an OBJ file
    static bool loadOBJ(
        const char* path,
        std::vector<glm::vec3>& outVertices,
        std::vector<glm::vec2>& outUVs,
        std::vector<glm::vec3>& outNormals
    ) {
        // Temporary storage for vertices, uvs, and normals
        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        std::vector<glm::vec3> tempVertices;
        std::vector<glm::vec2> tempUVs;
        std::vector<glm::vec3> tempNormals;

        // Open the file
        FILE* file = fopen(path, "r");
        if (file == nullptr) {
            std::cerr << "Failed to open OBJ file: " << path << std::endl;
            return false;
        }

        // Read the file line by line
        while (true) {
            char lineHeader[128];
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF)
                break; // End of file

            // Process vertex positions (v)
            if (strcmp(lineHeader, "v") == 0) {
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                tempVertices.push_back(vertex);
            }
            // Process texture coordinates (vt)
            else if (strcmp(lineHeader, "vt") == 0) {
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y);
                tempUVs.push_back(uv);
            }
            // Process vertex normals (vn)
            else if (strcmp(lineHeader, "vn") == 0) {
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
                tempNormals.push_back(normal);
            }
            // Process faces (f)
            else if (strcmp(lineHeader, "f") == 0) {
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                    &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                    &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

                if (matches != 9) {
                    std::cerr << "File can't be read by this parser: " << path << std::endl;
                    fclose(file);
                    return false;
                }

                // Store indices
                vertexIndices.push_back(vertexIndex[0]);
                uvIndices.push_back(uvIndex[0]);
                normalIndices.push_back(normalIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                uvIndices.push_back(uvIndex[1]);
                normalIndices.push_back(normalIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices.push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[2]);
            }
        }

        // Process indexed data into unindexed form
        for (unsigned int i = 0; i < vertexIndices.size(); i++) {
            unsigned int vertexIndex = vertexIndices[i];
            glm::vec3 vertex = tempVertices[vertexIndex - 1];
            outVertices.push_back(vertex);

            unsigned int uvIndex = uvIndices[i];
            glm::vec2 uv = tempUVs[uvIndex - 1];
            outUVs.push_back(uv);

            unsigned int normalIndex = normalIndices[i];
            glm::vec3 normal = tempNormals[normalIndex - 1];
            outNormals.push_back(normal);
        }

        fclose(file);
        return true;
    }
};

#endif // OBJIMPORTER_H
