#pragma once
#include <memory>
#include "IBehavior.h"

class GraphicsObject; // Forward declaration

class IAnimation : public IBehavior
{
protected:
	std::shared_ptr<GraphicsObject> object;
	std::string name;
public:
	IAnimation() : object(nullptr) {}
	virtual ~IAnimation() = default;
	virtual void SetObject(std::shared_ptr<GraphicsObject> object);
	virtual void Update(double elapsedSeconds) = 0;
	std::string GetName();
	void SetName(std::string newName);
};