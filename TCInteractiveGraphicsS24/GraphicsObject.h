#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "VertexBuffer.h"
#include "GraphicStructures.h"
#include "IndexBuffer.h"
#include "BoundingBox.h"
#include "IBehavior.h"
#include "IAnimation.h"
#include "Poke.h"

class IAnimation; // Forward declaration


class GraphicsObject
{
protected:
	glm::mat4 referenceFrame;
	std::shared_ptr<VertexBuffer> buffer;
	GraphicsObject* parent;
	std::vector<std::shared_ptr<GraphicsObject>> children;
	std::shared_ptr<IAnimation> animation = nullptr;
	GraphicStructures::Material material{};
	std::shared_ptr<BoundingBox> boundingBox = nullptr;
	std::unordered_map<std::string, std::shared_ptr<IBehavior>> behaviorMap;
	std::shared_ptr<Poke> poke = nullptr;


public:
	GraphicsObject();
	virtual ~GraphicsObject();
	GraphicStructures::Material& GetMaterial();
	const glm::mat4 GetReferenceFrame() const;
	void CreateVertexBuffer(unsigned int numberOfElementsPerVertex);
	void SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
	inline const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const {
		return buffer;
	}
	void StaticAllocateBuffers();

	void AddChild(std::shared_ptr<GraphicsObject> child);
	inline const std::vector<std::shared_ptr<GraphicsObject>>& GetChildren() const {
		return children;
	}

	void SetPosition(const glm::vec3& position);
	void ResetOrientation();
	void RotateLocalX(float degrees);
	void RotateLocalY(float degrees);
	void RotateLocalZ(float degrees);
	void SetReferenceFrame(glm::mat4 newReferenceFrame);
	void Update(double elapsedSeconds);   //needs definition
	void SetAnimation(std::shared_ptr<IAnimation> animation);
	std::shared_ptr<IAnimation> GetAnimation();
	glm::mat4& GetLocalReferenceFrame() { return referenceFrame; };
	void PointAtTarget(glm::vec3 point);
	std::shared_ptr<IndexBuffer> indexBuffer;
	void CreateIndexBuffer();
	std::shared_ptr<IndexBuffer>& GetIndexBuffer();
	bool IsIndexed() const;
	void CreateBoundingBox(float width, float height, float depth);
	BoundingBox& GetBoundingBox();
	bool IsIntersectingWithRay(const Ray& ray) const;
	bool HasBoundingBox();
	void AddBehavior(std::string name, std::shared_ptr<IBehavior> behavior);
	void SetBehaviorDefaults();
	void SetBehaviorParameters(std::string name, GraphicStructures::IParams& params);
	std::shared_ptr<Poke> GetPoke();
	void SetPoke(std::shared_ptr<Poke> newPoke);
};

