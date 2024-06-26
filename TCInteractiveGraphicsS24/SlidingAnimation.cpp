#include "SlidingAnimation.h"
#include "GraphicsEnvironment.h"
#include <glm/gtc/matrix_transform.hpp>


void SlidingAnimation::Update(double elapsedSeconds)
{
	if (object == nullptr) return;
	float deltaSpeed = deltaSpeed = static_cast<float>(speed * elapsedSeconds);

	glm::mat4& referenceFrame = object->GetLocalReferenceFrame();

	if (isMoving && distanceMoved < distanceToMove && !completed)
	{
		referenceFrame[3] = { referenceFrame[3].x + (deltaSpeed * direction.x), referenceFrame[3].y + (deltaSpeed * direction.y), referenceFrame[3].z + (deltaSpeed * direction.z), 1.0f };
		distanceMoved = abs(deltaSpeed) + distanceMoved;
	}
	else if (isMoving && distanceMoved >= distanceToMove && !completed)
	{
		distanceMoved = 0;
		isMoving = false;
		completed = true;
	}
}

void SlidingAnimation::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

float& SlidingAnimation::GetSpeed()
{
	return speed;
}

float SlidingAnimation::GetDistanceMoved()
{
	return distanceMoved;
}

float SlidingAnimation::GetDistanceToMove()
{
	return distanceToMove;
}

glm::vec3 SlidingAnimation::GetDirection()
{
	return direction;
}

void SlidingAnimation::SetMove(bool isMoving)
{
	this->isMoving = isMoving;
}

bool SlidingAnimation::GetMove()
{
	return isMoving;
}

bool SlidingAnimation::GetCompleted()
{
	return completed;
}

void SlidingAnimation::SetCompleted(bool newState)
{
	completed = newState;
}

void SlidingAnimation::SetDirection(glm::vec3 direction)
{
	this->direction = direction;
}
