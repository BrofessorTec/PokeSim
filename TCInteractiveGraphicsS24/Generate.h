#pragma once
#include "BaseObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
class Generate :
    public BaseObject
{
public:
    static std::shared_ptr<VertexBuffer> Cuboid(
        float width, float height, float depth,
        glm::vec3 color = { 1.0f, 1.0f, 1.0f },
        glm::vec2 tex = { 1.0f, 1.0f });

    static std::shared_ptr<VertexBuffer> XZPlane(
        float width, float depth,
        glm::vec3 color = { 1.0f, 1.0f, 1.0f },
        glm::vec2 tex = { 1.0f, 1.0 });

    static std::shared_ptr<VertexBuffer> XYPlane(
        float width, float height,
        glm::vec3 color = { 1.0f, 1.0f, 1.0f },
        glm::vec2 tex = { 1.0f, 1.0 });

    static std::shared_ptr<VertexBuffer> CuboidNorm(
        float width, float height, float depth,
        glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f },
        glm::vec3 normal = { 1.0f, 1.0f, 1.0f },
        glm::vec2 tex = { 1.0f, 1.0f });

    static std::shared_ptr<VertexBuffer> XZPlaneNorm(
        float width, float depth,
        glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f },
        glm::vec3 normal = { 1.0f, 1.0f, 1.0f },
        glm::vec2 tex = { 1.0f, 1.0 });

    static std::shared_ptr<VertexBuffer> XYPlaneNorm(
        float width, float height,
        glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f },
        glm::vec3 normal = { 1.0f, 1.0f, 1.0f },
        glm::vec2 tex = { 1.0f, 1.0 });

    static std::shared_ptr<VertexBuffer> XYPlaneNormReverse(
        float width, float height,
        glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f },
        glm::vec3 normal = { 1.0f, 1.0f, 1.0f },
        glm::vec2 tex = { 1.0f, 1.0 });

    static void GenerateXZCircle(double radius, glm::vec3 color, int steps, std::shared_ptr<VertexBuffer> bufferToFill);

    static void LineCircleIndexes(
        std::shared_ptr<IndexBuffer>& bufferToFill,
        int numberOfLineSegments, bool isClosed = true);

    static void GenerateXZCylinder(double radius, double height, glm::vec3 color, int steps, std::shared_ptr<VertexBuffer> bufferToFill);
    static void LineCylinderIndexes(
        std::shared_ptr<IndexBuffer>& bufferToFill,
        int numberOfLineSegments);

    static std::shared_ptr<VertexBuffer> Arrow(
        float width = 2, float height = 2, float depth = 8,
        glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f},
        glm::vec2 tex = { 1.0f, 1.0f });


    static std::shared_ptr<VertexBuffer> ArrowNorm(
        float width = 2, float height = 2, float depth = 8,
        glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f },
        glm::vec3 normal = { 1.0f, 1.0f, 1.0f },
        glm::vec2 tex = { 1.0f, 1.0f });

};

