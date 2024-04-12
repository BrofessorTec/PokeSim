#include "Generate.h"

std::shared_ptr<VertexBuffer> Generate::Cuboid(float width, float height, float depth, glm::vec3 color, glm::vec2 tex)
{
    // 2.1.Parameter tex specifies the repeat value for s and t.
    // 2.2.It creates a vertex buffer, fills it with vertex data based on the arguments, and then
    //    returns it.
    
    std::shared_ptr<VertexBuffer> vertexBuffer3d = std::make_shared<VertexBuffer>(8);

    float halfWidth = width / 2;
    float halfHeight = height / 2;
    float halfDepth = depth / 2;


	// front face  with 6 vertices and no indexed buffer?
	vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0, tex.t);
	vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, 0, 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0, tex.t);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, tex.s, tex.t);

    // right face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, 0, 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], tex[1]);

    // back face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color[2], 0, 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], tex[0], tex[1]);

    // left face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color[2], 0, 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color[0], color[1], color[2], tex[0], tex[1]);

    // top face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color[0], color[1], color[2], 0, 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color[0], color[1], color[2], tex[0], tex[1]);

    // bottom face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color[0], color[1], color[2], 0, 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color[2], tex[0], tex[1]);


    return vertexBuffer3d;
}

std::shared_ptr<VertexBuffer> Generate::XZPlane(float width, float depth, glm::vec3 color, glm::vec2 tex)
{
    std::shared_ptr<VertexBuffer> vertexBufferFloor = std::make_shared<VertexBuffer>(8);
    float halfWidth = width / 2;
    float halfDepth = depth / 2;

    // top face  with 6 vertices and no indexed buffer?
    vertexBufferFloor->AddVertexData(8, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, 0, tex.t);
    vertexBufferFloor->AddVertexData(8, -halfWidth, 0, halfDepth, color.r, color.g, color.b, 0, 0);
    vertexBufferFloor->AddVertexData(8, halfWidth, 0, halfDepth, color.r, color.g, color.b, tex.s, 0);
    vertexBufferFloor->AddVertexData(8, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, 0, tex.t);
    vertexBufferFloor->AddVertexData(8, halfWidth, 0, halfDepth, color.r, color.g, color.b, tex.s, 0);
    vertexBufferFloor->AddVertexData(8, halfWidth, 0, -halfDepth, color.r, color.g, color.b, tex.s, tex.t);

    // bottom face  with 6 vertices and no indexed buffer?
    vertexBufferFloor->AddVertexData(8, halfWidth, 0, -halfDepth, color.r, color.g, color.b, 0, tex.t);
    vertexBufferFloor->AddVertexData(8, halfWidth, 0, halfDepth, color.r, color.g, color.b, 0, 0);
    vertexBufferFloor->AddVertexData(8, -halfWidth, 0, halfDepth, color.r, color.g, color.b, tex.s, 0);
    vertexBufferFloor->AddVertexData(8, halfWidth, 0, -halfDepth, color.r, color.g, color.b, 0, tex.t);
    vertexBufferFloor->AddVertexData(8, -halfWidth, 0, halfDepth, color.r, color.g, color.b, tex.s, 0);
    vertexBufferFloor->AddVertexData(8, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, tex.s, tex.t);

    return vertexBufferFloor;
}

