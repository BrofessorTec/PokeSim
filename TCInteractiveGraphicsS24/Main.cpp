#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VertexBuffer.h"
#include "GraphicsObject.h"
#include "Scene.h"
#include "Shader.h"
#include "Renderer.h"
#include "TextFile.h"
#include "Texture.h"
#include "GraphicsEnvironment.h"
#include "Generate.h"
#include "HighlightBehavior.h"
#include "Poke.h"


// inserting poke scene here
static void SetUpPokeBattler(std::shared_ptr<Shader>& shader3d,
	std::shared_ptr<Scene>& scene3d, std::shared_ptr<GraphicsEnvironment>& graphicsEnviron, std::unordered_map<int, std::shared_ptr<Poke>>& pokeMap)
{

	std::shared_ptr<TextFile> vertFile = std::make_shared<TextFile>();
	// relative path 
	vertFile->ReadFile("lighting.vert.glsl");

	std::shared_ptr<TextFile> fragFile = std::make_shared<TextFile>();
	// relative path 
	fragFile->ReadFile("lighting.frag.glsl");


	shader3d = std::make_shared<Shader>(vertFile->GetString(), fragFile->GetString());

	shader3d->AddUniform("projection");
	shader3d->AddUniform("world");
	shader3d->AddUniform("view");
	shader3d->AddUniform("materialAmbientIntensity");
	shader3d->AddUniform("materialSpecularIntensity");
	shader3d->AddUniform("materialShininess");
	shader3d->AddUniform("globalLightPosition");
	shader3d->AddUniform("globalLightColor");
	shader3d->AddUniform("globalLightIntensity");
	shader3d->AddUniform("globalLightAttenuationCoef");
	shader3d->AddUniform("localLightPosition");
	shader3d->AddUniform("localLightColor");
	shader3d->AddUniform("localLightIntensity");
	shader3d->AddUniform("localLightAttenuationCoef");
	shader3d->AddUniform("viewPosition");
	shader3d->AddUniform("texUnit");

	unsigned int shaderProgram = shader3d->GetShaderProgram();
	scene3d = std::make_shared<Scene>();

	// Get the uniform locations
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	unsigned int worldLoc = glGetUniformLocation(shaderProgram, "world");

	// new Floor code here
	std::shared_ptr<Texture> texture3dFloor = std::make_shared<Texture>();

	texture3dFloor->LoadTextureDataFromFile("..\\3rdparty\\Poke\\floor.png");


	std::shared_ptr<GraphicsObject> graphicsObject3dFloor = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferFloor = Generate::XZPlaneNorm(30, 40, glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f });

	bufferFloor->AddVertexAttribute("position", 0, 3, 0);
	bufferFloor->AddVertexAttribute("vertexColor", 1, 4, 3);
	bufferFloor->AddVertexAttribute("normal", 2, 3, 7);
	bufferFloor->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	texture3dFloor->SetWrapS(GL_REPEAT);
	texture3dFloor->SetWrapT(GL_REPEAT);
	texture3dFloor->SetMagFilter(GL_NEAREST);
	texture3dFloor->SetMinFilter(GL_NEAREST);

	bufferFloor->SetTexture(texture3dFloor);

	graphicsObject3dFloor->SetVertexBuffer(bufferFloor);

	graphicsObject3dFloor->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));  //can adjust position if needed
	graphicsObject3dFloor->RotateLocalY(90.0f);
	scene3d->AddObject(graphicsObject3dFloor);

	// new poke code here

	std::shared_ptr<Texture> poke1Tex = std::make_shared<Texture>();
	// texture sprites from https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/6.png
	// wiki files also look nice if they can work, https://pokemongo.fandom.com/wiki/Venusaur?file=Venusaur_female.png

	float poke1Width = 10.0f;
	float poke1Height = 10.0f;

	std::shared_ptr<GraphicsObject> poke1 = std::make_shared<GraphicsObject>();
	std::shared_ptr<Poke> poke1Object = pokeMap[3];
	poke1Tex->LoadTextureDataFromFile(poke1Object->GetUrl());
	poke1->SetPoke(poke1Object);
	std::shared_ptr<VertexBuffer> bufferPoke1 = Generate::XYPlaneNormReverse(poke1Width, poke1Height);

	bufferPoke1->AddVertexAttribute("position", 0, 3, 0);
	bufferPoke1->AddVertexAttribute("vertexColor", 1, 4, 3);
	bufferPoke1->AddVertexAttribute("normal", 2, 3, 7);
	bufferPoke1->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	//poke1Tex->SetWrapS(GL_REPEAT);
	//poke1Tex->SetWrapT(GL_REPEAT);
	poke1Tex->SetMagFilter(GL_NEAREST);
	poke1Tex->SetMinFilter(GL_NEAREST);

	bufferPoke1->SetTexture(poke1Tex);

	poke1->SetVertexBuffer(bufferPoke1);

	//poke1->CreateBoundingBox(poke1Width, poke1Height, 0.5f);
	// this probably doesnt need a bounding box


	//poke 2 here
	std::shared_ptr<Texture> poke2Tex = std::make_shared<Texture>();
	std::string poke2Dex = "6";

	float poke2Width = 10.0f;
	float poke2Height = 10.0f;

	std::shared_ptr<GraphicsObject> poke2 = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferPoke2 = Generate::XYPlaneNorm(poke2Width, poke2Height);
	std::shared_ptr<Poke> poke2Object = pokeMap[6];
	poke2Tex->LoadTextureDataFromFile(poke2Object->GetUrl());
	poke2->SetPoke(poke2Object);

	bufferPoke2->AddVertexAttribute("position", 0, 3, 0);
	bufferPoke2->AddVertexAttribute("vertexColor", 1, 4, 3);
	bufferPoke2->AddVertexAttribute("normal", 2, 3, 7);
	bufferPoke2->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	poke2Tex->SetWrapS(GL_REPEAT);
	poke2Tex->SetWrapT(GL_REPEAT);
	poke2Tex->SetMagFilter(GL_NEAREST);
	poke2Tex->SetMinFilter(GL_NEAREST);

	bufferPoke2->SetTexture(poke2Tex);

	poke2->SetVertexBuffer(bufferPoke2);

	poke2->CreateBoundingBox(poke2Width, poke2Height, 0.5f);
	// this should probably be a sphere bounding box for detection of overlap with the ball


	//attack button here
	std::shared_ptr<Texture> attackBtnTex = std::make_shared<Texture>();
	std::string attackBtnUrl = "Attack";
	std::string url3 = "..\\3rdparty\\Poke\\" + attackBtnUrl;
	url3 += ".png";
	attackBtnTex->LoadTextureDataFromFile(url3);

	float attackBtnWidth = 2.0f;
	float attackBtnHeight = 1.5f;

	std::shared_ptr<GraphicsObject> attackBtn = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferAttackBtn = Generate::XYPlaneNorm(attackBtnWidth, attackBtnHeight);

	bufferAttackBtn->AddVertexAttribute("position", 0, 3, 0);
	bufferAttackBtn->AddVertexAttribute("vertexColor", 1, 4, 3);
	bufferAttackBtn->AddVertexAttribute("normal", 2, 3, 7);
	bufferAttackBtn->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	attackBtnTex->SetWrapS(GL_REPEAT);
	attackBtnTex->SetWrapT(GL_REPEAT);
	attackBtnTex->SetMagFilter(GL_NEAREST);
	attackBtnTex->SetMinFilter(GL_NEAREST);

	bufferAttackBtn->SetTexture(attackBtnTex);

	attackBtn->SetVertexBuffer(bufferAttackBtn);

	attackBtn->CreateBoundingBox(attackBtnWidth, attackBtnHeight, 0.5f);

	// adding highlight behavior here

	std::shared_ptr<HighlightBehavior> attackBtnHighlight = std::make_shared<HighlightBehavior>();
	attackBtnHighlight->SetObject(attackBtn);
	attackBtn->AddBehavior("highlight", attackBtnHighlight);


	//catch button here
	std::shared_ptr<Texture> catchBtnTex = std::make_shared<Texture>();
	std::string catchBtnUrl = "Catch";
	std::string url4 = "..\\3rdparty\\Poke\\" + catchBtnUrl;
	url4 += ".png";
	catchBtnTex->LoadTextureDataFromFile(url4);

	float catchBtnWidth = 2.0f;
	float catchBtnHeight = 1.5f;

	std::shared_ptr<GraphicsObject> catchBtn = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferCatchBtn = Generate::XYPlaneNorm(catchBtnWidth, catchBtnHeight);

	bufferCatchBtn->AddVertexAttribute("position", 0, 3, 0);
	bufferCatchBtn->AddVertexAttribute("vertexColor", 1, 4, 3);
	bufferCatchBtn->AddVertexAttribute("normal", 2, 3, 7);
	bufferCatchBtn->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	catchBtnTex->SetWrapS(GL_REPEAT);
	catchBtnTex->SetWrapT(GL_REPEAT);
	catchBtnTex->SetMagFilter(GL_NEAREST);
	catchBtnTex->SetMinFilter(GL_NEAREST);

	bufferCatchBtn->SetTexture(catchBtnTex);

	catchBtn->SetVertexBuffer(bufferCatchBtn);

	catchBtn->CreateBoundingBox(catchBtnWidth, catchBtnHeight, 0.5f);

	// adding highlight behavior here

	std::shared_ptr<HighlightBehavior> catchBtnHighlight = std::make_shared<HighlightBehavior>();
	catchBtnHighlight->SetObject(catchBtn);
	catchBtn->AddBehavior("highlight", catchBtnHighlight);


	poke1->SetPosition(glm::vec3(-7.5f, 4.0f, 3.0f));  //can adjust position if needed
	scene3d->AddObject(poke1);

	poke2->SetPosition(glm::vec3(7.5f, 4.0f, 0.0f));  //can adjust position if needed
	scene3d->AddObject(poke2);

	attackBtn->SetPosition(glm::vec3(-4.0f, 1.0f, 10.0f));
	scene3d->AddObject(attackBtn);
	catchBtn->SetPosition(glm::vec3(4.0f, 1.0f, 10.0f));
	scene3d->AddObject(catchBtn);

	//testing to check lighting here
	// new poke code here

	std::shared_ptr<Texture> poke1SideTex = std::make_shared<Texture>();
	// texture sprites from https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/3.png
	// wiki files also look nice if they can work, https://pokemongo.fandom.com/wiki/Venusaur?file=Venusaur_female.png
	std::string poke1SideDex = "149";

	float poke1SideWidth = 10.0f;
	float poke1SideHeight = 10.0f;

	std::shared_ptr<GraphicsObject> poke1Side = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferSidePoke1 = Generate::XYPlaneNormReverse(poke1SideWidth, poke1SideHeight);
	std::shared_ptr<Poke> poke1SideObject = pokeMap[149];
	poke1SideTex->LoadTextureDataFromFile(poke1SideObject->GetUrl());
	poke1Side->SetPoke(poke1SideObject);

	bufferSidePoke1->AddVertexAttribute("position", 0, 3, 0);
	bufferSidePoke1->AddVertexAttribute("vertexColor", 1, 4, 3);
	bufferSidePoke1->AddVertexAttribute("normal", 2, 3, 7);
	bufferSidePoke1->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	//poke1Tex->SetWrapS(GL_REPEAT);
	//poke1Tex->SetWrapT(GL_REPEAT);
	poke1SideTex->SetMagFilter(GL_NEAREST);
	poke1SideTex->SetMinFilter(GL_NEAREST);

	bufferSidePoke1->SetTexture(poke1SideTex);

	poke1Side->SetVertexBuffer(bufferSidePoke1);

	//poke1Side->CreateBoundingBox(poke1SideWidth, poke1SideHeight, 0.5f);


	//poke 2 here
	std::shared_ptr<Texture> poke2SideTex = std::make_shared<Texture>();
	std::string poke2SideDex = "150";

	float poke2SideWidth = 10.0f;
	float poke2SideHeight = 10.0f;

	std::shared_ptr<GraphicsObject> poke2Side = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferSidePoke2 = Generate::XYPlaneNormReverse(poke2SideWidth, poke2SideHeight);
	std::shared_ptr<Poke> poke2SideObject = pokeMap[150];
	poke2SideTex->LoadTextureDataFromFile(poke2SideObject->GetUrl());
	poke2Side->SetPoke(poke2SideObject);

	bufferSidePoke2->AddVertexAttribute("position", 0, 3, 0);
	bufferSidePoke2->AddVertexAttribute("vertexColor", 1, 4, 3);
	bufferSidePoke2->AddVertexAttribute("normal", 2, 3, 7);
	bufferSidePoke2->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	poke2SideTex->SetWrapS(GL_REPEAT);
	poke2SideTex->SetWrapT(GL_REPEAT);
	poke2SideTex->SetMagFilter(GL_NEAREST);
	poke2SideTex->SetMinFilter(GL_NEAREST);

	bufferSidePoke2->SetTexture(poke2SideTex);

	poke2Side->SetVertexBuffer(bufferSidePoke2);

	//poke2Side->CreateBoundingBox(poke2SideWidth, poke2SideHeight, 0.5f);


	poke1Side->SetPosition(glm::vec3(-7.5f + 60.0f, 4.0f, 0.0f));  //can adjust position if needed
	scene3d->AddObject(poke1Side);

	poke2Side->SetPosition(glm::vec3(7.5f + 60.0f, 4.0f, 0.0f));  //can adjust position if needed
	scene3d->AddObject(poke2Side);

	//graphicsEnviron->AddObject("background", background);
	graphicsEnviron->AddObject("poke1Side", poke1Side);
	graphicsEnviron->AddObject("poke2Side", poke2Side);
	

	graphicsEnviron->AddObject("floor", graphicsObject3dFloor);
	//graphicsEnviron->AddObject("background", background);
	graphicsEnviron->AddObject("poke1", poke1);
	graphicsEnviron->AddObject("poke2", poke2);
	graphicsEnviron->AddObject("attackBtn", attackBtn);
	graphicsEnviron->AddObject("catchBtn", catchBtn);


}
// poke scene ends here

