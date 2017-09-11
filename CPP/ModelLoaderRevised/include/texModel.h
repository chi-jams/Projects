#ifndef _TEX_MODEL_H
#define _TEX_MODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

#include "modelBasic.h"

class texModel: public modelBasic {

    public:
        texModel( std::string inputFile, GLenum primitive = GL_TRIANGLES );
        ~texModel();
        void draw( GLenum primitive );
        void draw( GLenum primitive, GLuint numElements );
    private:

        GLuint texCoordBuffer;

        
        bool loadFromFile( std::string inputFile,
                           std::vector<GLuint>& indices, 
                           std::vector<glm::vec4>& vertices,
                           std::vector<glm::vec2>& texCoords );
};

#endif