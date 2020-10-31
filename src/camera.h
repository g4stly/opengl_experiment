#ifndef camera_h_
#define camera_h_

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
	glm::vec3 up;
	glm::vec3 pos;
	glm::vec3 front;
	float pitch, yaw;
public:
	/*
	 * not actually rotation, just translate the point
	 * (on a 3d sphere around the camera origin) that
	 * the camera is pointing at
	 */
	void rotate(float dx, float dy);

	/*
	 * translate camera position
	 */
	void mv_fwrd(float speed);
	void mv_back(float speed);
	void mv_left(float speed);
	void mv_rght(float speed);
	void mv_down(float speed);
	void mv_up(float speed);

	/*
	 * return view matrix
	 */
	glm::mat4 get_view();

	Camera(float x, float y, float z);
};


#endif
