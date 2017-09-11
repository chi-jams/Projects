
#ifndef _MODEL_BASIC_H
#define _MODEL_BASIC_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

// Loads in models from a text file and then draws them as-is
// Stores a model matrix that user can perform operations on to
// transform the object
class modelBasic {
    
    public:

        modelBasic();
        ~modelBasic();
        
        void draw( GLenum primitive );
        void draw( GLenum primitive, GLuint numElements );

        // model matrix modifications
        void translate( glm::vec3 direction );
        void rotate( GLfloat angle, glm::vec3 axis );
        void scale( glm::vec3 scale );
        void setMatrix( glm::mat4 model );

    protected:

        // Data that's model specific that can change
        // over the lifetime of the model
        glm::mat4 modelMat;

        // VAO's/VBO's
        GLuint VAOptr;
        GLuint vertexBuffer;
        GLuint matrixBuffer;
        GLuint indicesVBOptr;

        // The number of indices in the element array buffer
        // Important for when you call glDrawElements
        GLuint numIndices;

        // Sends a new values to the GPU
        void updateMat();
};

#endif