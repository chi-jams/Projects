
#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

    public:
        Camera();
        Camera( float theta, float phi, float r, glm::vec3 dir, glm::vec3 up );

        void zoom( double rChange );
        void move( double xChange, double yChange );

        void updateTarget( glm::vec3 dir );

        glm::mat4 viewMat();
        glm::vec3 viewVec();

    private:
        glm::vec3 pos;
        glm::vec3 dir;
        glm::vec3 up;

        float theta, phi, r;

        float rotationScale;

        float closest, farthest;

        void computeArcballLocation(); 
};

#endif