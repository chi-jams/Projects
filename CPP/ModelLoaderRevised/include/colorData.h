#ifndef _COLOR_DATA_H
#define _COLOR_DATA_H

#include <glm/glm.hpp>

struct colorData {

    glm::vec4 amb;
    glm::vec4 spec;
    glm::vec4 diff;
    float shininess;
};

#endif