std::shared_ptr<VertexBuffer> Generate::XYPlane(float width, float height, glm::vec3 color, glm::vec2 tex)
{
    std::shared_ptr<VertexBuffer> vertexBufferFloor = std::make_shared<VertexBuffer>(8);
    float halfWidth = width / 2;
    float halfHeight = height / 2;

    // front face
    vertexBufferFloor->AddVertexData(8, -halfWidth, halfHeight, 0, color.r, color.g, color.b, 0, tex.t);
    vertexBufferFloor->AddVertexData(8, -halfWidth, -halfHeight, 0, color.r, color.g, color.b, 0, 0);
    vertexBufferFloor->AddVertexData(8, halfWidth, -halfHeight, 0, color.r, color.g, color.b, tex.s, 0);
    vertexBufferFloor->AddVertexData(8, -halfWidth, halfHeight, 0, color.r, color.g, color.b, 0, tex.t);
    vertexBufferFloor->AddVertexData(8, halfWidth, -halfHeight, 0, color.r, color.g, color.b, tex.s, 0);
    vertexBufferFloor->AddVertexData(8, halfWidth, halfHeight, 0, color.r, color.g, color.b, tex.s, tex.t);

    // back face
    vertexBufferFloor->AddVertexData(8, halfWidth, halfHeight, 0, color.r, color.g, color.b, 0, tex.t);
    vertexBufferFloor->AddVertexData(8, halfWidth, -halfHeight, 0, color.r, color.g, color.b, 0, 0);
    vertexBufferFloor->AddVertexData(8, -halfWidth, -halfHeight, 0, color.r, color.g, color.b, tex.s, 0);
    vertexBufferFloor->AddVertexData(8, halfWidth, halfHeight, 0, color.r, color.g, color.b, 0, tex.t);
    vertexBufferFloor->AddVertexData(8, -halfWidth, -halfHeight, 0, color.r, color.g, color.b, tex.s, 0);
    vertexBufferFloor->AddVertexData(8, -halfWidth, halfHeight, 0, color.r, color.g, color.b, tex.s, tex.t);

    return vertexBufferFloor;
}

std::shared_ptr<VertexBuffer> Generate::CuboidNorm(float width, float height, float depth, glm::vec4 color, glm::vec3 normal, glm::vec2 tex)
{

    std::shared_ptr<VertexBuffer> vertexBuffer3d = std::make_shared<VertexBuffer>(12);

    float halfWidth = width / 2;
    float halfHeight = height / 2;
    float halfDepth = depth / 2;


    // front face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0, 0, normal[2], 0, tex.t);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0, 0, normal[2], 0, 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0, 0, normal[2], tex.s, 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0, 0, normal[2], 0, tex.t);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0, 0, normal[2], tex.s, 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0, 0, normal[2], tex.s, tex.t);

    // right face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, normal[0], 0, 0, 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, normal[0], 0, 0, 0, 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, normal[0], 0, 0, tex[0], 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, normal[0], 0, 0, 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, normal[0], 0, 0, tex[0], 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, normal[0], 0, 0, tex[0], tex[1]);

    // back face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, 0, -normal[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, 0, -normal[2], 0, 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, 0, -normal[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, 0, -normal[2], 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, 0, -normal[2], tex[0], 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, 0, -normal[2], tex[0], tex[1]);

    // left face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, -normal[0], 0, 0, 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, -normal[0], 0, 0, 0, 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, color.a, -normal[0], 0, 0, tex[0], 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, -normal[0], 0, 0, 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, color.a, -normal[0], 0, 0, tex[0], 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, color.a, -normal[0], 0, 0, tex[0], tex[1]);

    // top face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, normal[1], 0, 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, color.a, 0, normal[1], 0, 0, 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, color.a, 0, normal[1], 0, tex[0], 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, normal[1], 0, 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, color.a, 0, normal[1], 0, tex[0], 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, normal[1], 0, tex[0], tex[1]);

    // bottom face  with 6 vertices and no indexed buffer?
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, -normal[1], 0, 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, color.a, 0, -normal[1], 0, 0, 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, color.a, 0, -normal[1], 0, tex[0], 0);
    vertexBuffer3d->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, -normal[1], 0, 0, tex[1]);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, color.a, 0, -normal[1], 0, tex[0], 0);
    vertexBuffer3d->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, -normal[1], 0, tex[0], tex[1]);


    return vertexBuffer3d;
}

