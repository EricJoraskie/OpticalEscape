#include "Camera.h"

#include "glm/gtx/transform.hpp"

#include <iostream>

// Camera constructor
Camera::Camera(){
    // std::cout << "(Camera.cpp) Constructor called\n";
    eyePosition = glm::vec3(0.0f,0.0f,0.0f); // FIX: Typically this should be 0,0,0, but I moved for our assignment.
    viewDirection = glm::vec3(0.0f,0.0f, -1.0f);
    upVector = glm::vec3(0.0f, 1.0f, 0.0f);

}

// I recycled my original mouse look from when we first implemented it because
// it worked better (no offense)
void Camera::mouseLook(int mouseX, int mouseY){
    if (firstMouse)
    {
        oldMousePosition.x = mouseX;
        oldMousePosition.y = mouseY;
        firstMouse = false;
    }
    // We find the difference between the old and new mouse positions
    float xoffset = mouseX - oldMousePosition.x;
    float yoffset = oldMousePosition.y - mouseY;
    // We then set the old mouse positions to the mouse position for next motion
    oldMousePosition.x = mouseX;
    oldMousePosition.y = mouseY;
    // The sensitivity took some playing with to find what seemed to make sense.
    float sensitivity = 0.62f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    // We have some camera level yaw and pitch variables (I set yaw to -90
    // so that the camera would be centered correctly on first movement, 
    // then realized they suggested that in the tutorial!)
    yaw   += xoffset;
    pitch += yoffset;
    // This restricts the camera from going past completely vertical or
    // past looking straight down
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    // Now the magic... 
    // We're setting the x view to the cos of the pitch and yaw to account to 
    viewDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    viewDirection.y = sin(glm::radians(pitch));
    viewDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}

void Camera::moveForward(float speed){
    eyePosition.z -= speed;
}

void Camera::moveBackward(float speed){
    eyePosition.z += speed;
}

void Camera::moveLeft(float speed){
    eyePosition.x -= speed;
}

void Camera::moveRight(float speed){
    eyePosition.x += speed;
}

void Camera::moveUp(float speed){
    eyePosition.y += speed;
}

void Camera::moveDown(float speed){
    eyePosition.y -= speed;
}

float Camera::getEyeXPosition(){
    return eyePosition.x;
}

float Camera::getEyeYPosition(){
    return eyePosition.y;
}

float Camera::getEyeZPosition(){
    return eyePosition.z;
}

float Camera::getViewXDirection(){
    return viewDirection.x;
}

float Camera::getViewYDirection(){
    return viewDirection.y;
}

float Camera::getViewZDirection(){
    return viewDirection.z;
}

void::Camera::lookFront() {
    viewDirection = glm::vec3(0, 0, -1.0f);
    yaw = -90.0f;
    pitch = 0.0f;
}


// Get our view matrix from this camera
glm::mat4 Camera::getWorldToViewmatrix() const{
    // Think about the second argument and why that is
    // setup as it is.
    return glm::lookAt( eyePosition,
                        eyePosition + viewDirection,
                        upVector);
}
