#pragma once
#include "BaseObject.h"
#include "Shader.h"
#include <glad/glad.h> 
#include "GraphicsObject.h"
#include "Scene.h"
#include "Camera.h"


class Renderer :
    public BaseObject
{
private:
        std::shared_ptr<Shader> shader;
        unsigned int vaoId;
        std::shared_ptr<Scene> scene;
        glm::mat4 view;
        glm::mat4 projection;

public:
    Renderer(std::shared_ptr<Shader> shader2)
    {
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);
        shader = shader2;
        glGenVertexArrays(1, &vaoId);
    }
    inline const std::shared_ptr<Shader>& GetShader() const { return shader; }
    std::shared_ptr<Scene> GetScene()
    {
        return scene;
    }
    void SetScene(std::shared_ptr<Scene> sceneNew)
    {
        scene = sceneNew;
    }
    void SetView(glm::mat4 viewNew)
    {
        view = viewNew;
    }
    void SetProjection(glm::mat4 projection2)
    {
        projection = projection2;
    }

    void AllocateVertexBuffers() 
    {
        std::vector<std::shared_ptr<GraphicsObject>> objects = scene->GetObjects();
        glBindVertexArray(vaoId);
        for (auto& object : objects) {
            object->StaticAllocateBuffers();
        }
        glBindVertexArray(0);
    }
    
    void RenderScene(Camera& camera)
    {
        if (shader->IsCreated()) {
            glUseProgram(shader->GetShaderProgram());
            glBindVertexArray(vaoId);
            //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            shader->SendMat4Uniform("view", view);
            shader->SendMat4Uniform("projection", projection);
            shader->SendVec3Uniform("cameraPos", camera.GetPosition());  // had to create a GetPosition() method for this?
            shader->SendFloatUniform("globalLightAttenuationCoef", scene->GetGlobalLight().attenuationCoef);
            shader->SendFloatUniform("localLightAttenuationCoef", scene->GetLocalLight().attenuationCoef);
            shader->SendFloatUniform("globalLightIntensity", scene->GetGlobalLight().intensity);
            shader->SendFloatUniform("localLightIntensity", scene->GetLocalLight().intensity);
            shader->SendVec3Uniform("globalLightColor", scene->GetGlobalLight().color);
            shader->SendVec3Uniform("localLightColor", scene->GetLocalLight().color);
            shader->SendVec3Uniform("globalLightPosition", scene->GetGlobalLight().position);
            shader->SendVec3Uniform("localLightPosition", scene->GetLocalLight().position);

            // Render the objects in the scene
            // might need to change this so the current user poke is rendered and not the rest of the inventory
            for (auto& object : scene->GetObjects()) {
                RenderObject(*object);
            }
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glUseProgram(0);
            glBindVertexArray(0);
        }
    }
private:
    void RenderObject(GraphicsObject& object)
    {
        shader->SendMat4Uniform("world", object.GetReferenceFrame());
        shader->SendFloatUniform("materialAmbientIntensity", object.GetMaterial().ambientIntensity);
        shader->SendFloatUniform("materialSpecularIntensity", object.GetMaterial().specularIntensity);
        shader->SendFloatUniform("materialShininess", object.GetMaterial().shininess);

        auto& buffer = object.GetVertexBuffer();
        buffer->Select();
        if (buffer->HasTexture())
        {
            shader->SendIntUniform("texUnit", buffer->GetTextureUnit());
            buffer->GetTexture()->SelectToRender();
        }
        buffer->SetUpAttributeInterpretration();
        if (object.IsIndexed())
        {
            auto& indexBuffer = object.GetIndexBuffer();
            indexBuffer->Select(); // selecting buffer
            glDrawElements(buffer->GetPrimitiveType(), indexBuffer->GetIndexCount(),
                GL_UNSIGNED_SHORT, (void*)0);
            // deselect missing?
            indexBuffer->Deselect();
        }
        else
        {
            glDrawArrays(buffer->GetPrimitiveType(), 0, buffer->GetNumberOfVertices());
        }

        // Recursively render the children
        auto& children = object.GetChildren();
        for (auto& child : children) {
            RenderObject(*child);
        }
    }
}; 


/*
class Renderer :
    public BaseObject
{
private:
    std::shared_ptr<Shader> shader;
    unsigned int vaoId;

public:
    Renderer(std::shared_ptr<Shader> shader);
    inline const std::shared_ptr<Shader>& GetShader() const { return shader; }
    void AllocateVertexBuffers(const auto& objects);
    void RenderScene(std::shared_ptr<Scene> scene, glm::mat4 view);
private:
    void RenderObject(const GraphicsObject& object);
};*/