std::shared_ptr<VertexBuffer> Generate::XZPlaneNorm(float width, float depth, glm::vec4 color, glm::vec3 normal, glm::vec2 tex)
{
    std::shared_ptr<VertexBuffer> vertexBufferFloor = std::make_shared<VertexBuffer>(12);
    float halfWidth = width / 2;
    float halfDepth = depth / 2;

    // top face  with 6 vertices and no indexed buffer
    vertexBufferFloor->AddVertexData(12, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, color.a, 0, normal[1], 0, 0, tex.t);
    vertexBufferFloor->AddVertexData(12, -halfWidth, 0, halfDepth, color.r, color.g, color.b, color.a, 0, normal[1], 0, 0, 0);
    vertexBufferFloor->AddVertexData(12, halfWidth, 0, halfDepth, color.r, color.g, color.b, color.a, 0, normal[1], 0, tex.s, 0);
    vertexBufferFloor->AddVertexData(12, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, color.a, 0, normal[1], 0, 0, tex.t);
    vertexBufferFloor->AddVertexData(12, halfWidth, 0, halfDepth, color.r, color.g, color.b, color.a, 0, normal[1], 0, tex.s, 0);
    vertexBufferFloor->AddVertexData(12, halfWidth, 0, -halfDepth, color.r, color.g, color.b, color.a, 0, normal[1], 0, tex.s, tex.t);

    // bottom face  with 6 vertices and no indexed buffer
    vertexBufferFloor->AddVertexData(12, halfWidth, 0, -halfDepth, color.r, color.g, color.b, color.a, 0, -normal[1], 0, 0, tex.t);
    vertexBufferFloor->AddVertexData(12, halfWidth, 0, halfDepth, color.r, color.g, color.b, color.a, 0, -normal[1], 0, 0, 0);
    vertexBufferFloor->AddVertexData(12, -halfWidth, 0, halfDepth, color.r, color.g, color.b, color.a, 0, -normal[1], 0, tex.s, 0);
    vertexBufferFloor->AddVertexData(12, halfWidth, 0, -halfDepth, color.r, color.g, color.b, color.a, 0, -normal[1], 0, 0, tex.t);
    vertexBufferFloor->AddVertexData(12, -halfWidth, 0, halfDepth, color.r, color.g, color.b, color.a, 0, -normal[1], 0, tex.s, 0);
    vertexBufferFloor->AddVertexData(12, -halfWidth, 0, -halfDepth, color.r, color.g, color.b, color.a, 0, -normal[1], 0, tex.s, tex.t);

    return vertexBufferFloor;
}




std::shared_ptr<VertexBuffer> Generate::XYPlaneNorm(float width, float height, glm::vec4 color, glm::vec3 normal, glm::vec2 tex)
{
    std::shared_ptr<VertexBuffer> vertexBufferPlane = std::make_shared<VertexBuffer>(12);
    float halfWidth = width / 2;
    float halfHeight = height / 2;

    // front face  with 6 vertices and no indexed buffer
    vertexBufferPlane->AddVertexData(12, -halfWidth, halfHeight, 0, color.r, color.g, color.b, color.a, 0, 0, normal[2], 0, tex.t);
    vertexBufferPlane->AddVertexData(12, -halfWidth, -halfHeight, 0, color.r, color.g, color.b, color.a, 0, 0, normal[2], 0, 0);
    vertexBufferPlane->AddVertexData(12, halfWidth, -halfHeight, 0, color.r, color.g, color.b, color.a, 0, 0, normal[2], tex.s, 0);
    vertexBufferPlane->AddVertexData(12, -halfWidth, halfHeight, 0, color.r, color.g, color.b, color.a, 0, 0, normal[2], 0, tex.t);
    vertexBufferPlane->AddVertexData(12, halfWidth, -halfHeight, 0, color.r, color.g, color.b, color.a, 0, 0, normal[2], tex.s, 0);
    vertexBufferPlane->AddVertexData(12, halfWidth, halfHeight, 0, color.r, color.g, color.b, color.a, 0, 0, normal[2], tex.s, tex.t);

    // back face  with 6 vertices and no indexed buffer
    vertexBufferPlane->AddVertexData(12, halfWidth, halfHeight, 0, color[0], color[1], color.b, color.a, 0, 0, -normal[2], 0, tex.t);
    vertexBufferPlane->AddVertexData(12, halfWidth, -halfHeight, 0, color[0], color[1], color.b, color.a, 0, 0, -normal[2], 0, 0);
    vertexBufferPlane->AddVertexData(12, -halfWidth, -halfHeight, 0, color[0], color[1], color.b, color.a, 0, 0, -normal[2], tex.s, 0);
    vertexBufferPlane->AddVertexData(12, halfWidth, halfHeight, 0, color[0], color[1], color.b, color.a, 0, 0, -normal[2], 0, tex.t);
    vertexBufferPlane->AddVertexData(12, -halfWidth, -halfHeight, 0, color[0], color[1], color.b, color.a, 0, 0, -normal[2], tex.s, 0);
    vertexBufferPlane->AddVertexData(12, -halfWidth, halfHeight, 0, color[0], color[1], color.b, color.a, 0, 0, -normal[2], tex.s, tex.t);

    return vertexBufferPlane;
}