// new backgrounds scene here
static void SetUpBackgroundScene(std::shared_ptr<Shader>&
	backgroundShader, std::shared_ptr<Scene>& backgroundScene, std::shared_ptr<GraphicsEnvironment>& graphicsEnviron)
{
	//unsigned int shaderProgram;
	std::shared_ptr<TextFile> vertFile = std::make_shared<TextFile>();
	// relative path 
	vertFile->ReadFile("texture.vert.glsl");

	// relative path
	std::shared_ptr<TextFile> fragFile = std::make_shared<TextFile>();
	fragFile->ReadFile("texture.frag.glsl");

	backgroundShader = std::make_shared<Shader>(vertFile->GetString(), fragFile->GetString());

	backgroundShader->AddUniform("projection");
	backgroundShader->AddUniform("world");
	backgroundShader->AddUniform("view");

	// new textured object to scene
	backgroundScene = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> background = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> backgroundBuffer = Generate::XYPlane(180, 90);

	backgroundBuffer->AddVertexAttribute("position", 0, 3, 0);
	backgroundBuffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	backgroundBuffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> backgroundTex = std::make_shared<Texture>();
	backgroundTex->LoadTextureDataFromFile("..\\3rdparty\\Background.jpg");

	// adjusting the texture settings here
	backgroundTex->SetWrapS(GL_MIRRORED_REPEAT);
	backgroundTex->SetWrapT(GL_MIRRORED_REPEAT);
	backgroundTex->SetMagFilter(GL_NEAREST);
	backgroundTex->SetMinFilter(GL_NEAREST);


	backgroundBuffer->SetTexture(backgroundTex);
	background->SetVertexBuffer(backgroundBuffer);
	background->SetPosition(glm::vec3(0.0f, 30.0f, -75.0f));

	backgroundScene->AddObject(background);
	graphicsEnviron->AddObject("background", background);

	// new sky texture
	std::shared_ptr<GraphicsObject> sky = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> skyBuffer = Generate::XYPlane(180, 90);

	skyBuffer->AddVertexAttribute("position", 0, 3, 0);
	skyBuffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	skyBuffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> skyTex = std::make_shared<Texture>();
	skyTex->LoadTextureDataFromFile("..\\3rdparty\\Sky.jpg");

	// adjusting the texture settings here
	skyTex->SetWrapS(GL_MIRRORED_REPEAT);
	skyTex->SetWrapT(GL_MIRRORED_REPEAT);
	skyTex->SetMagFilter(GL_NEAREST);
	skyTex->SetMinFilter(GL_NEAREST);


	skyBuffer->SetTexture(skyTex);
	sky->SetVertexBuffer(skyBuffer);
	sky->SetPosition(glm::vec3(0.0f, 90.0f, -76.0f));

	backgroundScene->AddObject(sky);
	graphicsEnviron->AddObject("sky", sky);

	// setting dirt floor here
	std::shared_ptr<GraphicsObject> floor = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> floorBuffer = Generate::XZPlane(180, 180);

	floorBuffer->AddVertexAttribute("position", 0, 3, 0);
	floorBuffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	floorBuffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> floorTex = std::make_shared<Texture>();
	floorTex->LoadTextureDataFromFile("..\\3rdparty\\Ground.jpg");

	// adjusting the texture settings here
	floorTex->SetWrapS(GL_MIRRORED_REPEAT);
	floorTex->SetWrapT(GL_MIRRORED_REPEAT);
	floorTex->SetMagFilter(GL_NEAREST);
	floorTex->SetMinFilter(GL_NEAREST);


	floorBuffer->SetTexture(floorTex);
	floor->SetVertexBuffer(floorBuffer);
	floor->SetPosition(glm::vec3(0.0f, -0.1f, 30.0f));

	backgroundScene->AddObject(floor);
	graphicsEnviron->AddObject("floor", floor);


	//std::shared_ptr<ObjectManager> objManager = graphicsEnviron->GetObjManager();
	//std::string currSel = objManager->GetCurrPokeSel();
	//glm::vec4 currPos = objManager->GetObject(currSel)->GetReferenceFrame()[3];


	// new curr hp textures
	// maybe this should just be the number
	std::shared_ptr<GraphicsObject> currSelHp10 = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> currSelHp10Buffer = Generate::XYPlane(3, 2);

	currSelHp10Buffer->AddVertexAttribute("position", 0, 3, 0);
	currSelHp10Buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	currSelHp10Buffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> currSelHp10Tex = std::make_shared<Texture>();
	currSelHp10Tex->LoadTextureDataFromFile("..\\3rdparty\\Poke\\HP10.png");

	// adjusting the texture settings here
	currSelHp10Tex->SetWrapS(GL_MIRRORED_REPEAT);
	currSelHp10Tex->SetWrapT(GL_MIRRORED_REPEAT);
	currSelHp10Tex->SetMagFilter(GL_NEAREST);
	currSelHp10Tex->SetMinFilter(GL_NEAREST);


	currSelHp10Buffer->SetTexture(currSelHp10Tex);
	currSelHp10->SetVertexBuffer(currSelHp10Buffer);

	currSelHp10->SetPosition(glm::vec3(-7.5f, 10.0f, 3.0f));

	backgroundScene->AddObject(currSelHp10);
	graphicsEnviron->AddObject("currSelHp10", currSelHp10);

	// 9
	std::shared_ptr<GraphicsObject> currSelHp9 = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> currSelHp9Buffer = Generate::XYPlane(3, 2);

	currSelHp9Buffer->AddVertexAttribute("position", 0, 3, 0);
	currSelHp9Buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	currSelHp9Buffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> currSelHp9Tex = std::make_shared<Texture>();
	currSelHp9Tex->LoadTextureDataFromFile("..\\3rdparty\\Poke\\HP9.png");

	// adjusting the texture settings here
	currSelHp9Tex->SetWrapS(GL_MIRRORED_REPEAT);
	currSelHp9Tex->SetWrapT(GL_MIRRORED_REPEAT);
	currSelHp9Tex->SetMagFilter(GL_NEAREST);
	currSelHp9Tex->SetMinFilter(GL_NEAREST);


	currSelHp9Buffer->SetTexture(currSelHp9Tex);
	currSelHp9->SetVertexBuffer(currSelHp9Buffer);

	currSelHp9->SetPosition(glm::vec3(-50.5f, 10.0f, 3.0f));

	backgroundScene->AddObject(currSelHp9);
	graphicsEnviron->AddObject("currSelHp9", currSelHp9);


	// 8
	std::shared_ptr<GraphicsObject> currSelHp8 = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> currSelHp8Buffer = Generate::XYPlane(3, 2);

	currSelHp8Buffer->AddVertexAttribute("position", 0, 3, 0);
	currSelHp8Buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	currSelHp8Buffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> currSelHp8Tex = std::make_shared<Texture>();
	currSelHp8Tex->LoadTextureDataFromFile("..\\3rdparty\\Poke\\HP8.png");

	// adjusting the texture settings here
	currSelHp8Tex->SetWrapS(GL_MIRRORED_REPEAT);
	currSelHp8Tex->SetWrapT(GL_MIRRORED_REPEAT);
	currSelHp8Tex->SetMagFilter(GL_NEAREST);
	currSelHp8Tex->SetMinFilter(GL_NEAREST);


	currSelHp8Buffer->SetTexture(currSelHp8Tex);
	currSelHp8->SetVertexBuffer(currSelHp8Buffer);

	currSelHp8->SetPosition(glm::vec3(-50.5f, 10.0f, 3.0f));

	backgroundScene->AddObject(currSelHp8);
	graphicsEnviron->AddObject("currSelHp8", currSelHp8);

	// 7
	std::shared_ptr<GraphicsObject> currSelHp7 = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> currSelHp7Buffer = Generate::XYPlane(3, 2);

	currSelHp7Buffer->AddVertexAttribute("position", 0, 3, 0);
	currSelHp7Buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	currSelHp7Buffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> currSelHp7Tex = std::make_shared<Texture>();
	currSelHp7Tex->LoadTextureDataFromFile("..\\3rdparty\\Poke\\HP7.png");

	// adjusting the texture settings here
	currSelHp7Tex->SetWrapS(GL_MIRRORED_REPEAT);
	currSelHp7Tex->SetWrapT(GL_MIRRORED_REPEAT);
	currSelHp7Tex->SetMagFilter(GL_NEAREST);
	currSelHp7Tex->SetMinFilter(GL_NEAREST);


	currSelHp7Buffer->SetTexture(currSelHp7Tex);
	currSelHp7->SetVertexBuffer(currSelHp7Buffer);

	currSelHp7->SetPosition(glm::vec3(-50.5f, 10.0f, 3.0f));

	backgroundScene->AddObject(currSelHp7);
	graphicsEnviron->AddObject("currSelHp7", currSelHp7);


	// 6
	std::shared_ptr<GraphicsObject> currSelHp6 = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> currSelHp6Buffer = Generate::XYPlane(3, 2);

	currSelHp6Buffer->AddVertexAttribute("position", 0, 3, 0);
	currSelHp6Buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	currSelHp6Buffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> currSelHp6Tex = std::make_shared<Texture>();
	currSelHp6Tex->LoadTextureDataFromFile("..\\3rdparty\\Poke\\HP6.png");

	// adjusting the texture settings here
	currSelHp6Tex->SetWrapS(GL_MIRRORED_REPEAT);
	currSelHp6Tex->SetWrapT(GL_MIRRORED_REPEAT);
	currSelHp6Tex->SetMagFilter(GL_NEAREST);
	currSelHp6Tex->SetMinFilter(GL_NEAREST);


	currSelHp6Buffer->SetTexture(currSelHp6Tex);
	currSelHp6->SetVertexBuffer(currSelHp6Buffer);

	currSelHp6->SetPosition(glm::vec3(-50.5f, 10.0f, 3.0f));

	backgroundScene->AddObject(currSelHp6);
	graphicsEnviron->AddObject("currSelHp6", currSelHp6);

	// 5
	std::shared_ptr<GraphicsObject> currSelHp5 = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> currSelHp5Buffer = Generate::XYPlane(3, 2);

	currSelHp5Buffer->AddVertexAttribute("position", 0, 3, 0);
	currSelHp5Buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	currSelHp5Buffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> currSelHp5Tex = std::make_shared<Texture>();
	currSelHp5Tex->LoadTextureDataFromFile("..\\3rdparty\\Poke\\HP5.png");

	// adjusting the texture settings here
	currSelHp5Tex->SetWrapS(GL_MIRRORED_REPEAT);
	currSelHp5Tex->SetWrapT(GL_MIRRORED_REPEAT);
	currSelHp5Tex->SetMagFilter(GL_NEAREST);
	currSelHp5Tex->SetMinFilter(GL_NEAREST);


	currSelHp5Buffer->SetTexture(currSelHp5Tex);
	currSelHp5->SetVertexBuffer(currSelHp5Buffer);

	currSelHp5->SetPosition(glm::vec3(-50.5f, 10.0f, 3.0f));

	backgroundScene->AddObject(currSelHp5);
	graphicsEnviron->AddObject("currSelHp5", currSelHp5);

	// 4
	std::shared_ptr<GraphicsObject> currSelHp4 = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> currSelHp4Buffer = Generate::XYPlane(3, 2);

	currSelHp4Buffer->AddVertexAttribute("position", 0, 3, 0);
	currSelHp4Buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	currSelHp4Buffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> currSelHp4Tex = std::make_shared<Texture>();
	currSelHp4Tex->LoadTextureDataFromFile("..\\3rdparty\\Poke\\HP4.png");

	// adjusting the texture settings here
	currSelHp4Tex->SetWrapS(GL_MIRRORED_REPEAT);
	currSelHp4Tex->SetWrapT(GL_MIRRORED_REPEAT);
	currSelHp4Tex->SetMagFilter(GL_NEAREST);
	currSelHp4Tex->SetMinFilter(GL_NEAREST);


	currSelHp4Buffer->SetTexture(currSelHp4Tex);
	currSelHp4->SetVertexBuffer(currSelHp4Buffer);

	currSelHp4->SetPosition(glm::vec3(-50.5f, 10.0f, 3.0f));

	backgroundScene->AddObject(currSelHp4);
	graphicsEnviron->AddObject("currSelHp4", currSelHp4);


	// curr enemy hp
	std::shared_ptr<GraphicsObject> currEnemyHp10 = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> currEnemyHp10Buffer = Generate::XYPlane(3, 2);

	currEnemyHp10Buffer->AddVertexAttribute("position", 0, 3, 0);
	currEnemyHp10Buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	currEnemyHp10Buffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> currEnemyHp10Tex = std::make_shared<Texture>();
	currEnemyHp10Tex->LoadTextureDataFromFile("..\\3rdparty\\Poke\\HP10.png");

	// adjusting the texture settings here
	currEnemyHp10Tex->SetWrapS(GL_MIRRORED_REPEAT);
	currEnemyHp10Tex->SetWrapT(GL_MIRRORED_REPEAT);
	currEnemyHp10Tex->SetMagFilter(GL_NEAREST);
	currEnemyHp10Tex->SetMinFilter(GL_NEAREST);


	currEnemyHp10Buffer->SetTexture(currEnemyHp10Tex);
	currEnemyHp10->SetVertexBuffer(currEnemyHp10Buffer);

	currEnemyHp10->SetPosition(glm::vec3(7.5f, 10.0f, 0.0f));

	backgroundScene->AddObject(currEnemyHp10);
	graphicsEnviron->AddObject("currEnemyHp10", currEnemyHp10);

	// 9
	std::shared_ptr<GraphicsObject> currEnemyHp9 = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> currEnemyHp9Buffer = Generate::XYPlane(3, 2);

	currEnemyHp9Buffer->AddVertexAttribute("position", 0, 3, 0);
	currEnemyHp9Buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	currEnemyHp9Buffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> currEnemyHp9Tex = std::make_shared<Texture>();
	currEnemyHp9Tex->LoadTextureDataFromFile("..\\3rdparty\\Poke\\HP9.png");

	// adjusting the texture settings here
	currEnemyHp9Tex->SetWrapS(GL_MIRRORED_REPEAT);
	currEnemyHp9Tex->SetWrapT(GL_MIRRORED_REPEAT);
	currEnemyHp9Tex->SetMagFilter(GL_NEAREST);
	currEnemyHp9Tex->SetMinFilter(GL_NEAREST);


	currEnemyHp9Buffer->SetTexture(currEnemyHp9Tex);
	currEnemyHp9->SetVertexBuffer(currEnemyHp9Buffer);

	currEnemyHp9->SetPosition(glm::vec3(-50.5f, 10.0f, 0.0f));

	backgroundScene->AddObject(currEnemyHp9);
	graphicsEnviron->AddObject("currEnemyHp9", currEnemyHp9);


	// 8
	std::shared_ptr<GraphicsObject> currEnemyHp8 = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> currEnemyHp8Buffer = Generate::XYPlane(3, 2);

	currEnemyHp8Buffer->AddVertexAttribute("position", 0, 3, 0);
	currEnemyHp8Buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	currEnemyHp8Buffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> currEnemyHp8Tex = std::make_shared<Texture>();
	currEnemyHp8Tex->LoadTextureDataFromFile("..\\3rdparty\\Poke\\HP8.png");

	// adjusting the texture settings here
	currEnemyHp8Tex->SetWrapS(GL_MIRRORED_REPEAT);
	currEnemyHp8Tex->SetWrapT(GL_MIRRORED_REPEAT);
	currEnemyHp8Tex->SetMagFilter(GL_NEAREST);
	currEnemyHp8Tex->SetMinFilter(GL_NEAREST);


	currEnemyHp8Buffer->SetTexture(currEnemyHp8Tex);
	currEnemyHp8->SetVertexBuffer(currEnemyHp8Buffer);

	currEnemyHp8->SetPosition(glm::vec3(-50.5f, 10.0f, 0.0f));

	backgroundScene->AddObject(currEnemyHp8);
	graphicsEnviron->AddObject("currEnemyHp8", currEnemyHp8);


	// 7
	std::shared_ptr<GraphicsObject> currEnemyHp7 = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> currEnemyHp7Buffer = Generate::XYPlane(3, 2);

	currEnemyHp7Buffer->AddVertexAttribute("position", 0, 3, 0);
	currEnemyHp7Buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	currEnemyHp7Buffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> currEnemyHp7Tex = std::make_shared<Texture>();
	currEnemyHp7Tex->LoadTextureDataFromFile("..\\3rdparty\\Poke\\HP7.png");

	// adjusting the texture settings here
	currEnemyHp7Tex->SetWrapS(GL_MIRRORED_REPEAT);
	currEnemyHp7Tex->SetWrapT(GL_MIRRORED_REPEAT);
	currEnemyHp7Tex->SetMagFilter(GL_NEAREST);
	currEnemyHp7Tex->SetMinFilter(GL_NEAREST);


	currEnemyHp7Buffer->SetTexture(currEnemyHp7Tex);
	currEnemyHp7->SetVertexBuffer(currEnemyHp7Buffer);

	currEnemyHp7->SetPosition(glm::vec3(-50.5f, 10.0f, 3.0f));

	backgroundScene->AddObject(currEnemyHp7);
	graphicsEnviron->AddObject("currEnemyHp7", currEnemyHp7);


	// 6
	std::shared_ptr<GraphicsObject> currEnemyHp6 = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> currEnemyHp6Buffer = Generate::XYPlane(3, 2);

	currEnemyHp6Buffer->AddVertexAttribute("position", 0, 3, 0);
	currEnemyHp6Buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	currEnemyHp6Buffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> currEnemyHp6Tex = std::make_shared<Texture>();
	currEnemyHp6Tex->LoadTextureDataFromFile("..\\3rdparty\\Poke\\HP6.png");

	// adjusting the texture settings here
	currEnemyHp6Tex->SetWrapS(GL_MIRRORED_REPEAT);
	currEnemyHp6Tex->SetWrapT(GL_MIRRORED_REPEAT);
	currEnemyHp6Tex->SetMagFilter(GL_NEAREST);
	currEnemyHp6Tex->SetMinFilter(GL_NEAREST);


	currEnemyHp6Buffer->SetTexture(currEnemyHp6Tex);
	currEnemyHp6->SetVertexBuffer(currEnemyHp6Buffer);

	currEnemyHp6->SetPosition(glm::vec3(-50.5f, 10.0f, 3.0f));

	backgroundScene->AddObject(currEnemyHp6);
	graphicsEnviron->AddObject("currEnemyHp6", currEnemyHp6);

	// 5
	std::shared_ptr<GraphicsObject> currEnemyHp5 = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> currEnemyHp5Buffer = Generate::XYPlane(3, 2);

	currEnemyHp5Buffer->AddVertexAttribute("position", 0, 3, 0);
	currEnemyHp5Buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	currEnemyHp5Buffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> currEnemyHp5Tex = std::make_shared<Texture>();
	currEnemyHp5Tex->LoadTextureDataFromFile("..\\3rdparty\\Poke\\HP5.png");

	// adjusting the texture settings here
	currEnemyHp5Tex->SetWrapS(GL_MIRRORED_REPEAT);
	currEnemyHp5Tex->SetWrapT(GL_MIRRORED_REPEAT);
	currEnemyHp5Tex->SetMagFilter(GL_NEAREST);
	currEnemyHp5Tex->SetMinFilter(GL_NEAREST);


	currEnemyHp5Buffer->SetTexture(currEnemyHp5Tex);
	currEnemyHp5->SetVertexBuffer(currEnemyHp5Buffer);

	currEnemyHp5->SetPosition(glm::vec3(-50.5f, 10.0f, 3.0f));

	backgroundScene->AddObject(currEnemyHp5);
	graphicsEnviron->AddObject("currEnemyHp5", currEnemyHp5);

	// 4
	std::shared_ptr<GraphicsObject> currEnemyHp4 = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> currEnemyHp4Buffer = Generate::XYPlane(3, 2);

	currEnemyHp4Buffer->AddVertexAttribute("position", 0, 3, 0);
	currEnemyHp4Buffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	currEnemyHp4Buffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> currEnemyHp4Tex = std::make_shared<Texture>();
	currEnemyHp4Tex->LoadTextureDataFromFile("..\\3rdparty\\Poke\\HP4.png");

	// adjusting the texture settings here
	currEnemyHp4Tex->SetWrapS(GL_MIRRORED_REPEAT);
	currEnemyHp4Tex->SetWrapT(GL_MIRRORED_REPEAT);
	currEnemyHp4Tex->SetMagFilter(GL_NEAREST);
	currEnemyHp4Tex->SetMinFilter(GL_NEAREST);


	currEnemyHp4Buffer->SetTexture(currEnemyHp4Tex);
	currEnemyHp4->SetVertexBuffer(currEnemyHp4Buffer);

	currEnemyHp4->SetPosition(glm::vec3(-50.5f, 10.0f, 3.0f));

	backgroundScene->AddObject(currEnemyHp4);
	graphicsEnviron->AddObject("currEnemyHp4", currEnemyHp4);
}



