#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Camera {
public:
	Camera();
	Camera(const glm::vec3 _pos, const glm::vec3 _rot, const float _FOV, const float _AR, const float _zNear, const float _zFar);

	void MoveCamera(const glm::vec3 _pos);
	void RotateCamera(const glm::vec3 _rot);

	glm::mat4 GetCameraViewMatrix();
	glm::mat4 GetCameraProjectMatrix();

private:

	glm::vec3 cameraPosition;
	glm::vec3 cameraRotation;

	float FOV;
	float AR;
	float zNear;
	float zFar;
};

#endif