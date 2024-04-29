#include "IAnimation.h"
#include "GraphicsObject.h"
void IAnimation::SetObject(std::shared_ptr<GraphicsObject> object)
{
	this->object = object;
}

std::string IAnimation::GetName()
{
	return name;
}

void IAnimation::SetName(std::string newName)
{
	name = newName;
}