// inserting new hidden scene here for the objects rendered on the side
static void SetUpSideScene(std::shared_ptr<Shader>& shader3d,
	std::shared_ptr<Scene>& scene3d, std::shared_ptr<GraphicsEnvironment>& graphicsEnviron)
{

	std::shared_ptr<TextFile> vertFile = std::make_shared<TextFile>();
	// relative path 
	vertFile->ReadFile("lighting.vert.glsl");

	std::shared_ptr<TextFile> fragFile = std::make_shared<TextFile>();
	// relative path 
	fragFile->ReadFile("lighting.frag.glsl");


	shader3d = std::make_shared<Shader>(vertFile->GetString(), fragFile->GetString());

	shader3d->AddUniform("projection");
	shader3d->AddUniform("world");
	shader3d->AddUniform("view");
	shader3d->AddUniform("materialAmbientIntensity");
	shader3d->AddUniform("materialSpecularIntensity");
	shader3d->AddUniform("materialShininess");
	shader3d->AddUniform("globalLightPosition");
	shader3d->AddUniform("globalLightColor");
	shader3d->AddUniform("globalLightIntensity");
	shader3d->AddUniform("globalLightAttenuationCoef");
	shader3d->AddUniform("localLightPosition");
	shader3d->AddUniform("localLightColor");
	shader3d->AddUniform("localLightIntensity");
	shader3d->AddUniform("localLightAttenuationCoef");
	shader3d->AddUniform("viewPosition");
	shader3d->AddUniform("texUnit");

	unsigned int shaderProgram = shader3d->GetShaderProgram();
	scene3d = std::make_shared<Scene>();

	// Get the uniform locations
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	unsigned int worldLoc = glGetUniformLocation(shaderProgram, "world");

	// new Floor code here
	std::shared_ptr<Texture> texture3dFloor = std::make_shared<Texture>();

	texture3dFloor->LoadTextureDataFromFile("..\\3rdparty\\Poke\\floor.png");


	std::shared_ptr<GraphicsObject> graphicsObject3dFloor = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferFloor = Generate::XZPlaneNorm(30, 40, glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 1.0f, 1.0f });

	bufferFloor->AddVertexAttribute("position", 0, 3, 0);
	bufferFloor->AddVertexAttribute("vertexColor", 1, 4, 3);
	bufferFloor->AddVertexAttribute("normal", 2, 3, 7);
	bufferFloor->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	texture3dFloor->SetWrapS(GL_REPEAT);
	texture3dFloor->SetWrapT(GL_REPEAT);
	texture3dFloor->SetMagFilter(GL_NEAREST);
	texture3dFloor->SetMinFilter(GL_NEAREST);

	bufferFloor->SetTexture(texture3dFloor);

	graphicsObject3dFloor->SetVertexBuffer(bufferFloor);

	graphicsObject3dFloor->SetPosition(glm::vec3(60.0f, 0.0f, 0.0f));  //can adjust position if needed
	graphicsObject3dFloor->RotateLocalY(90.0f);
	scene3d->AddObject(graphicsObject3dFloor);

	// new poke code here

	std::shared_ptr<Texture> poke1SideTex = std::make_shared<Texture>();
	// texture sprites from https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/6.png
	// wiki files also look nice if they can work, https://pokemongo.fandom.com/wiki/Venusaur?file=Venusaur_female.png
	std::string poke1SideDex = "149";
	std::string url1Side = "..\\3rdparty\\Poke\\" + poke1SideDex;
	url1Side += ".png";
	poke1SideTex->LoadTextureDataFromFile(url1Side);

	float poke1SideWidth = 10.0f;
	float poke1SideHeight = 10.0f;

	std::shared_ptr<GraphicsObject> poke1Side = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferSidePoke1 = Generate::XYPlaneNormReverse(poke1SideWidth, poke1SideHeight);

	bufferSidePoke1->AddVertexAttribute("position", 0, 3, 0);
	bufferSidePoke1->AddVertexAttribute("vertexColor", 1, 4, 3);
	bufferSidePoke1->AddVertexAttribute("normal", 2, 3, 7);
	bufferSidePoke1->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	//poke1Tex->SetWrapS(GL_REPEAT);
	//poke1Tex->SetWrapT(GL_REPEAT);
	poke1SideTex->SetMagFilter(GL_NEAREST);
	poke1SideTex->SetMinFilter(GL_NEAREST);

	bufferSidePoke1->SetTexture(poke1SideTex);

	poke1Side->SetVertexBuffer(bufferSidePoke1);

	//poke1Side->CreateBoundingBox(poke1SideWidth, poke1SideHeight, 0.5f);


	//poke 2 here
	std::shared_ptr<Texture> poke2SideTex = std::make_shared<Texture>();
	std::string poke2SideDex = "150";
	std::string url2Side = "..\\3rdparty\\Poke\\" + poke2SideDex;
	url2Side += ".png";
	poke2SideTex->LoadTextureDataFromFile(url2Side);

	float poke2SideWidth = 10.0f;
	float poke2SideHeight = 10.0f;

	std::shared_ptr<GraphicsObject> poke2Side = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferSidePoke2 = Generate::XYPlaneNormReverse(poke2SideWidth, poke2SideHeight);

	bufferSidePoke2->AddVertexAttribute("position", 0, 3, 0);
	bufferSidePoke2->AddVertexAttribute("vertexColor", 1, 4, 3);
	bufferSidePoke2->AddVertexAttribute("normal", 2, 3, 7);
	bufferSidePoke2->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	poke2SideTex->SetWrapS(GL_REPEAT);
	poke2SideTex->SetWrapT(GL_REPEAT);
	poke2SideTex->SetMagFilter(GL_NEAREST);
	poke2SideTex->SetMinFilter(GL_NEAREST);

	bufferSidePoke2->SetTexture(poke2SideTex);

	poke2Side->SetVertexBuffer(bufferSidePoke2);

	//poke2Side->CreateBoundingBox(poke2SideWidth, poke2SideHeight, 0.5f);


	poke1Side->SetPosition(glm::vec3(-7.5f+60.0f, 4.0f, 0.0f));  //can adjust position if needed
	scene3d->AddObject(poke1Side);

	poke2Side->SetPosition(glm::vec3(7.5f+60.0f, 4.0f, 0.0f));  //can adjust position if needed
	scene3d->AddObject(poke2Side);

	graphicsEnviron->AddObject("floorSide", graphicsObject3dFloor);
	//graphicsEnviron->AddObject("background", background);
	graphicsEnviron->AddObject("poke1Side", poke1Side);
	graphicsEnviron->AddObject("poke2Side", poke2Side);



}

