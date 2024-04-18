#include "GraphicsEnvironment.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iterator> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>



void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	// making this right click for now so IMGui doesnt break
	std::shared_ptr<ObjectManager> objManager = GraphicsEnvironment::self->GetObjManager();
	std::string currSel = objManager->GetCurrPokeSel();

	// set up check on who poke's need the animation set to them

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		// perform animation here
		if (objManager->GetObject("attackBtn")->IsIntersectingWithRay(GraphicsEnvironment::self->GetMouseRayVar())) {
			// rotate left right left to simulate and attack rumble
			//bool isMoving = std::static_pointer_cast<AttackAnimation>(objManager->GetObject("poke1")->GetAnimation())->GetMove();
			std::static_pointer_cast<AttackAnimation>(objManager->GetObject(currSel)->GetAnimation())->SetMove(true);
		}

		// if interseting with catch, spawn a ball

		// if ball is spawned, clicking will throw it

		// if swap is clicked, will swap to a random poke in inventory?
	}
}


// poke swap code here
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// for 1
	std::shared_ptr<ObjectManager> objManager = GraphicsEnvironment::self->GetObjManager();
	std::string currSel = objManager->GetCurrPokeSel();
	std::string sel1 = objManager->GetPoke1Sel();
	std::string sel2 = objManager->GetPoke2Sel();;



	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		std::string placeholderSelName = currSel;
		glm::vec3 placeholderPos = static_cast<glm::vec3>(objManager->GetObject(currSel)->GetReferenceFrame()[3]);
		objManager->GetObject(currSel)->SetPosition(objManager->GetObject(sel1)->GetReferenceFrame()[3]);
		objManager->GetObject(sel1)->SetPosition(placeholderPos);
		objManager->SetCurrPokeSel(sel1);
		objManager->SetPoke1Sel(placeholderSelName);

		currSel = objManager->GetCurrPokeSel();

		std::shared_ptr<AttackAnimation> attackAnimation1 = std::make_shared<AttackAnimation>();

		attackAnimation1->SetObject(objManager->GetObject(currSel));
		objManager->GetObject(currSel)->SetAnimation(attackAnimation1);

		return;
		

		/*
		// this should actually change out the object to work correctly and not just change the position..?
		std::shared_ptr<GraphicsObject> placeholderObj = GraphicsEnvironment::self->GetObjManager()->GetObject("poke1");
		std::shared_ptr<GraphicsObject> newObj = GraphicsEnvironment::self->GetObjManager()->GetObject("poke1Side");

		GraphicsEnvironment::self->GetObjManager()->SetObject("poke1", newObj);
		GraphicsEnvironment::self->GetObjManager()->SetObject("poke1Side", placeholderObj);
		return;
		*/

	}
	// for 2
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		std::string placeholderSelName = currSel;
		glm::vec3 placeholderPos = static_cast<glm::vec3>(objManager->GetObject(currSel)->GetReferenceFrame()[3]);
		objManager->GetObject(currSel)->SetPosition(objManager->GetObject(sel2)->GetReferenceFrame()[3]);
		objManager->GetObject(sel2)->SetPosition(placeholderPos);
		objManager->SetCurrPokeSel(sel2);
		objManager->SetPoke2Sel(placeholderSelName);

		currSel = objManager->GetCurrPokeSel();

		std::shared_ptr<AttackAnimation> attackAnimation1 = std::make_shared<AttackAnimation>();

		attackAnimation1->SetObject(objManager->GetObject(currSel));
		objManager->GetObject(currSel)->SetAnimation(attackAnimation1);

		return;

		/*
		// this should actually change out the object to work correctly and not just change the position..?
		std::shared_ptr<GraphicsObject> placeholderObj = GraphicsEnvironment::self->GetObjManager()->GetObject("poke1");
		std::shared_ptr<GraphicsObject> newObj = GraphicsEnvironment::self->GetObjManager()->GetObject("poke2Side");

		GraphicsEnvironment::self->GetObjManager()->SetObject("poke1", newObj);
		GraphicsEnvironment::self->GetObjManager()->SetObject("poke2Side", placeholderObj);

		return;
		*/
	}
	// can do this for 1-6 for the player's inventory, or less if desired

	if (key == GLFW_KEY_F2 && action == GLFW_PRESS) {
		GraphicsEnvironment::self->SetLookWithMouse(!GraphicsEnvironment::self->GetLookWithMouse());
		return;
	}
}


