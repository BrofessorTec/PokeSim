#include "SlidingAnimation.h"
#include "GraphicsEnvironment.h"
#include <glm/gtc/matrix_transform.hpp>


void SlidingAnimation::Update(double elapsedSeconds)
{
	if (object == nullptr) return;
	float deltaSpeed;
	if (direction == glm::vec3(-1.0f, 0.0f, 0.0f))
	{
		deltaSpeed = -static_cast<float>(speed * elapsedSeconds);
	}
	else
	{
		deltaSpeed = static_cast<float>(speed * elapsedSeconds);
	}

	glm::mat4& referenceFrame = object->GetLocalReferenceFrame();
	// need to change this from rotation to moving in the direction
	//referenceFrame = glm::rotate(referenceFrame, glm::radians(deltaSpeed),
	//	direction);
	if (isMoving && distanceMoved < distanceToMove && !completed)
	{
		referenceFrame[3] = { referenceFrame[3].x + deltaSpeed, referenceFrame[3].y, referenceFrame[3].z, 1.0f };
		distanceMoved = abs(deltaSpeed) + distanceMoved;
	}
	else if (isMoving && distanceMoved >= distanceToMove && !completed)
	{
		distanceMoved = 0;
		direction = -direction;
		isMoving = false;
		completed = true;
	}
	/*
	else if (isMoving && distanceMoved >= distanceToMove)
	{
		distanceMoved = 0;
		direction = -direction;
	}
	*/

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