// end of hidden scene code here


static void SetUp3DScene2(std::shared_ptr<Shader>& shader3d,
	std::shared_ptr<Scene>& scene3d, std::shared_ptr<GraphicsEnvironment>& graphicsEnviron)
{

	std::shared_ptr<TextFile> vertFile = std::make_shared<TextFile>();
	// relative path 
	vertFile->ReadFile("lighting.vert.glsl");

	std::shared_ptr<TextFile> fragFile = std::make_shared<TextFile>();
	// relative path 
	fragFile->ReadFile("lighting.frag.glsl");


	shader3d = std::make_shared<Shader>(vertFile->GetString(), fragFile->GetString());

	shader3d->AddUniform("projection");
	shader3d->AddUniform("world");
	shader3d->AddUniform("view");
	shader3d->AddUniform("materialAmbientIntensity");
	shader3d->AddUniform("materialSpecularIntensity");
	shader3d->AddUniform("materialShininess");
	shader3d->AddUniform("globalLightPosition");
	shader3d->AddUniform("globalLightColor");
	shader3d->AddUniform("globalLightIntensity");
	shader3d->AddUniform("globalLightAttenuationCoef");
	shader3d->AddUniform("localLightPosition");
	shader3d->AddUniform("localLightColor");
	shader3d->AddUniform("localLightIntensity");
	shader3d->AddUniform("localLightAttenuationCoef");
	shader3d->AddUniform("viewPosition");
	shader3d->AddUniform("texUnit");

	unsigned int shaderProgram = shader3d->GetShaderProgram();


	// Get the uniform locations
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	unsigned int worldLoc = glGetUniformLocation(shaderProgram, "world");


	std::shared_ptr<Texture> texture3d = std::make_shared<Texture>();
	texture3d->SetHeight(4);
	texture3d->SetWidth(4);

	// Create the texture data
	unsigned char* textureData = new unsigned char[] {
		0, 0, 0, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 0, 255,
			0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
			0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
			0, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 0, 0, 0, 255
		};

	texture3d->SetTextureData(64, textureData);

	float cubeWidth = 10.0f;
	float cubeHeight = 5.0f;
	float cubeDepth = 5.0f;


	scene3d = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> graphicsObject3d = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer = Generate::CuboidNorm(cubeWidth, cubeHeight, cubeDepth);

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 4, 3);
	buffer->AddVertexAttribute("normal", 2, 3, 7);
	buffer->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	texture3d->SetWrapS(GL_REPEAT);
	texture3d->SetWrapT(GL_REPEAT);
	texture3d->SetMagFilter(GL_NEAREST);
	texture3d->SetMinFilter(GL_NEAREST);

	buffer->SetTexture(texture3d);



	graphicsObject3d->SetVertexBuffer(buffer);

	graphicsObject3d->CreateBoundingBox(cubeWidth, cubeHeight, cubeDepth);

	// adding highlight behavior here
	std::shared_ptr<HighlightBehavior> cubeHighlight = std::make_shared<HighlightBehavior>();
	cubeHighlight->SetObject(graphicsObject3d);
	graphicsObject3d->AddBehavior("highlight", cubeHighlight);


	graphicsObject3d->SetPosition(glm::vec3(0.0f, 2.6f, 0.0f));  //can adjust position if needed
	scene3d->AddObject(graphicsObject3d);


	// new crate code here
	std::shared_ptr<Texture> texture3dNew = std::make_shared<Texture>();

	//texture3dNew->LoadTextureDataFromFile("..\\3rdparty\\CrateTex.png");
	texture3dNew->LoadTextureDataFromFile("..\\3rdparty\\CrateTex2.jpg");


	float crateWidth = 5.0f;
	float crateHeight = 5.0f;
	float crateDepth = 5.0f;

	std::shared_ptr<GraphicsObject> graphicsObject3dCrate = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferNew = Generate::CuboidNorm(crateWidth, crateHeight, crateDepth);

	bufferNew->AddVertexAttribute("position", 0, 3, 0);
	bufferNew->AddVertexAttribute("vertexColor", 1, 4, 3);
	bufferNew->AddVertexAttribute("normal", 2, 3, 7);
	bufferNew->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	texture3dNew->SetWrapS(GL_REPEAT);
	texture3dNew->SetWrapT(GL_REPEAT);
	texture3dNew->SetMagFilter(GL_NEAREST);
	texture3dNew->SetMinFilter(GL_NEAREST);

	bufferNew->SetTexture(texture3dNew);


	graphicsObject3dCrate->SetVertexBuffer(bufferNew);
	// add bounding box here?
	graphicsObject3dCrate->CreateBoundingBox(crateWidth, crateHeight, crateDepth);

	// adding highlight behavior here
	std::shared_ptr<HighlightBehavior> crateHighlight = std::make_shared<HighlightBehavior>();
	crateHighlight->SetObject(graphicsObject3dCrate);
	graphicsObject3dCrate->AddBehavior("highlight", crateHighlight);


	graphicsObject3dCrate->SetPosition(glm::vec3(-10.0f, 2.6f, 0.0f));  //can adjust position if needed
	scene3d->AddObject(graphicsObject3dCrate);


	// new Floor code here
	std::shared_ptr<Texture> texture3dFloor = std::make_shared<Texture>();

	texture3dFloor->LoadTextureDataFromFile("..\\3rdparty\\FloorTex.jpg");


	std::shared_ptr<GraphicsObject> graphicsObject3dFloor = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferFloor = Generate::XZPlaneNorm(60, 60, glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec2{ 5.0f, 5.0f });

	bufferFloor->AddVertexAttribute("position", 0, 3, 0);
	bufferFloor->AddVertexAttribute("vertexColor", 1, 4, 3);
	bufferFloor->AddVertexAttribute("normal", 2, 3, 7);
	bufferFloor->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	texture3dFloor->SetWrapS(GL_REPEAT);
	texture3dFloor->SetWrapT(GL_REPEAT);
	texture3dFloor->SetMagFilter(GL_NEAREST);
	texture3dFloor->SetMinFilter(GL_NEAREST);

	bufferFloor->SetTexture(texture3dFloor);



	graphicsObject3dFloor->SetVertexBuffer(bufferFloor);

	graphicsObject3dFloor->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));  //can adjust position if needed
	scene3d->AddObject(graphicsObject3dFloor);


	// new globe code here
	std::shared_ptr<Texture> textureGlobe = std::make_shared<Texture>();

	textureGlobe->LoadTextureDataFromFile("..\\3rdparty\\GlobeTex.jpg");


	float globeWidth = 5.0f;
	float globeHeight = 5.0f;
	float globeDepth = 5.0f;

	std::shared_ptr<GraphicsObject> globe = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> bufferGlobe = Generate::CuboidNorm(globeWidth, globeHeight, globeDepth);

	bufferGlobe->AddVertexAttribute("position", 0, 3, 0);
	bufferGlobe->AddVertexAttribute("vertexColor", 1, 4, 3);
	bufferGlobe->AddVertexAttribute("normal", 2, 3, 7);
	bufferGlobe->AddVertexAttribute("texCoord", 3, 2, 10);

	// adjusting the texture settings here
	textureGlobe->SetWrapS(GL_REPEAT);
	textureGlobe->SetWrapT(GL_REPEAT);
	textureGlobe->SetMagFilter(GL_NEAREST);
	textureGlobe->SetMinFilter(GL_NEAREST);

	bufferGlobe->SetTexture(textureGlobe);


	globe->SetVertexBuffer(bufferGlobe);
	// add bounding box here?
	globe->CreateBoundingBox(globeWidth, globeHeight, globeDepth);

	// adding highlight behavior here
	std::shared_ptr<HighlightBehavior> globeHighlight = std::make_shared<HighlightBehavior>();
	globeHighlight->SetObject(globe);
	globe->AddBehavior("highlight", globeHighlight);


	globe->SetPosition(glm::vec3(27.5f, 2.5f, 27.5f));  //need to adjust to south east corner of plane
	scene3d->AddObject(globe);




	graphicsEnviron->AddObject("cube", graphicsObject3d);
	graphicsEnviron->AddObject("Crate", graphicsObject3dCrate);
	graphicsEnviron->AddObject("floor", graphicsObject3dFloor);
	graphicsEnviron->AddObject("globe", globe);



}




