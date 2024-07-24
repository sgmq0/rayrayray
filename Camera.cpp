#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

Camera::Camera() :
	pos(glm::vec3(0.0f, 0.0f, 3.0f)),
	front(glm::vec3(0.0f, 0.0f, -1.0f)),
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	right(glm::vec3(1.0f, 0.0f, 0.0f)),
	cameraSpeed(0.05f)
{
}

Camera::Camera(const glm::vec3 pos, const glm::vec3 front, const glm::vec3 worldUp) :
	pos(pos),
	front(front),
	cameraSpeed(0.05f)
{
	glm::vec3 forward = glm::normalize(pos - front);
	right = glm::normalize(glm::cross(worldUp, forward));
	up = glm::normalize(glm::cross(forward, right));
}
