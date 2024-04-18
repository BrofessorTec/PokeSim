#include "GraphicsObject.h"
#include <glm/gtc/matrix_transform.hpp>

GraphicsObject::GraphicsObject() : referenceFrame(1.0f), parent(nullptr)
{
	material.ambientIntensity = 0.4f;
	material.shininess = 0.5f;
	material.specularIntensity = 0.5f;
	indexBuffer = nullptr;
}

GraphicsObject::~GraphicsObject()
{
}

const glm::mat4 GraphicsObject::GetReferenceFrame() const
{
	if (parent != nullptr) {
		return parent->referenceFrame * referenceFrame;
	}
	return referenceFrame;
}

void GraphicsObject::CreateVertexBuffer(unsigned int numberOfElementsPerVertex)
{
	buffer = std::make_shared<VertexBuffer>(numberOfElementsPerVertex);
}

void GraphicsObject::SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
{
	this->buffer = buffer;
}

void GraphicsObject::StaticAllocateBuffers()
{
	buffer->Select();
	buffer->StaticAllocate();
	buffer->Deselect();
	for (auto& child : children) {
		child->StaticAllocateBuffers();
	}
	if (indexBuffer != nullptr)
	{
		indexBuffer->Select();
		indexBuffer->StaticAllocate();
		indexBuffer->Deselect();
	}
}

void GraphicsObject::AddChild(std::shared_ptr<GraphicsObject> child)
{
	children.push_back(child);
	child->parent = this;
}

void GraphicsObject::SetPosition(const glm::vec3& position)
{
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void GraphicsObject::ResetOrientation()
{
	glm::vec4 position = referenceFrame[3];
	referenceFrame = glm::mat4(1.0f);
	referenceFrame[3] = position;
}

void GraphicsObject::RotateLocalX(float degrees)
{
	referenceFrame = glm::rotate(
		referenceFrame,
		glm::radians(degrees),
		glm::vec3(1.0f, 0.0f, 0.0f)
	);
}

void GraphicsObject::RotateLocalY(float degrees)
{
	referenceFrame = glm::rotate(
		referenceFrame,
		glm::radians(degrees),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}

void GraphicsObject::RotateLocalZ(float degrees)
{
	referenceFrame = glm::rotate(
		referenceFrame, 
		glm::radians(degrees), 
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
}

void GraphicsObject::SetReferenceFrame(glm::mat4 newReferenceFrame)
{
	referenceFrame = newReferenceFrame;
}

void GraphicsObject::Update(double elapsedSeconds)
{
	// needs stuff
	if (this->animation != nullptr)
	{
		// call animation's update
		animation->Update(elapsedSeconds);
	}

	for (auto& [name, behavior] : behaviorMap) {
		behavior->Update(elapsedSeconds);
	}
}

void GraphicsObject::SetAnimation(std::shared_ptr<IAnimation> animation)
{
	this->animation = animation;
}

std::shared_ptr<IAnimation> GraphicsObject::GetAnimation()
{
	if (this->animation != nullptr)
	{
		return animation;
	}
}

void GraphicsObject::PointAtTarget(glm::vec3 point)
{
	glm::vec3 position = referenceFrame[3];
	glm::vec3 zAxis = glm::normalize(point - position);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 xAxis = glm::normalize(glm::cross(up, zAxis));
	glm::vec3 yAxis = glm::cross(zAxis, xAxis);
	referenceFrame[0] = glm::vec4(xAxis, 0.0f);
	referenceFrame[1] = glm::vec4(yAxis, 0.0f);
	referenceFrame[2] = glm::vec4(zAxis, 0.0f);
}

void GraphicsObject::CreateIndexBuffer()
{
	indexBuffer = std::make_shared<IndexBuffer>();
}

std::shared_ptr<IndexBuffer>& GraphicsObject::GetIndexBuffer()
{
	return indexBuffer;
}

bool GraphicsObject::IsIndexed() const
{
	if (indexBuffer != nullptr)
	{
		return true;
	}
	return false;
}

void GraphicsObject::CreateBoundingBox(float width, float height, float depth)
{
	boundingBox = std::make_shared<BoundingBox>();
	boundingBox->SetReferenceFrame(referenceFrame);
	boundingBox->Create(width, height, depth);
}

BoundingBox& GraphicsObject::GetBoundingBox()
{
	// is the * how you are supposed to do this?
	return *boundingBox;
	// return boundingBox;
}

bool GraphicsObject::IsIntersectingWithRay(const Ray& ray) const
{
	boundingBox->SetReferenceFrame(referenceFrame);
	return boundingBox->IsIntersectingWithRay(ray);
}

bool GraphicsObject::HasBoundingBox()
{
	if (boundingBox != nullptr)
	{
		return true;
	}
	return false;
}

void GraphicsObject::AddBehavior(std::string name, std::shared_ptr<IBehavior> behavior)
{
	behaviorMap.emplace(name, behavior);
}

void GraphicsObject::SetBehaviorDefaults()
{
	//It loops through all the behaviors storing their defaults
	//is this done correctly?
	for (auto& [name, behavior] : behaviorMap) {
		behavior->StoreDefaults();
	}
}

void GraphicsObject::SetBehaviorParameters(std::string name, GraphicStructures::IParams& params)
{
	behaviorMap[name]->SetParameter(params);
}

std::shared_ptr<Poke> GraphicsObject::GetPoke()
{
	return poke;
}

void GraphicsObject::SetPoke(std::shared_ptr<Poke> newPoke)
{
	poke = newPoke;
}

GraphicStructures::Material& GraphicsObject::GetMaterial()
{
	return material;
}