// new ray scene here
static void SetUpPCObjectsScene(
	std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene,
	std::shared_ptr<GraphicsEnvironment>& env)
{
	std::shared_ptr<TextFile> vertFile = std::make_shared<TextFile>();
	// relative path 
	vertFile->ReadFile("basic.vert.glsl");

	// relative path
	std::shared_ptr<TextFile> fragFile = std::make_shared<TextFile>();
	fragFile->ReadFile("basic.frag.glsl");

	shader = std::make_shared<Shader>(vertFile->GetString(), fragFile->GetString());

	shader->AddUniform("projection");
	shader->AddUniform("world");
	shader->AddUniform("view");

	// create object
	scene = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> pcLinesCircle = std::make_shared<GraphicsObject>();
	pcLinesCircle->CreateVertexBuffer(6);  
	pcLinesCircle->CreateIndexBuffer();
	std::shared_ptr<VertexBuffer> bufferNew = pcLinesCircle->GetVertexBuffer();
	std::shared_ptr<IndexBuffer> indexBufferNew = pcLinesCircle->GetIndexBuffer();
	int steps = 10;  // can change this if we want to change the number of steps
	bufferNew->SetPrimitiveType(GL_LINES); 
	Generate::GenerateXZCircle(6, glm::vec3(1.0f), steps, bufferNew);  //10 steps used here
	Generate::LineCircleIndexes(indexBufferNew, (360/steps), true);  // 36 used here because 360 degrees and 10 steps
	bufferNew->AddVertexAttribute("position", 0, 3, 0); 
	bufferNew->AddVertexAttribute("color", 1, 3, 3);
	bufferNew->SetUpAttributeInterpretration();
	pcLinesCircle->SetPosition({ 0.0f, 1.0f, 10.0f }); // set initial position
	scene->AddObject(pcLinesCircle);
	env->AddObject("pcLinesCircle", pcLinesCircle);

	//cylinder 
	std::shared_ptr<GraphicsObject> pcLinesCylinder = std::make_shared<GraphicsObject>();
	pcLinesCylinder->CreateVertexBuffer(6);
	pcLinesCylinder->CreateIndexBuffer();
	std::shared_ptr<VertexBuffer> bufferNewCylinder = pcLinesCylinder->GetVertexBuffer();
	std::shared_ptr<IndexBuffer> indexBufferNewCylinder = pcLinesCylinder->GetIndexBuffer();
	int steps2 = 10;  // can change this if we want to change the number of steps
	bufferNewCylinder->SetPrimitiveType(GL_LINES);
	Generate::GenerateXZCylinder(6, 10, glm::vec3(1.0f), steps2, bufferNewCylinder); 
	Generate::LineCylinderIndexes(indexBufferNewCylinder, (360 / steps2)); 
	bufferNewCylinder->AddVertexAttribute("position", 0, 3, 0);
	bufferNewCylinder->AddVertexAttribute("color", 1, 3, 3);
	bufferNewCylinder->SetUpAttributeInterpretration();
	pcLinesCylinder->SetPosition({ 15.0f, 10.0f, 10.0f }); // set initial position
	scene->AddObject(pcLinesCylinder);
	env->AddObject("pcLinesCylinder", pcLinesCylinder);


}


