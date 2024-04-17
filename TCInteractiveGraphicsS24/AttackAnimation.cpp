#include "AttackAnimation.h"
#include "GraphicsEnvironment.h"
#include <glm/gtc/matrix_transform.hpp>


void AttackAnimation::Update(double elapsedSeconds)
{
	if (object == nullptr) return;
	float deltaSpeed;
	/*
	if (direction == glm::vec3(0.0f, 0.0f, -1.0f))
	{
		deltaSpeed = -static_cast<float>(speed * elapsedSeconds);
	}
	else
	{
		deltaSpeed = static_cast<float>(speed * elapsedSeconds);
	}
	*/
	deltaSpeed = -static_cast<float>(speed * elapsedSeconds);

	glm::mat4& referenceFrame = object->GetLocalReferenceFrame();
	// need to change this from rotation to moving in the direction
	//referenceFrame = glm::rotate(referenceFrame, glm::radians(deltaSpeed),
	//	direction);

	if(!completed && isMoving)
	{
		if (firstPassCompleted && secondPassCompleted && isMoving && distanceMoved >= distanceToMove)
		{
			distanceMoved = 0;
			//direction = -direction;
			completed = true;
		}
		else if (firstPassCompleted && !secondPassCompleted && isMoving && distanceMoved >= distanceToMove)
		{
			distanceMoved = 0;
			distanceToMove = distanceToMove / 2;
			direction = -direction;
			secondPassCompleted = true;
		}
		else if (!firstPassCompleted && isMoving && distanceMoved >= distanceToMove)
		{
			distanceMoved = 0;
			distanceToMove = distanceToMove * 2;
			direction = -direction;
			firstPassCompleted = true;
		}
		else if (isMoving && distanceMoved < distanceToMove)
		{
			referenceFrame = glm::rotate(referenceFrame, glm::radians(deltaSpeed), direction);
			distanceMoved = abs(deltaSpeed) + distanceMoved;
		}
		//firstPassCompleted = true;
	}
	else if (completed)
	{
		isMoving = false;
		firstPassCompleted = false;
		secondPassCompleted = false;
		completed = false;
		// set other poke hp lower and trigger it's attack here? seems like that would work
	}
}

void AttackAnimation::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

float& AttackAnimation::GetSpeed()
{
	return speed;
}

float AttackAnimation::GetDistanceMoved()
{
	return distanceMoved;
}

float AttackAnimation::GetDistanceToMove()
{
	return distanceToMove;
}

glm::vec3 AttackAnimation::GetDirection()
{
	return direction;
}

void AttackAnimation::SetMove(bool isMoving)
{
	this->isMoving = isMoving;
}

bool AttackAnimation::GetMove()
{
	return isMoving;
}

bool AttackAnimation::GetCompleted()
{
	return completed;
}
