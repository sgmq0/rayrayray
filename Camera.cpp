#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

Camera::Camera() :
	pos(glm::vec3(0.0f, 0.0f, 3.0f)),
	front(glm::vec3(0.0f, 0.0f, -1.0f)),
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	right(glm::vec3(1.0f, 0.0f, 0.0f)),
	worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	cameraSpeed(0.05f),
	yaw(0.0f), pitch(0.0f)
{
	recomputeCam();
}

Camera::Camera(const glm::vec3 pos, const glm::vec3 front, const glm::vec3 worldUp) :
	pos(pos),
	front(front),
	worldUp(worldUp),
	cameraSpeed(0.05f),
	yaw(0.0f), pitch(0.0f)
{
	recomputeCam();
}

void Camera::processMouseMovement(float xOffset, float yOffset) {
	const float sensitivity = 0.1f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	// constrain pitch for gimbal lock
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	recomputeCam();
}

void Camera::recomputeCam() {
	glm::vec3 front2;
	front2.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front2.y = sin(glm::radians(pitch));
	front2.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front2);
	right = glm::normalize(glm::cross(front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getView() {
	return glm::lookAt(pos, pos + front, up);
}