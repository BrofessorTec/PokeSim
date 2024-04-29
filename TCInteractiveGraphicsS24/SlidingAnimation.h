#pragma once
#include "IAnimation.h"
#include <glm/glm.hpp>

class SlidingAnimation : public IAnimation
{
private:
	float distanceToMove = 15;
	float distanceMoved = 0;
	glm::vec3 direction;
	float speed;
	bool isMoving = false;
	bool completed = false;
public:
	SlidingAnimation(glm::vec3 direction = glm::vec3(-1.0f, 0.0f, 0.0f), float speed
		= 20.0f)
		: IAnimation(), direction(direction), speed(speed) {}
	void Update(double elapsedSeconds) override;
	void SetSpeed(float newSpeed);
	float& GetSpeed();
	float GetDistanceMoved();
	float GetDistanceToMove();
	glm::vec3 GetDirection();
	void SetMove(bool isMoving);
	bool GetMove();
	bool GetCompleted();
	void SetCompleted(bool newState);
	void SetDirection(glm::vec3 direction);


};