std::shared_ptr<VertexBuffer> Generate::XYPlaneNormReverse(float width, float height, glm::vec4 color, glm::vec3 normal, glm::vec2 tex)
{
    std::shared_ptr<VertexBuffer> vertexBufferPlane = std::make_shared<VertexBuffer>(12);
    float halfWidth = width / 2;
    float halfHeight = height / 2;

    // front face  with 6 vertices and no indexed buffer
    vertexBufferPlane->AddVertexData(12, -halfWidth, halfHeight, 0, color.r, color.g, color.b, color.a, 0, 0, normal[2], 1.0f, 1.0f); // top left
    vertexBufferPlane->AddVertexData(12, -halfWidth, -halfHeight, 0, color.r, color.g, color.b, color.a, 0, 0, normal[2], 1.0f, 0.0f); // bottom left
    vertexBufferPlane->AddVertexData(12, halfWidth, -halfHeight, 0, color.r, color.g, color.b, color.a, 0, 0, normal[2], 0.0f, 0.0f); // bottom right
    vertexBufferPlane->AddVertexData(12, -halfWidth, halfHeight, 0, color.r, color.g, color.b, color.a, 0, 0, normal[2], 1.0f, 1.0f); // top left
    vertexBufferPlane->AddVertexData(12, halfWidth, -halfHeight, 0, color.r, color.g, color.b, color.a, 0, 0, normal[2], 0.0f, 0.0f); //bottom right
    vertexBufferPlane->AddVertexData(12, halfWidth, halfHeight, 0, color.r, color.g, color.b, color.a, 0, 0, normal[2], 0.0f, 1.0f); // top right

    return vertexBufferPlane;
}

void Generate::GenerateXZCircle(double radius, glm::vec3 color, int steps, std::shared_ptr<VertexBuffer> bufferToFill)
{
    // std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(6);
    for (double theta = 0.0; theta < 360.0; theta += steps) {
        double radians = glm::radians(theta);
        double x = radius * std::cosf(radians);
        double z = radius * std::sinf(radians);
        bufferToFill->AddVertexData(6, x, 0, z, color.r, color.g, color.b);
    }
}

void Generate::LineCircleIndexes(std::shared_ptr<IndexBuffer>& bufferToFill, int numberOfLineSegments, bool isClosed)
{
    // finish this
    /*
    * 4.1.It fills the index buffer with indexes for a line circle. There are two indexes per line
        segment. If the circle is closed, then the last line segment includes the starting index
    */

    unsigned short nextIndex;
    if (isClosed)
    {
        for (unsigned short index = 0; index < numberOfLineSegments; index++) {
            bufferToFill->AddIndexData(index);
            nextIndex = (index + 1) % static_cast<unsigned short>(numberOfLineSegments);
            bufferToFill->AddIndexData(nextIndex);
        }
    }
    else 
    {
        for (unsigned short index = 0; index < numberOfLineSegments - 1; index++) {
            bufferToFill->AddIndexData(index);
            nextIndex = index + 1;
            bufferToFill->AddIndexData(nextIndex);
        }
    }
}

void Generate::GenerateXZCylinder(double radius, double height, glm::vec3 color, int steps, std::shared_ptr<VertexBuffer> bufferToFill)
{
    int halfHeight = height / 2;

    // top ring
    for (double theta = 0.0; theta < 360.0; theta += steps) {
        double radians = glm::radians(theta);
        double x = radius * std::cosf(radians);
        double y = (double)halfHeight;
        double z = radius * std::sinf(radians);
        bufferToFill->AddVertexData(6, x, y, z, color.r, color.g, color.b);
    }

    // bottom ring
    for (double theta = 0.0; theta < 360.0; theta += steps) {
        double radians = glm::radians(theta);
        double x = radius * std::cosf(radians);
        double y = -(double)halfHeight;
        double z = radius * std::sinf(radians);
        bufferToFill->AddVertexData(6, x, y, z, color.r, color.g, color.b);
    }
}

