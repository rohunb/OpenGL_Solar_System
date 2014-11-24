#pragma once
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include <stdio.h>

class Camera
{
private:
	glm::vec3 position, forward, up, right, worldUp;
	glm::mat4 orientation;
	float fovY, aspectRatio, nearClipDistance, farClipDistance;
	glm::mat4 viewMatrix, projectionMatrix;

public:

	Camera(const glm::vec3& _position = glm::vec3(0.0f))
		: position(_position),
		worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
		orientation(glm::mat4(1.0f)),
		fovY(53.13f), aspectRatio(1.0f), nearClipDistance(0.1f), farClipDistance(1000.0f)
	{
		Recalculate();
		SetProjection(fovY, aspectRatio, nearClipDistance, farClipDistance);
	}

	Camera(const glm::vec3& _position, const glm::vec3& up, const glm::mat4& _orientation)
		: position(_position),
		worldUp(up),
		orientation(_orientation),
		fovY(53.13f), aspectRatio(1.0f), nearClipDistance(0.1f), farClipDistance(1000.0f)
	{
		Recalculate();
		SetProjection(fovY, aspectRatio, nearClipDistance, farClipDistance);
	}

	Camera(float _fovY, float _aspectRatio, float _nearClipDistance, float _farClipDistance)
		: position(glm::vec3(0.0f)),
		worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
		orientation(glm::mat4(1.0f)),
		fovY(_fovY),
		aspectRatio(_aspectRatio),
		nearClipDistance(_nearClipDistance),
		farClipDistance(_farClipDistance)
	{
		Recalculate();
		SetProjection(fovY, aspectRatio, nearClipDistance, farClipDistance);
	}

	Camera(const glm::vec3& _position, const glm::vec3& _up, const glm::mat4& _orientation,
		float _fovY, float _aspectRatio, float _nearClipDistance, float _farClipDistance)
		:position(_position),
		worldUp(_up),
		orientation(_orientation),
		fovY(_fovY),
		aspectRatio(_aspectRatio),
		nearClipDistance(_nearClipDistance),
		farClipDistance(_farClipDistance)
	{
		Recalculate();
		SetProjection(fovY, aspectRatio, nearClipDistance, farClipDistance);
	}

	~Camera(){}

	inline glm::mat4 View() const
	{
		return viewMatrix;
	}
	inline glm::mat4 Projection() const
	{
		return projectionMatrix;
	}
	inline void SetProjection(float fovY, float aspectRatio, float nearClipDistance, float farClipDistance)
	{
		projectionMatrix = glm::perspective(fovY, aspectRatio, nearClipDistance, farClipDistance);
	}
	inline void MoveCamera(const glm::vec3& direction)
	{
		position += direction;
	}
	inline void RotateCamera(float angle, const glm::vec3& axis)
	{
		orientation = glm::rotate(orientation, angle, axis);
		Recalculate();
	}

private:
	void Recalculate()
	{
		forward = glm::vec3(orientation * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
		right = glm::normalize(glm::cross(forward, worldUp));
		up = glm::normalize(glm::cross(forward, right));
		viewMatrix = glm::lookAt(position, position + forward, worldUp);
	}


};

