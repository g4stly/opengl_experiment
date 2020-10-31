#include "camera.h"

void Camera::rotate(float dx, float dy)
{
	pitch -= dy;
	yaw = std::fmod(yaw + dx, 2*M_PI);
	if (pitch > 0.499*M_PI) pitch = (float)0.499*M_PI;
	if (pitch < -0.499*M_PI) pitch = (float)-0.499*M_PI;
}

void Camera::mv_fwrd(float speed)
{
	pos += speed * front;
}
void Camera::mv_back(float speed)
{
	pos -= speed * front;
}

void Camera::mv_left(float speed)
{
	pos -= glm::normalize(glm::cross(front, up)) * speed;
}

void Camera::mv_rght(float speed)
{
	pos += glm::normalize(glm::cross(front, up)) * speed;
}

void Camera::mv_down(float speed)
{
	pos -= glm::vec3(0, speed, 0);
}

void Camera::mv_up(float speed)
{
	pos += glm::vec3(0, speed, 0);
}

Camera::Camera(float x, float y, float z)
{
	pitch = 0;
	yaw = -0.5 * M_PI;
	up = glm::vec3(0, 1, 0);
	pos = glm::vec3(x, y, z);
	front = glm::vec3(0, 0, -1);
}

glm::mat4 Camera::get_view()
{
	front = glm::normalize(glm::vec3(
		cos(yaw) * cos(pitch),
		sin(pitch),
		sin(yaw) * cos(pitch)
	));
	return glm::lookAt(pos, pos + front, up);
}