GraphicsEnvironment* GraphicsEnvironment::self;

struct VertexData {
	glm::vec3 position, color;
	glm::vec2 tex;
};


GraphicsEnvironment::~GraphicsEnvironment()
{
    glfwTerminate();
}

GraphicsEnvironment::GraphicsEnvironment()
{
	window = nullptr;
	objManager = std::make_shared<ObjectManager>();
	camera = std::make_shared<Camera>();
	self = this;
}

GLFWwindow* GraphicsEnvironment::GetWindow()
{
    return window;
}

void GraphicsEnvironment::Init(unsigned int majorVersion, unsigned int minorVersion)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
}

bool GraphicsEnvironment::SetWindow(unsigned int width, unsigned int height, const std::string& title)
{
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (window == NULL) {
//		std::cout << "Failed to create GLFW window" << std::endl;
		Log("Failed to create GLFW window");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	return true;
}

bool GraphicsEnvironment::InitGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		//std::cout << "Failed to initialize GLAD" << std::endl;
		Log("Failed to initialize GLAD");
		return false;
	}
	return true;
}

void GraphicsEnvironment::SetUpGraphics()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// on mouse move callback
	glfwSetCursorPosCallback(window, OnMouseMove);
	glfwSetFramebufferSizeCallback(window, OnWindowSizeChanged);

	// attempting to add mouse button callback code..
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	// Setting up keyboard callbacks here for poke swap
	glfwSetKeyCallback(window, keyCallback);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430");

    // Cull back faces and use counter-clockwise winding of front faces
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

	glEnable(GL_MULTISAMPLE);
}

