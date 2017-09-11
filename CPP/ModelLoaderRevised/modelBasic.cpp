
#include "modelBasic.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <iostream>

modelBasic::modelBasic() {
    modelMat = glm::mat4();

    VAOptr = 0;
    vertexBuffer = 0;
    matrixBuffer = 0;
    indicesVBOptr = 0;
    numIndices = 0;
}

modelBasic::~modelBasic() {
    glDeleteVertexArrays( 1, &VAOptr );
    glDeleteBuffers( 1, &vertexBuffer );
    glDeleteBuffers( 1, &matrixBuffer );
    glDeleteBuffers( 1, &indicesVBOptr );
}

void modelBasic::translate( glm::vec3 direction ) {
    modelMat = glm::translate( modelMat, direction );
    updateMat();
}

void modelBasic::rotate( GLfloat angle, glm::vec3 axis )  {
    modelMat = glm::rotate( modelMat, angle, axis );
    updateMat();
}

void modelBasic::scale( glm::vec3 scale ) {
    modelMat = glm::scale( modelMat, scale );
    updateMat();
}

void modelBasic::setMatrix( glm::mat4 model ) {
    modelMat = model;
    updateMat();
}

void modelBasic::updateMat() {
    glBindBuffer( GL_ARRAY_BUFFER, matrixBuffer );

    glBufferData( GL_ARRAY_BUFFER, sizeof( glm::mat4 ), 
                          &modelMat[0][0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}