static void SetUpLightScene(std::shared_ptr<Shader>&
	lightShader, std::shared_ptr<Scene>& lightScene, std::shared_ptr<GraphicsEnvironment>& graphicsEnviron)
{
	//unsigned int shaderProgram;
	std::shared_ptr<TextFile> vertFile = std::make_shared<TextFile>();
	// relative path 
	vertFile->ReadFile("texture.vert.glsl");

	// relative path
	std::shared_ptr<TextFile> fragFile = std::make_shared<TextFile>();
	fragFile->ReadFile("texture.frag.glsl");

	lightShader = std::make_shared<Shader>(vertFile->GetString(), fragFile->GetString());

	lightShader->AddUniform("projection");
	lightShader->AddUniform("world");
	lightShader->AddUniform("view");



	// new textured object to scene
	lightScene = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> lightbulb = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> lightbulbBuffer = Generate::XYPlane(4, 4);

	lightbulbBuffer->AddVertexAttribute("position", 0, 3, 0);
	lightbulbBuffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	lightbulbBuffer->AddVertexAttribute("texCoord", 2, 2, 6);


	std::shared_ptr<Texture> lightbulbTexture = std::make_shared<Texture>();
	lightbulbTexture->LoadTextureDataFromFile("..\\3rdparty\\lightbulb.png");


	lightbulbBuffer->SetTexture(lightbulbTexture);
	lightbulb->SetVertexBuffer(lightbulbBuffer);

	lightScene->AddObject(lightbulb);
	graphicsEnviron->AddObject("lightbulb", lightbulb);


}


