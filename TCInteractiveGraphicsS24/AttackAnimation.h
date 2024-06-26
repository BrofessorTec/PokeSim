#pragma once
#include "IAnimation.h"
#include <glm/glm.hpp>

class AttackAnimation : public IAnimation
{
private:
	float distanceToMove = 20;
	float distanceMoved = 0;
	glm::vec3 direction;
	float speed;
	bool isMoving = false;
	bool firstPassCompleted = false;
	bool secondPassCompleted = false;
	bool completed = false;
	glm::mat4 startingFrame = glm::mat4(1.0f);
public:
	AttackAnimation(glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f), float speed
		= 180.0f)
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
};