void GraphicsEnvironment::OnWindowSizeChanged(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void GraphicsEnvironment::CreateRenderer(const std::string& name, std::shared_ptr<Shader> shader)
{
	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(shader);
	rendererMap.emplace(name, renderer);
}

std::shared_ptr<Renderer> GraphicsEnvironment::GetRenderer(const std::string& name)
{
	return rendererMap[name];
}

void GraphicsEnvironment::StaticAllocate()
{
	for (const auto& [name, renderer] : rendererMap) {
		renderer->AllocateVertexBuffers();
	}

}

void GraphicsEnvironment::Render()
{
	for (const auto& [name, renderer] : rendererMap) {
		renderer->RenderScene(*camera); 
	}
	// might need to change this so that the current user poke is the only one rendered for the scene?
}

void GraphicsEnvironment::ProcessInput(GLFWwindow* window, double elapsedSeconds)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera->MoveForward(elapsedSeconds);
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera->MoveLeft(elapsedSeconds);
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera->MoveBackward(elapsedSeconds);
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera->MoveRight(elapsedSeconds);
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		camera->MoveUp(elapsedSeconds);
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		camera->MoveDown(elapsedSeconds);
		return;
	}
	/*
	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS) {
		lookWithMouse = !lookWithMouse;
		return;
	}
	*/
	/* changing this to a callback for now
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		glm::vec3 placeholderPos = static_cast<glm::vec3>(objManager->GetObject("poke1")->GetReferenceFrame()[3]);
		objManager->GetObject("poke1")->SetPosition(objManager->GetObject("poke1Side")->GetReferenceFrame()[3]);
		objManager->GetObject("poke1Side")->SetPosition(placeholderPos);

		return;
	}

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		glm::mat4 look(1.0f);
		look = glm::rotate(look, glm::radians(90.0f), { 0, 1, 0 });
		camera->SetLookFrame(look);
		camera->SetPosition(glm::vec3(30.0f, 5.5f, 0.0f));
		lookWithMouse = false;
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		glm::mat4 look(1.0f);
		look = glm::rotate(look, glm::radians(180.0f), { 0, 1, 0 });
		camera->SetLookFrame(look);
		camera->SetPosition(glm::vec3(0.0f, 5.5f, -20.0f));
		lookWithMouse = false;
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		glm::mat4 look(1.0f);
		look = glm::rotate(look, glm::radians(-90.0f), { 0, 1, 0 });
		camera->SetLookFrame(look);
		camera->SetPosition(glm::vec3(-30.0f, 5.5f, 0.0f));
		lookWithMouse = false;
		return;
	}
	*/

	// shifts to the side scene for testing
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
		camera->SetLookFrame(glm::mat4(1.0f));
		camera->SetPosition(glm::vec3(60.0f, 5.5f, 22.5f));
		lookWithMouse = false;
		return;
	}
	// sends camera back to initial scene for testing
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
		camera->SetLookFrame(glm::mat4(1.0f));
		camera->SetPosition(glm::vec3(0.0f, 5.5f, 22.5f));
		lookWithMouse = false;
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		// raycast and pickup item to use as ammo?
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		// starts the animation and a timer for how long it is pressed down
		// releasing mouse button will fire the item
		/*if (objManager->GetObject("globe")->IsIntersectingWithRay(mouseRayVar)) {
			bool isMoving = std::static_pointer_cast<SlidingAnimation>(objManager->GetObject("globe")->GetAnimation())->GetMove();
			std::static_pointer_cast<SlidingAnimation>(objManager->GetObject("globe")->GetAnimation())->SetMove(!isMoving);
		}*/

		/*
		if (objManager->GetObject("attackBtn")->IsIntersectingWithRay(mouseRayVar)) {
			// rotate left right left to simulate and attack rumble
			//bool isMoving = std::static_pointer_cast<AttackAnimation>(objManager->GetObject("poke1")->GetAnimation())->GetMove();
			std::static_pointer_cast<AttackAnimation>(objManager->GetObject("poke1")->GetAnimation())->SetMove(true);
		}
		*/

		
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		// reset back to normal animation
		// fires the item based on how long the left mouse button was held down
	}

}

glm::mat4 GraphicsEnvironment::CreateViewMatrix(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up)
{
	glm::vec3 right = glm::cross(direction, up);
	right = glm::normalize(right);

	glm::vec3 vUp = glm::cross(right, direction);
	vUp = glm::normalize(vUp);

	glm::mat4 view(1.0f);
	view[0] = glm::vec4(right, 0.0f);
	view[1] = glm::vec4(up, 0.0f);
	view[2] = glm::vec4(direction, 0.0f);
	view[3] = glm::vec4(position, 1.0f);
	return glm::inverse(view);
}

