#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Camera {

public:
	Camera();
	Camera(const glm::vec3 pos, const glm::vec3 front, const glm::vec3 worldUp);

	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	float cameraSpeed;
};

#endif