static void SetUpArrowScene(std::shared_ptr<Shader>&
	arrowShader, std::shared_ptr<Scene>& arrowScene, std::shared_ptr<GraphicsEnvironment>& graphicsEnviron)
{
	//unsigned int shaderProgram;
	std::shared_ptr<TextFile> vertFile = std::make_shared<TextFile>();
	// relative path 
	vertFile->ReadFile("texture.vert.glsl");

	// relative path
	std::shared_ptr<TextFile> fragFile = std::make_shared<TextFile>();
	fragFile->ReadFile("texture.frag.glsl");

	arrowShader = std::make_shared<Shader>(vertFile->GetString(), fragFile->GetString());

	arrowShader->AddUniform("projection");
	arrowShader->AddUniform("world");
	arrowShader->AddUniform("view");



	// new textured object to scene
	arrowScene = std::make_shared<Scene>();
	std::shared_ptr<GraphicsObject> arrow = std::make_shared<GraphicsObject>();

	std::shared_ptr<VertexBuffer> arrowBuffer = Generate::Cuboid(4, 4, 10);
	std::shared_ptr<VertexBuffer> arrowBuffer2 = Generate::ArrowNorm(4, 4, 10);


	arrowBuffer->AddVertexAttribute("position", 0, 3, 0);
	arrowBuffer->AddVertexAttribute("vertexColor", 1, 3, 3);
	arrowBuffer->AddVertexAttribute("texCoord", 2, 2, 6);




	std::shared_ptr<Texture> arrowTexture = std::make_shared<Texture>();
	// this texture is breaking now for some reason
	//arrowTexture->LoadTextureDataFromFile("..\\3rdparty\\ArrowTex2.jpg");


	arrowBuffer->SetTexture(arrowTexture);
	arrow->SetVertexBuffer(arrowBuffer);
	arrow->SetPosition(glm::vec3(10.0f, 10.0f, 0.0f));

	arrowScene->AddObject(arrow);
	graphicsEnviron->AddObject("arrow", arrow);


}


