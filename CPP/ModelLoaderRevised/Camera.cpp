
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <math.h>

#include <iostream>

Camera::Camera() {

    theta = 0.0;
    phi = 0.0;
    r = 5.0;

    computeArcballLocation();

    dir = glm::vec3( 0.0, 0.0, 0.0 );
    up  = glm::vec3( 0.0, 1.0, 0.0 );

    rotationScale = 0.01;

    closest = 2.0;
    farthest = 20.0;
}

Camera::Camera( float theta, float phi, float r, glm::vec3 dir, glm::vec3 up ) {

    *this = Camera();

    this->theta = theta;
    this->phi = phi;
    this->r = r;

    this->dir = dir;
    this->up = up;

    computeArcballLocation();
}

void Camera::computeArcballLocation() {

    // Bind our vertical rotation between straight up and straight down
    // We gave a nuber really close to straight up and straight down since straight
    // up and straight down both of pretty weird behavior
    if( phi < 0 + 0.001) {
        phi = 0.001;
    }
    else if( phi > M_PI - 0.001 ) {
        phi = M_PI - 0.001;
    }

    float x = r * sin( phi ) * sin( theta ),
          y = r * -cos( phi ),
          z = r * -sin( phi ) * cos( theta );

    pos = glm::vec3( x, y, z );
}

// Zooms the camera in and out based on 
// how far the mouse moves vertically
void Camera::zoom( double rChange ) {

    r += rChange;

    if( r < closest )
        r = closest;
    else if( r > farthest )
        r = farthest;
    
    computeArcballLocation();
}

void Camera::move( double xChange, double yChange ) {

    // Rotate the camera based on how far the mouse moved on the screen
    theta += rotationScale * ( xChange );
    // y rotation is inverted so up is to look up
    phi += rotationScale * ( yChange );            

    computeArcballLocation();

}

void Camera::updateTarget( glm::vec3 dir ) {

    this->dir = dir;
}

glm::mat4 Camera::viewMat() {

    return glm::lookAt( pos, dir, up );
}

glm::vec3 Camera::viewVec() {

    return glm::normalize( pos - dir );
}