void GraphicsEnvironment::Run3D()
{	

	ImGuiIO& io = ImGui::GetIO();

	float cubeYAngle = 0;
    float cubeXAngle = 0;
	float cubeZAngle = 0;
	float left = -20.0f;
	float right = 20.0f;
	float bottom = -20.0f;
	float top = 20.0f;
	int width, height;

	//std::string message = result.message;

	float aspectRatio;
	float nearPlane = 1.0f;
	float farPlane = 200.0f;
	float fieldOfView = 60;

	//glm::vec3 cameraPosition(15.0f, 15.0f, 20.0f);
	glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
	//glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 referenceFrame(1.0f);
	glm::vec3 clearColor = { 0.2f, 0.3f, 0.3f };
	camera->SetPosition(glm::vec3(0.0f, 5.5f, 22.5f));


	//bool lookWithMouse = false;
	bool resetCameraPosition = false;
	double elapsedSeconds;
	Timer timer;
	bool correctGamma = false;
	glm::vec3 mouseRayStart{};
	glm::vec3 mouseRayDir{};
	GeometricPlane plane;
	Intersection intersection;
	glm::vec3 floorIntersectionPoint{};
	//float crateDefaultAmbient = objManager->GetObject("Crate")->GetMaterial().ambient
	// ;
	//float cubeDefaultAmbient = objManager->GetObject("cube")->GetMaterial().ambientIntensity;


	// add animation
	std::shared_ptr<RotateAnimation> rotateAnimation = std::make_shared<RotateAnimation>();
	// this could be repurposedfor the ball with a forward spin direction
	
	//rotateAnimation->SetObject(objManager->GetObject("Crate"));
	//objManager->GetObject("Crate")->SetAnimation(rotateAnimation);

	std::shared_ptr<SlidingAnimation> slideAnimation = std::make_shared<SlidingAnimation>();
	//slideAnimation->SetObject(objManager->GetObject("globe"));
	//objManager->GetObject("globe")->SetAnimation(slideAnimation);
	//slideAnimation->SetMove(true);
	
	// new attack animation here
	std::shared_ptr<AttackAnimation> attackAnimation1 = std::make_shared<AttackAnimation>();
	std::shared_ptr<AttackAnimation> attackAnimation2 = std::make_shared<AttackAnimation>();

	// this needs to be done for whatever the current selection is, or just all pokes not just poke1
	std::string currSel = objManager->GetCurrPokeSel();
	attackAnimation1->SetObject(objManager->GetObject("poke1"));
	objManager->GetObject("poke1")->SetAnimation(attackAnimation1);

	attackAnimation2->SetObject(objManager->GetObject("poke2"));
	objManager->GetObject("poke2")->SetAnimation(attackAnimation2);

	int prevCurrSelHp = objManager->GetObject(objManager->GetCurrPokeSel())->GetPoke()->GetCurrHp();
	int prevEnemySelHp = objManager->GetObject(objManager->GetCurrEnemy())->GetPoke()->GetCurrHp();



	// Set the behavior defaults for all objects
	for (auto& [name, object] : objManager->GetObjectMap()) {
		object->SetBehaviorDefaults();
	}

	while (!glfwWindowShouldClose(window)) {
		elapsedSeconds = timer.GetElapsedTimeInSeconds();
		ProcessInput(window, elapsedSeconds);
		glfwGetWindowSize(window, &width, &height);
		// set mouse parameters
		mouse.windowWidth = width;
		mouse.windowHeight = height;

		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//referenceFrame = glm::rotate(glm::mat4(1.0f), glm::radians(cubeYAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		//referenceFrame = glm::rotate(referenceFrame, glm::radians(cubeXAngle), glm::vec3(1.0f, 0.0f, 0.0f));
		//referenceFrame = glm::rotate(referenceFrame, glm::radians(cubeZAngle), glm::vec3(0.0f, 0.0f, 1.0f));

		//view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

		// mouse settings
		if (resetCameraPosition) {
			camera->SetLookFrame(glm::mat4(1.0f));
			camera->SetPosition(glm::vec4(0.0f, 5.5f, 25.0f, 1.0f));
			resetCameraPosition = false;
			lookWithMouse = false;
		}
		if (lookWithMouse) {
			camera->SetLookFrame(mouse.spherical.ToMat4());
		}

		// gamma correction
		if (correctGamma) {
			glEnable(GL_FRAMEBUFFER_SRGB);
		}
		else {
			glDisable(GL_FRAMEBUFFER_SRGB);
		}


		// set camera look frame to be mouse speherical
		//camera->SetLookFrame(self->mouse.spherical.ToMat4());

		view = camera->LookForward();
		//view = camera->LookAtTarget(glm::vec3(self->mouse.spherical.ToMat4()[3]));

		if (width >= height) {
			aspectRatio = width / (height * 1.0f);
		}
		else {
			aspectRatio = height / (width * 1.0f);
		}
		projection = glm::perspective(
			glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);

		// Update the objects in the scene
		// commenting this out so the animation works correctly
		/*
		for (auto& object : GetRenderer("renderer3d")->GetScene()->GetObjects()) {
			object->ResetOrientation();
			object->RotateLocalX(cubeXAngle);
			object->RotateLocalY(cubeYAngle);
			object->RotateLocalZ(cubeZAngle);
		}*/

		// if i want the buttons to move with the screen, can use this code
		/*
		glm::vec3 attackBtnPos = camera->GetPosition();
		attackBtnPos = { attackBtnPos.x - 0.5f, attackBtnPos.y -0.4f, attackBtnPos.z - 1.0f };
		objManager->GetObject("attackBtn")->SetPosition(attackBtnPos);

		glm::vec3 catchBtnPos = camera->GetPosition();
		catchBtnPos = { catchBtnPos.x + 0.5f, catchBtnPos.y - 0.4f, catchBtnPos.z - 1.0f };
		objManager->GetObject("catchBtn")->SetPosition(catchBtnPos);
		*/

		// pointing the pokes at the camera
		//objManager->GetObject("poke1")->PointAtTarget(camera->GetPosition());
		//objManager->GetObject("poke2")->PointAtTarget(camera->GetPosition());


		// this should work for all renderers now
		for (auto& [name, renderer] : rendererMap) {
			renderer->SetView(view);
			renderer->SetProjection(projection);
		}

		// before update set behavior params
		Ray mouseRay = GetMouseRay(projection, view);
		mouseRayVar = mouseRay;
		float offset = plane.GetIntersectionOffset(mouseRay);
		/*if (offset > 0) {
			floorIntersectionPoint = mouseRay.GetIntersectionPoint(offset);
			objManager->GetObject("pcLinesCylinder")->SetPosition({ (float)floorIntersectionPoint.x , (float)objManager->GetObject("pcLinesCylinder")->GetReferenceFrame()[3].y, (float)floorIntersectionPoint.z });
		}
		else
		{
			objManager->GetObject("pcLinesCylinder")->SetPosition({ 10.0f, 10.0f, 10.0f });
		}
		*/

		GraphicStructures::HighlightParams hp = { {}, &mouseRay };
		//objManager->GetObject("cube")->SetBehaviorParameters("highlight", hp);
		//objManager->GetObject("Crate")->SetBehaviorParameters("highlight", hp);
		//objManager->GetObject("globe")->SetBehaviorParameters("highlight", hp);
		objManager->GetObject("attackBtn")->SetBehaviorParameters("highlight", hp);
		objManager->GetObject("catchBtn")->SetBehaviorParameters("highlight", hp);

		

		if (std::static_pointer_cast<AttackAnimation>(objManager->GetObject(objManager->GetCurrPokeSel())->GetAnimation())->GetCompleted())
		{
			// lower enemy hp, start animation for enemy
			// lower enemy hp here
			objManager->GetObject(objManager->GetCurrEnemy())->GetPoke()->SetCurrHp(1);
			std::static_pointer_cast<AttackAnimation>(objManager->GetObject(objManager->GetCurrEnemy())->GetAnimation())->SetMove(true);
		}
		if (std::static_pointer_cast<AttackAnimation>(objManager->GetObject(objManager->GetCurrEnemy())->GetAnimation())->GetCompleted())
		{
			// lower currSel hp here
			objManager->GetObject(objManager->GetCurrPokeSel())->GetPoke()->SetCurrHp(1);
		}


		// could use dynamic buffers to shrink the size of the pokes when swapping and summoning


		// call update
		objManager->Update(elapsedSeconds);

		//
		if (objManager->GetObject(objManager->GetCurrPokeSel())->GetPoke()->GetCurrHp() != prevCurrSelHp)
		{
			int currHp = objManager->GetObject(objManager->GetCurrPokeSel())->GetPoke()->GetCurrHp();
			std::string currHpObject = "currSelHp" + std::to_string(currHp);
			glm::vec3 currHpPos = objManager->GetObject(currHpObject)->GetReferenceFrame()[3];


			//need to swap out prev with the Curr
			std::string prevHpObject = "currSelHp" + std::to_string(prevCurrSelHp);
			glm::vec3 prevHpPos = objManager->GetObject(prevHpObject)->GetReferenceFrame()[3];

			objManager->GetObject(prevHpObject)->SetPosition(currHpPos);
			objManager->GetObject(currHpObject)->SetPosition(prevHpPos);

			// update prev
			prevCurrSelHp = objManager->GetObject(objManager->GetCurrPokeSel())->GetPoke()->GetCurrHp();
		}
		if (objManager->GetObject(objManager->GetCurrEnemy())->GetPoke()->GetCurrHp() != prevEnemySelHp)
		{
			int currEnemyHp = objManager->GetObject(objManager->GetCurrEnemy())->GetPoke()->GetCurrHp();
			std::string currEnemyHpObject = "currEnemyHp" + std::to_string(currEnemyHp);
			glm::vec3 currEnemyHpPos = objManager->GetObject(currEnemyHpObject)->GetReferenceFrame()[3];


			//need to swap out prev with the Curr
			std::string prevEnemyHpObject = "currEnemyHp" + std::to_string(prevEnemySelHp);
			glm::vec3 prevEnemyHpPos = objManager->GetObject(prevEnemyHpObject)->GetReferenceFrame()[3];

			objManager->GetObject(prevEnemyHpObject)->SetPosition(currEnemyHpPos);
			objManager->GetObject(currEnemyHpObject)->SetPosition(prevEnemyHpPos);

			// update prev
			prevEnemySelHp = objManager->GetObject(objManager->GetCurrEnemy())->GetPoke()->GetCurrHp();
		}

		Render();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Poke Sim");
		//ImGui::Text(message.c_str());  no result object anymore?
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / io.Framerate, io.Framerate);
		ImGui::ColorEdit3("Background color", (float*)&clearColor.r);
		//ImGui::SliderFloat("X Angle", &cubeXAngle, 0, 360);  // commenting these out so the animation works correctly
		//ImGui::SliderFloat("Y Angle", &cubeYAngle, 0, 360);
		//ImGui::SliderFloat("Z Angle", &cubeZAngle, 0, 360);

		//ImGui::SliderFloat("Camera X", &cameraPosition.x, left, right);
		//ImGui::SliderFloat("Camera Y", &cameraPosition.y, bottom, top);
		//ImGui::SliderFloat("Camera Z", &cameraPosition.z, 20, 50);

		ImGui::SliderFloat("Global Intensity", &GetRenderer("renderer3d")->GetScene()->GetGlobalLight().intensity, 0, 1);
		ImGui::SliderFloat("Local Intensity", &GetRenderer("renderer3d")->GetScene()->GetLocalLight().intensity, 0, 1);
		//ImGui::SliderFloat("Local Attenuation ", &GetRenderer("renderer3d")->GetScene()->GetLocalLight().attenuationCoef, 0, 1);
		//ImGui::SliderFloat("Specular Cube", &objManager->GetObject("cube")->GetMaterial().specularIntensity, 0, 1);
		//ImGui::SliderFloat("Shininess Cube", &objManager->GetObject("cube")->GetMaterial().shininess, 0, 100);
		//ImGui::SliderFloat("Ambient Intensity Cube", &objManager->GetObject("cube")->GetMaterial().ambientIntensity, 0, 1);
		//ImGui::SliderFloat("Specular Crate", &objManager->GetObject("Crate")->GetMaterial().specularIntensity, 0, 1);
		//ImGui::SliderFloat("Shininess Crate", &objManager->GetObject("Crate")->GetMaterial().shininess, 0, 100);
		//ImGui::SliderFloat("Ambient Intensity Crate", &objManager->GetObject("Crate")->GetMaterial().ambientIntensity, 0, 1);
		//ImGui::SliderFloat("Specular Floor", &objManager->GetObject("floor")->GetMaterial().specularIntensity, 0, 1);
		//ImGui::SliderFloat("Shininess Floor", &objManager->GetObject("floor")->GetMaterial().shininess, 0, 100);
		//ImGui::SliderFloat("Ambient Intensity Floor", &objManager->GetObject("floor")->GetMaterial().ambientIntensity, 0, 1);

		// add a slider for box animation speed 
		//ImGui::SliderFloat("Animation Speed", &rotateAnimation->GetSpeed(), -360, 360);
		//ImGui::SliderFloat("Sliding Speed", &slideAnimation->GetSpeed(), 0, 120);
		//ImGui::Checkbox("Correct gamma", &correctGamma);
		//ImGui::SliderFloat("Local Light Position X", &GetRenderer("renderer3d")->GetScene()->GetLocalLight().position.x, -40, 40); 
		//ImGui::SliderFloat("Local Light Position Y", &GetRenderer("renderer3d")->GetScene()->GetLocalLight().position.y, -40, 40);
		//ImGui::SliderFloat("Local Light Position Z", &GetRenderer("renderer3d")->GetScene()->GetLocalLight().position.z, -40, 40); 
		ImGui::DragFloat3("Local light position", (float*)&GetRenderer("renderer3d")->GetScene()->GetLocalLight().position, 0.1f);
		ImGui::Checkbox("Use mouse to look", &this->lookWithMouse);
		ImGui::Checkbox("Reset camera position", &resetCameraPosition);
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();

}

