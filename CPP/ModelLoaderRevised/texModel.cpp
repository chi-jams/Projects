
#include "texModel.h"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

texModel::texModel( std::string inputFile, GLenum primitive ) {

    std::vector<GLuint> indices;
    std::vector<glm::vec4> vertices;
    std::vector<glm::vec2> texCoords;

    // Default the model matrix to an identity matrix
    modelMat = glm::mat4( 1.0f );

    // Load all of the model attributes from file
    if( loadFromFile( inputFile, indices, vertices, texCoords ) ) {
        
        /* Debug, print out the coordinates after we've got them */
        for( unsigned int i = 0; i < texCoords.size(); i++ ) {
            std::cout << texCoords[i][0] << ", " << texCoords[i][1] << std::endl;
        }

        for( unsigned int i = 0; i < vertices.size(); i++ ) {
            std::cout << vertices[i][0] << ", "
                      << vertices[i][1] << ", "
                      << vertices[i][2] << ", "
                      << vertices[i][3] << std::endl;
        }

        for( unsigned int i = 0; i < indices.size(); i++ ) {
            std::cout << indices[i];

            if( i % 3 == 2 )
                std::cout << std::endl;
            else
                std::cout << ", ";
        }

        // Build our object vertex array
        glGenVertexArrays( 1, &VAOptr );
        glBindVertexArray( VAOptr );

            //////////////
            // Vertices //
            //////////////

            glGenBuffers( 1, &vertexBuffer );
            glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
            glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( glm::vec4 ), 
                          &vertices[0][0], GL_STATIC_DRAW );

            // Vertex location
            glEnableVertexAttribArray( 0 );
            glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0 );

            /////////////////////////
            // Texture coordinates //
            /////////////////////////

            glGenBuffers( 1, &texCoordBuffer );
            glBindBuffer( GL_ARRAY_BUFFER, texCoordBuffer );
            glBufferData( GL_ARRAY_BUFFER, texCoords.size() * sizeof( glm::vec2 ),
                          &texCoords[0][0], GL_STATIC_DRAW );

            glEnableVertexAttribArray( 2 );
            glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, 0 );

            //////////////////
            // Model Matrix //
            //////////////////

            glGenBuffers( 1, &matrixBuffer );
            glBindBuffer( GL_ARRAY_BUFFER, matrixBuffer );

            glBufferData( GL_ARRAY_BUFFER, sizeof( glm::mat4 ), 
                          &modelMat[0][0], GL_STATIC_DRAW );

            int modelMatLoc = 6;            
            for( int i = 0; i < 4; i++ ) {

                glEnableVertexAttribArray( modelMatLoc + i );
                glVertexAttribPointer( modelMatLoc + i, 4, GL_FLOAT, GL_FALSE,
                                       sizeof( glm::mat4 ),
                                       (GLvoid*)( i * sizeof( glm::vec4 ) ) );
                glVertexAttribDivisor( modelMatLoc + i, 1 );
            }

            /////////////
            // Indices //
            /////////////

            // Indices of how the model is going to be drawn
            glGenBuffers( 1, &indicesVBOptr );
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indicesVBOptr );
            glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( GLuint ),
                          &indices[0], GL_STATIC_DRAW );

        glBindVertexArray( 0 );

        numIndices = indices.size();
    }
    // If we failed to load the file, there's not much we can do
    else {
        std::cout << "Something exploded!" << std::endl;
    }
}

texModel::~texModel() {
    glDeleteVertexArrays( 1, &VAOptr );
    glDeleteBuffers( 1, &vertexBuffer );
    glDeleteBuffers( 1, &matrixBuffer );
    glDeleteBuffers( 1, &indicesVBOptr );
}

void texModel::draw( GLenum primitive ) {

    glBindVertexArray( VAOptr );

        glDrawElementsInstanced( primitive, numIndices, GL_UNSIGNED_INT, 0, 1 );

    glBindVertexArray( 0 );
}

void texModel::draw( GLenum primitive, GLuint numElements ) {

    glBindVertexArray( VAOptr );

        glDrawElementsInstanced( primitive, numElements, GL_UNSIGNED_INT, 0, 1 );

    glBindVertexArray( 0 );
}

bool texModel::loadFromFile( std::string inputFile,
                             std::vector<GLuint>& indices,
                             std::vector<glm::vec4>& vertices,
                             std::vector<glm::vec2>& texCoords ) {

    std::ifstream fin( inputFile.c_str() );
    if( fin.fail() ) {
        std::cout << "Error! Failed to open " << inputFile << "!" << std::endl;
        return false;
    }
    else {

        int indicesPerPrimitive = 3;

        // Get all the indices that'll be put together as control points
        // For patches. They come in sets of 16
        int numPatches;
        fin >> numPatches;
        fin.ignore();
        for( int i = 0; i < numPatches; i++ ) {
            std::string input;
            for( int i = 0; i < indicesPerPrimitive - 1; i++ ) {
                getline( fin, input, ',' );

                // Bandage solutions are fun right?
                if( indicesPerPrimitive > 4 )
                    indices.push_back( atoi( input.c_str() ) - 1 );
                else
                    indices.push_back( atoi( input.c_str() ) );
            }
            getline( fin, input );
            if( indicesPerPrimitive > 4 )
                indices.push_back( atoi( input.c_str() ) - 1 );
            else
                indices.push_back( atoi( input.c_str() ) );

        }

        int numVertices;
        fin >> numVertices;
        //std::cout << "Number of vertices: " << numVertices << std::endl;
        
        for( int i = 0; i < numVertices; i++ ) {
            std::string input;
            glm::vec4 vertex = glm::vec4( 0.0, 0.0, 0.0, 1.0 );
            for( int i = 0; i < 2; i++ ) {
                getline( fin, input, ',' );
                vertex[i] = atof( input.c_str() );
            }
            getline( fin, input );
            vertex[2] = atof( input.c_str() );
            vertices.push_back( vertex );
        }

        for( int i = 0; i < numVertices; i++ ) {
            std::string input;
            glm::vec2 texCoord = glm::vec2( 0.0, 0.0 );
            getline( fin, input, ',' );
            texCoord[0] = atof( input.c_str() );
            getline( fin, input );
            texCoord[1] = atof( input.c_str() );
            texCoords.push_back( texCoord );
        }

        fin.close();

    }
    return true;
}