void Generate::LineCylinderIndexes(std::shared_ptr<IndexBuffer>& bufferToFill, int numberOfLineSegments)
{
    unsigned short nextIndex;

    // connect top ring
    for (unsigned short index = 0; index < numberOfLineSegments; index++) {
        bufferToFill->AddIndexData(index);
        nextIndex = (index + 1) % static_cast<unsigned short>(numberOfLineSegments);
        bufferToFill->AddIndexData(nextIndex);
    }

    //connect bottom ring?
    for (unsigned short index = numberOfLineSegments; index < (numberOfLineSegments + numberOfLineSegments); index++) {
        bufferToFill->AddIndexData(index);
        nextIndex = ((index + 1) % static_cast<unsigned short>(numberOfLineSegments)) + numberOfLineSegments;
        bufferToFill->AddIndexData(nextIndex);
    }

    //connect the two rings?
    for (unsigned short index = 0; index < numberOfLineSegments; index++) {
        bufferToFill->AddIndexData(index);
        nextIndex = ((index) % static_cast<unsigned short>(numberOfLineSegments)) + numberOfLineSegments;
        bufferToFill->AddIndexData(nextIndex);
    }
}

std::shared_ptr<VertexBuffer> Generate::Arrow(float width, float height, float depth, glm::vec4 color, glm::vec2 tex)
{
    std::shared_ptr<VertexBuffer> arrowBuffer = std::make_shared<VertexBuffer>(8);
    float halfWidth = width / 2;
    float halfHeight = height / 2;
    float halfDepth = depth / 2;


    // front face  with 6 vertices and no indexed buffer?
    arrowBuffer->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0, tex.t);
    arrowBuffer->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, 0, 0);
    arrowBuffer->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0);
    arrowBuffer->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0, tex.t);
    arrowBuffer->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0);
    arrowBuffer->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, tex.s, tex.t);

    // right face  with 6 vertices and no indexed buffer?
    arrowBuffer->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0, tex[1]);
    arrowBuffer->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, 0, 0);
    arrowBuffer->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], 0);
    arrowBuffer->AddVertexData(8, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0, tex[1]);
    arrowBuffer->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], 0);
    arrowBuffer->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, tex[0], tex[1]);

    // back face  with 6 vertices and no indexed buffer?
    arrowBuffer->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, 0, tex[1]);
    arrowBuffer->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, 0, 0);
    arrowBuffer->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, tex[0], 0);
    arrowBuffer->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, 0, tex[1]);
    arrowBuffer->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, tex[0], 0);
    arrowBuffer->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, tex[0], tex[1]);

    // left face  with 6 vertices and no indexed buffer?
    arrowBuffer->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, 0, tex[1]);
    arrowBuffer->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, 0, 0);
    arrowBuffer->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, tex[0], 0);
    arrowBuffer->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, 0, tex[1]);
    arrowBuffer->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, tex[0], 0);
    arrowBuffer->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, tex[0], tex[1]);

    // top face  with 6 vertices and no indexed buffer?
    arrowBuffer->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, 0, tex[1]);
    arrowBuffer->AddVertexData(8, -halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, 0, 0);
    arrowBuffer->AddVertexData(8, halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, tex[0], 0);
    arrowBuffer->AddVertexData(8, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, 0, tex[1]);
    arrowBuffer->AddVertexData(8, halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, tex[0], 0);
    arrowBuffer->AddVertexData(8, halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, tex[0], tex[1]);

    // bottom face  with 6 vertices and no indexed buffer?
    arrowBuffer->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, 0, tex[1]);
    arrowBuffer->AddVertexData(8, halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, 0, 0);
    arrowBuffer->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, tex[0], 0);
    arrowBuffer->AddVertexData(8, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, 0, tex[1]);
    arrowBuffer->AddVertexData(8, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, tex[0], 0);
    arrowBuffer->AddVertexData(8, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, tex[0], tex[1]);


    return arrowBuffer;
}