void GraphicsEnvironment::AddObject(const std::string name, std::shared_ptr<GraphicsObject> object)
{
	objManager->SetObject(name, object);
}

std::shared_ptr<Camera> GraphicsEnvironment::GetCamera()
{
	return camera;
}

void GraphicsEnvironment::OnMouseMove(GLFWwindow* window, double mouseX, double mouseY)
{
	self->mouse.x = mouseX;
	self->mouse.y = mouseY;

	float xPercent = static_cast<float>(self->mouse.x / self->mouse.windowWidth);
	float yPercent = static_cast<float>(self->mouse.y / self->mouse.windowHeight);

	self->mouse.spherical.theta = 90.0f - (xPercent * 180); // left/right
	self->mouse.spherical.phi = 180.0f - (yPercent * 180); // up/down

	self->mouse.nsx = xPercent * 2.0 - 1.0;
	self->mouse.nsy = -(yPercent * 2.0 - 1.0);
}

Ray GraphicsEnvironment::GetMouseRay(const glm::mat4& projection, const glm::mat4& view)
{
	// Set up the ray
	Ray ray;
	glm::mat4 projInv = glm::inverse(projection);
	glm::mat4 viewInv = glm::inverse(view);
	glm::vec4 rayDirClip = glm::vec4(mouse.nsx, mouse.nsy, -1, 1);
	glm::vec4 rayDirEye = projInv * rayDirClip;
	rayDirEye.z = -1;
	rayDirEye.w = 0;
	ray.direction = glm::normalize(viewInv * rayDirEye);
	glm::vec4 rayStartClip = glm::vec4(mouse.nsx, mouse.nsy, 1, 1);
	glm::vec4 rayStartEye = projInv * rayStartClip;
	rayStartEye.z = 1;
	rayStartEye.w = 1;
	ray.startPoint = viewInv * rayStartEye;
	return ray;
}

std::shared_ptr<ObjectManager> GraphicsEnvironment::GetObjManager()
{
	return objManager;
}

Ray GraphicsEnvironment::GetMouseRayVar()
{
	return mouseRayVar;
}

bool GraphicsEnvironment::GetLookWithMouse()
{
	return lookWithMouse;
}

void GraphicsEnvironment::SetLookWithMouse(bool setting)
{
	lookWithMouse = setting;
}


