#include "Camera.h"

void Camera::SetLookFrame(glm::mat4 lookFrame)
{
	this->lookFrame = lookFrame;
}

void Camera::SetMoveSpeed(int speed)
{
	moveSpeed = speed;
}

void Camera::SetPosition(glm::vec3 position)
{
	refFrame[3] = glm::vec4(position, 1.0f);
}

glm::mat4 Camera::LookForward()
{
	//returns a view matrix that looks forward. Use the look frame

	glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraForward;


	cameraForward = -lookFrame[2];
	cameraTarget = glm::vec3(refFrame[3]) + cameraForward;
	cameraUp = lookFrame[1];

	return glm::lookAt(glm::vec3(refFrame[3]), cameraTarget, cameraUp);
}

glm::mat4 Camera::LookAtTarget(glm::vec3 target)
{
	// it returns a view matrix that looks at the target position.
	//Use the look frame.

	glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraForward; // camera forward isnt used at all here?

	cameraForward = -lookFrame[2];
	cameraUp = lookFrame[1];

	return glm::lookAt(glm::vec3(refFrame[3]), target, cameraUp);
}

void Camera::MoveForward(double elapsedSeconds)
{
	glm::vec3 forward = -lookFrame[2];
	glm::vec3 position = refFrame[3];
	forward = forward * static_cast<float>(moveSpeed * elapsedSeconds);
	position = position + forward;
	refFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveBackward(double elapsedSeconds)
{
	glm::vec3 backward = lookFrame[2];
	glm::vec3 position = refFrame[3];
	backward = backward * static_cast<float>(moveSpeed * elapsedSeconds);
	position = position + backward;
	refFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveLeft(double elapsedSeconds)
{
	glm::vec3 toLeft = -lookFrame[0];
	glm::vec3 position = refFrame[3];
	toLeft = toLeft * static_cast<float>(10.0f * elapsedSeconds);
	position = position + toLeft;
	refFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveRight(double elapsedSeconds)
{
	glm::vec3 toRight = lookFrame[0];
	glm::vec3 position = refFrame[3];
	toRight = toRight * static_cast<float>(10.0f * elapsedSeconds);
	position = position + toRight;
	refFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveUp(double elapsedSeconds)
{
	glm::vec3 up = refFrame[1];
	glm::vec3 position = refFrame[3];
	up = up * static_cast<float>(moveSpeed * elapsedSeconds);
	position = position + up;
	refFrame[3] = glm::vec4(position, 1.0f);
}

void Camera::MoveDown(double elapsedSeconds)
{
	glm::vec3 up = -refFrame[1];
	glm::vec3 position = refFrame[3];
	up = up * static_cast<float>(moveSpeed * elapsedSeconds);
	position = position + up;
	refFrame[3] = glm::vec4(position, 1.0f);
}

glm::vec3 Camera::GetPosition()
{
	return refFrame[3];
}

void Camera::SetCanMove(bool newState)
{
	canMove = newState;
}

bool Camera::GetCanMove()
{
	return canMove;
}
