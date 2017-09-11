
#ifndef _TESS_MODEL_H
#define _TESS_MODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "modelBasic.h"
#include "colorData.h"

// Loads and draws a tessellated object
// Same exact thing as modelLoader except
// for the draw call
// I should make a superclass... 
class tessModel: public modelBasic {
    
    public:

        tessModel( std::string inputFile );
        ~tessModel();
        void draw();
        void draw( GLuint numElements );
        void drawCtrlPts( GLenum primitive );

        // Color modifications
        void setColor( colorData color );
        void setAmbColor( glm::vec4 amb );
        void setSpecColor( glm::vec4 spec );
        void setDiffColor( glm::vec4 diff );
        void setShininess( float shininess );

    private:

        // Data that's model specific that can change
        // over the lifetime of the model
        //glm::mat4 modelMat;
        colorData modelColor;

        // VAO's/VBO's
        GLuint colorBuffer;
        
        bool loadFromFile( std::string inputFile,
                           std::vector<GLuint>& indices, 
                           std::vector<glm::vec4>& vertices );

        // Sends a new values to the GPU
        void updateColor();
};

#endif