std::shared_ptr<VertexBuffer> Generate::ArrowNorm(float width, float height, float depth, glm::vec4 color, glm::vec3 normal, glm::vec2 tex)
{
    std::shared_ptr<VertexBuffer> arrowBuffer = std::make_shared<VertexBuffer>(12);
    float halfWidth = width / 2;
    float halfHeight = height / 2;
    float halfDepth = depth / 2;


    // front face  with 6 vertices and no indexed buffer?
    arrowBuffer->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0, 0, normal[2], 0, tex.t);
    arrowBuffer->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0, 0, normal[2], 0, 0);
    arrowBuffer->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0, 0, normal[2], tex.s, 0);
    arrowBuffer->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0, 0, normal[2], 0, tex.t);
    arrowBuffer->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0, 0, normal[2], tex.s, 0);
    arrowBuffer->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, 0, 0, normal[2], tex.s, tex.t);

    // right face  with 6 vertices and no indexed buffer?
    arrowBuffer->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, normal[0], 0, 0, 0, tex[1]);
    arrowBuffer->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, color.a, normal[0], 0, 0, 0, 0);
    arrowBuffer->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, normal[0], 0, 0, tex[0], 0);
    arrowBuffer->AddVertexData(12, halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, color.a, normal[0], 0, 0, 0, tex[1]);
    arrowBuffer->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, color.a, normal[0], 0, 0, tex[0], 0);
    arrowBuffer->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, color.a, normal[0], 0, 0, tex[0], tex[1]);

    // back face  with 6 vertices and no indexed buffer?
    arrowBuffer->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, 0, -normal[2], 0, tex[1]);
    arrowBuffer->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, 0, -normal[2], 0, 0);
    arrowBuffer->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, 0, -normal[2], tex[0], 0);
    arrowBuffer->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, 0, -normal[2], 0, tex[1]);
    arrowBuffer->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, 0, -normal[2], tex[0], 0);
    arrowBuffer->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, 0, -normal[2], tex[0], tex[1]);

    // left face  with 6 vertices and no indexed buffer?
    arrowBuffer->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, -normal[0], 0, 0, 0, tex[1]);
    arrowBuffer->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, -normal[0], 0, 0, 0, 0);
    arrowBuffer->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, color.a, -normal[0], 0, 0, tex[0], 0);
    arrowBuffer->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, -normal[0], 0, 0, 0, tex[1]);
    arrowBuffer->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, color.a, -normal[0], 0, 0, tex[0], 0);
    arrowBuffer->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, color.a, -normal[0], 0, 0, tex[0], tex[1]);

    // top face  with 6 vertices and no indexed buffer?
    arrowBuffer->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, normal[1], 0, 0, tex[1]);
    arrowBuffer->AddVertexData(12, -halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, color.a, 0, normal[1], 0, 0, 0);
    arrowBuffer->AddVertexData(12, halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, color.a, 0, normal[1], 0, tex[0], 0);
    arrowBuffer->AddVertexData(12, -halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, normal[1], 0, 0, tex[1]);
    arrowBuffer->AddVertexData(12, halfWidth, halfHeight, halfDepth, color[0], color[1], color.b, color.a, 0, normal[1], 0, tex[0], 0);
    arrowBuffer->AddVertexData(12, halfWidth, halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, normal[1], 0, tex[0], tex[1]);

    // bottom face  with 6 vertices and no indexed buffer?
    arrowBuffer->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, -normal[1], 0, 0, tex[1]);
    arrowBuffer->AddVertexData(12, halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, color.a, 0, -normal[1], 0, 0, 0);
    arrowBuffer->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, color.a, 0, -normal[1], 0, tex[0], 0);
    arrowBuffer->AddVertexData(12, halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, -normal[1], 0, 0, tex[1]);
    arrowBuffer->AddVertexData(12, -halfWidth, -halfHeight, halfDepth, color[0], color[1], color.b, color.a, 0, -normal[1], 0, tex[0], 0);
    arrowBuffer->AddVertexData(12, -halfWidth, -halfHeight, -halfDepth, color[0], color[1], color.b, color.a, 0, -normal[1], 0, tex[0], tex[1]);


    return arrowBuffer;
}
