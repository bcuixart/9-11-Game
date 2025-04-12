#include "Camera.hh"

#include <iostream>
using namespace std;

Camera::Camera() 
{

}

Camera::Camera(const glm::vec3 _pos, const glm::vec3 _rot, const float _FOV, const float _AR, const float _zNear, const float _zFar)
{
    cameraPosition = _pos;
    cameraRotation = _rot;

    FOV = _FOV;
    AR = _AR;
    zNear = _zNear;
    zFar = _zFar;
}

void Camera::MoveCamera(const glm::vec3 _pos) 
{
	cameraPosition = _pos;
}

void Camera::RotateCamera(const glm::vec3 _rot)
{
    cameraRotation = _rot;
}

glm::mat4 Camera::GetCameraViewMatrix()
{
    glm::vec3 rotation = glm::radians(cameraRotation);

    glm::mat4 view = glm::mat4(1.0f);

    view = glm::rotate(view, -rotation.x, glm::vec3(1, 0, 0));
    view = glm::rotate(view, -rotation.y, glm::vec3(0, 1, 0));
    view = glm::rotate(view, -rotation.z, glm::vec3(0, 0, 1));

    view = glm::translate(view, -cameraPosition);

    return view;
}

glm::mat4 Camera::GetCameraProjectMatrix()
{
    return glm::perspective(glm::radians(FOV), AR, zNear, zFar);
}