static void SetUpDex(std::unordered_map<int, std::shared_ptr<Poke>>& pokeMap)
{
	std::vector<std::string> pokeNames = {"Bulbasaur", "Ivysaur", "Venusaur", "Charmander", "Charmeleon", "Charizard", "Blastoise", "Pikachu", "Alakazam", "Machamp", "Dragonite", "Mewtwo", "Mew"};
	std::vector<int> pokeNums = {1, 2, 3, 4, 5, 6, 9, 25, 65, 68, 149, 150, 151 };
	std::string pokeUrl = "";

	// ideally this will populate from the default database that is used for random encounters

	for (int i = 0; i < pokeNames.size(); i++)
	{
		pokeUrl = "";
		pokeUrl += "..\\3rdparty\\Poke\\";
		int num = pokeNums[i];
		pokeUrl += std::to_string(num);
		pokeUrl += ".png";
		std::shared_ptr<Poke> poke = std::make_shared<Poke>(pokeNums[i], pokeNames[i], pokeUrl, 10, 10);
		pokeMap.emplace(pokeNums[i], poke);
	}		
}



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	std::shared_ptr<GraphicsEnvironment> graphicsEnviron = std::make_shared<GraphicsEnvironment>();
	graphicsEnviron->Init(4, 3);

	bool created = graphicsEnviron->SetWindow(1200, 800, "Poke Sim");
	if (created == false) return -1;


	bool loaded = graphicsEnviron->InitGlad();
	if (loaded == false) return -1;
	
	graphicsEnviron->SetUpGraphics();

	// new 3d code created here
	std::shared_ptr<Shader> shader3d;
	std::shared_ptr<Scene> scene3d;

	// set up the poke scenes here
	std::shared_ptr<Shader> shaderBackground;
	std::shared_ptr<Scene> sceneBackground;

	// set up the poke scenes here
	std::shared_ptr<Shader> shaderSideScene;
	std::shared_ptr<Scene> sceneSideScene;

	std::unordered_map<int, std::shared_ptr<Poke>> pokeMap;

	SetUpDex(pokeMap);

	SetUpBackgroundScene(shaderBackground, sceneBackground, graphicsEnviron);
	SetUpPokeBattler(shader3d, scene3d, graphicsEnviron, pokeMap);
	SetUpSideScene(shaderSideScene, sceneSideScene, graphicsEnviron);

	graphicsEnviron->CreateRenderer("rendererBackground", shaderBackground);
	graphicsEnviron->GetRenderer("rendererBackground")->SetScene(sceneBackground);

	graphicsEnviron->CreateRenderer("renderer3d", shader3d);
	graphicsEnviron->GetRenderer("renderer3d")->SetScene(scene3d);

	//graphicsEnviron->CreateRenderer("rendererSideScene", shaderSideScene);
	//graphicsEnviron->GetRenderer("rendererSideScene")->SetScene(sceneSideScene);

	graphicsEnviron->StaticAllocate();

	graphicsEnviron->Run3D();
	
	
	return 0;
}

