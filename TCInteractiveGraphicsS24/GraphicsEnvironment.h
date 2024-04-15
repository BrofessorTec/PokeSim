#pragma once
#include "BaseObject.h"
#include "Renderer.h"
#include "Timer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h> 
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include "ObjectManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "IAnimation.h"
#include "RotateAnimation.h"
#include "SlidingAnimation.h"
#include "AttackAnimation.h"
#include "Camera.h"
#include "GraphicStructures.h"
#include "Ray.h"

class GraphicsEnvironment :
    public BaseObject
{
private: 
    GLFWwindow* window;
    std::unordered_map<std::string, std::shared_ptr<Renderer>> rendererMap;
    std::shared_ptr<ObjectManager> objManager;
    std::shared_ptr<Camera> camera;  
    GraphicStructures::MouseParams mouse;
    bool lookWithMouse = false;
    Ray mouseRayVar;

public:
    static GraphicsEnvironment* self;
    GraphicsEnvironment();
    ~GraphicsEnvironment();
    GLFWwindow* GetWindow();
    void Init(unsigned int majorVersion, unsigned int minorVersion);
    bool SetWindow(unsigned int width, unsigned int height, const std::string&
        title);
    bool InitGlad();
    void ProcessInput(GLFWwindow* window, double elapsedSeconds);
    void SetUpGraphics();
    static void OnWindowSizeChanged(GLFWwindow* window, int width, int height);
    void CreateRenderer(const std::string& name, std::shared_ptr<Shader>
        shader);
    std::shared_ptr<Renderer> GetRenderer(const std::string& name);
    void StaticAllocate();
    void Render();
    glm::mat4 CreateViewMatrix(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up);
    //void Run2D();
    void Run3D();
    void AddObject(const std::string name, std::shared_ptr<GraphicsObject>
        object);
    std::shared_ptr<Camera> GetCamera();
    static void OnMouseMove(GLFWwindow* window, double mouseX, double mouseY);
    Ray GetMouseRay(const glm::mat4& projection, const glm::mat4&
        view);
    std::shared_ptr<ObjectManager> GetObjManager();
    Ray GetMouseRayVar();
    bool GetLookWithMouse();
    void SetLookWithMouse(bool setting);
};

