
#ifndef _MODEL_LOADER_H
#define _MODEL_LOADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "modelBasic.h"
#include "colorData.h"

// Loads in models from a text file and then draws them as-is
// Stores a model matrix that user can perform operations on to
// transform the object
class modelLoader: public modelBasic {
    
    public:

        modelLoader( std::string inputFile, GLenum primitive = GL_TRIANGLES );
        ~modelLoader();
        void draw( GLenum primitive );
        void draw( GLenum primitive, GLuint numElements );

        // Color modifications
        void setColor( colorData color );
        void setAmbColor( glm::vec4 amb );
        void setSpecColor( glm::vec4 spec );
        void setDiffColor( glm::vec4 diff );
        void setShininess( float shininess );

    private:

        // Data that's model specific that can change
        // over the lifetime of the model
        colorData modelColor;

        // VAO's/VBO's
        GLuint colorBuffer;

        bool loadFromFile( std::string inputFile, 
                           GLenum primitive,
                           std::vector<GLuint>& indices, 
                           std::vector<glm::vec4>& vertices );
        
        // Sends a new values to the GPU
        void updateColor();
};

#endif