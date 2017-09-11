

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <math.h>
#include <iostream>
#include <vector>

#include "modelLoader.h"
#include "tessModel.h"
#include "colorData.h"
#include "Camera.h"
#include "OpenGLUtils.h"
#include "ShaderUtils.h"
#include "ShaderProgram.h"

//#include "texModel.h"
//#include "perlin.h"

/*** Make windows and initialize glew and opengl ***/
GLFWwindow* setupGLFW( int wWidth, int wHeight );
bool setupOpenGL();

void errorCallback( int error, const char* description );
void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
void mClickCallback( GLFWwindow* window, int button, int action, int mods );
void mMoveCallback( GLFWwindow* window, double xPos, double yPos );
void mScrollCallback( GLFWwindow* window, double xOffset, double yOffset );
void mWindowCallback( GLFWwindow* window, int width, int height );
/*** end init stuff ***/

Camera arcball( 0.66, 2.36, 12.0,
     glm::vec3( 0.0, 2.0, 0.0 ),
     glm::vec3( 0.0, 1.0, 0.0 ) );

double lastX = 0, lastY = 0;
bool buttonPressed = false;

glm::vec4 lightPos( 0.0, 7.0, 0.0, 1.0 );

float tessLvl = 10.0;
bool useWireframe = false;

const int LOWER_TESS_LVL = 0;
const int RAISE_TESS_LVL = 1;
bool keyPressed[2] = {false};

// Probs gonna have to stay here
int wWidth = 1280,
    wHeight = 720;

int main() {
        
    GLFWwindow *window = setupGLFW( wWidth, wHeight );
    if( window == NULL )
        return EXIT_FAILURE;

    if( !setupOpenGL() )
        return EXIT_FAILURE;

    //////////////////////////////
    // Load all shader programs //
    //////////////////////////////

    std::string bPShaders[3] = {
        "./shaders/BPhong.v.glsl",
        "./shaders/WireMesh.g.glsl",
        "./shaders/WireMesh.f.glsl"
    };
    CSCI441::ShaderProgram bPhong( bPShaders[0].c_str(),
                                   bPShaders[1].c_str(),
                                   bPShaders[2].c_str() );

    std::string tTShaders[5] = {
        "./shaders/bezier.v.glsl",
        "./shaders/bezier.tc.glsl",
        "./shaders/bezier.te.glsl",
        "./shaders/bezier.g.glsl",
        "./shaders/WireMesh.f.glsl"
    };
    CSCI441::ShaderProgram teaTess( tTShaders[0].c_str(),
                                    tTShaders[1].c_str(),
                                    tTShaders[2].c_str(),
                                    tTShaders[3].c_str(),
                                    tTShaders[4].c_str() );

    std::string pShaders[2] = {
        "./shaders/BPhong.v.glsl",
        "./shaders/points.f.glsl"
    };
    CSCI441::ShaderProgram makePts( pShaders[0].c_str(),
                                    pShaders[1].c_str() );

    
    std::string texShaders[5] = {
        "./shaders/bezier.v.glsl",
        "./shaders/bezier.tc.glsl",
        "./shaders/bezier.te.glsl",
        "./shaders/bezier.g.glsl",
        "./shaders/texPhong.f.glsl"
    };
    CSCI441::ShaderProgram texPhong( texShaders[0].c_str(),
                                    texShaders[1].c_str(),
                                    texShaders[2].c_str(),
                                    texShaders[3].c_str(),
                                    texShaders[4].c_str() );
                                     

    /////////////////////////////////
    // Make Uniform Buffer Objects //
    /////////////////////////////////

    glm::mat4 view = arcball.viewMat();
    glm::mat4 projection = glm::perspective( 45.0, (double)wWidth/wHeight, 0.1, 50.0 );

    // The uniform block location the matrices are being bound to
    GLuint matrixBlockIndex = 0;

    GLuint matrixBuffer;
    glGenBuffers( 1, &matrixBuffer );
    glBindBuffer( GL_UNIFORM_BUFFER, matrixBuffer );

        glBufferData( GL_UNIFORM_BUFFER, 2 * sizeof( glm::mat4 ) + sizeof( glm::vec3 ),
                      NULL, GL_DYNAMIC_DRAW );

        glBindBufferRange( GL_UNIFORM_BUFFER, matrixBlockIndex,
                           matrixBuffer, 0, 2 * sizeof( glm::mat4 ) );

        glBufferSubData( GL_UNIFORM_BUFFER, 0, 
                         sizeof( glm::mat4 ), &view[0][0] );
        glBufferSubData( GL_UNIFORM_BUFFER, sizeof( glm::mat4 ),
                         sizeof( glm::mat4 ), &projection[0][0] );
        glBufferSubData( GL_UNIFORM_BUFFER, 2 * sizeof( glm::mat4 ),
                         sizeof( glm::vec3 ), &(arcball.viewVec())[0]);

    glBindBuffer( GL_UNIFORM_BUFFER, 0 );

    // Get the location in memory of the light uniform block
    GLuint lightBlockIndex = 1;

    // Create a uniform buffer object that gets stored in index 0
    // of the uniform buffer object blocks
    GLuint lightBuffer;
    glGenBuffers( 1, &lightBuffer );
    glBindBuffer( GL_UNIFORM_BUFFER, lightBuffer );

        colorData lightProps = {
            glm::vec4( 0.8, 0.8, 0.8, 1.0 ),
            glm::vec4( 1.0, 1.0, 1.0, 1.0 ),
            glm::vec4( 0.8, 0.8, 0.8, 1.0 ),
            10.0
        };

        glBufferData( GL_UNIFORM_BUFFER, ( 4 * sizeof( glm::vec4 ) ) + sizeof( GLfloat ), 
                      NULL, GL_DYNAMIC_DRAW );
        glBindBufferRange( GL_UNIFORM_BUFFER, lightBlockIndex, 
                      lightBuffer, 0, ( 4 * sizeof( glm::vec4 ) ) + sizeof( GLfloat ) );
        
        // REMEMBER THAT UNIFORM BLOCKS DO THIS BS LAYOUT DEALIO
        // Items are spaced in multiples of 2, 
        // which means vec3 actually has offset n*vec4
        glBufferSubData( GL_UNIFORM_BUFFER, 0, 
                         sizeof( glm::vec4 ), &lightPos[0] );
        glBufferSubData( GL_UNIFORM_BUFFER, sizeof( glm::vec4 ), 
                         sizeof( glm::vec4 ), &lightProps.amb );
        glBufferSubData( GL_UNIFORM_BUFFER, 2 * sizeof( glm::vec4 ), 
                         sizeof( glm::vec4 ), &lightProps.spec );
        glBufferSubData( GL_UNIFORM_BUFFER, 3 * sizeof( glm::vec4 ), 
                         sizeof( glm::vec4 ), &lightProps.diff );
        glBufferSubData( GL_UNIFORM_BUFFER, 4 * sizeof( glm::vec4 ), 
                         sizeof( GLfloat ), &lightProps.shininess );

    glBindBuffer( GL_UNIFORM_BUFFER, 0 );


    /////////////////////////////////////
    // Bind uniform blocks to programs //
    //      Get uniforms as well       //
    /////////////////////////////////////

    bPhong.useProgram(); 

        bPhong.uniformBlockBinding( "Matrices", matrixBlockIndex );
        
        GLuint bPuseWf = bPhong.getUniformLocation( "useWireframe" );
        glUniform1i( bPuseWf, useWireframe );
        
        bPhong.uniformBlockBinding( "Light", lightBlockIndex );

    glUseProgram( 0 );

    teaTess.useProgram();

        teaTess.uniformBlockBinding( "Matrices", matrixBlockIndex );

        GLuint tTuseWf = teaTess.getUniformLocation( "useWireframe" );
        glUniform1i( tTuseWf, useWireframe );

        GLuint tTTessLvlLoc = teaTess.getUniformLocation( "tessLevel" );
        glUniform1f( tTTessLvlLoc, tessLvl );

        teaTess.uniformBlockBinding( "Light", lightBlockIndex );

    glUseProgram( 0 );

    makePts.useProgram();

        glPointSize( 5.0 );
        makePts.uniformBlockBinding( "Matrices", matrixBlockIndex );

    glUseProgram( 0 );

    
    texPhong.useProgram();

        GLuint tPTessLvlLoc = texPhong.getUniformLocation( "tessLevel" );
        glUniform1f( tPTessLvlLoc, tessLvl );

        texPhong.uniformBlockBinding( "Matrices", matrixBlockIndex );

        texPhong.uniformBlockBinding( "Light", lightBlockIndex ); 

        std::cout << "OpenGL Error: " << glGetError() << std::endl;       

    glUseProgram( 0 );
    

    ////////////////////////////////////
    // Load in & configure all models //
    ////////////////////////////////////

    tessModel teapot = tessModel( "models/teapot.model" );
    /* Old, pretty blue teapot color
    colorData teapotColor = {
        glm::vec4( 0.0, 0.1, 0.06, 1.0 ),
        glm::vec4( 0.50754, 0.50754, 0.50754, 1.0 ),
        glm::vec4( 0.0, 0.50980392, 0.50980392, 1.0 ),
        32.0
    };
    */
    colorData teapotColor = {
        glm::vec4( 0.0, 0.0, 0.00, 1.0 ),
        glm::vec4( 0.50754, 0.50754, 0.50754, 1.0 ),
        glm::vec4( 0.1, 0.1, 0.1, 1.0 ),
        32.0
    };
    teapot.setColor( teapotColor );
    teapot.translate( glm::vec3( 0.0, 1.0, 0.0 ) );
    //teapot.rotate( 90.0 / 180.0 * M_PI, glm::vec3( -1.0, 0.0, 0.0 ) );    

    modelLoader cube = modelLoader( "models/cube.model" );
    colorData cubeColor = {
        glm::vec4( 0.4, 0.0, 0.4, 1.0 ),
        glm::vec4( 0.5, 0.5, 0.5, 1.0 ),
        glm::vec4( 1.0, 0.0, 1.0, 1.0 ),
        10.0
    };
    cube.setColor( cubeColor );
    
    cube.translate( lightPos );
    
    modelLoader plane = modelLoader( "models/plane.model" );
    colorData planeColor = {
        glm::vec4( 0.0, 0.05, 0.05, 1.0 ),
        glm::vec4( 0.4, 0.5, 0.5, 1.0 ),
        glm::vec4( 0.04, 0.7, 0.7, 1.0 ),
        100.0
    };
    plane.setColor( planeColor );
    plane.scale( glm::vec3( 20.0, 20.0, 20.0 ) );

    // LOOP DE LOOP
    while( !glfwWindowShouldClose( window ) ) {

        // Actively get key inputs
        glfwPollEvents();

        if( keyPressed[ RAISE_TESS_LVL ] && tessLvl < 63.0 ) {
            tessLvl += 0.01;
        }
        else if( keyPressed[ LOWER_TESS_LVL ] && tessLvl > 1.0 ) {
            tessLvl -= 0.01;
        }

        // Reset the Screen to all black
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // Gotta update this when the camera moves
        view = arcball.viewMat();
        glBindBuffer( GL_UNIFORM_BUFFER, matrixBuffer );
            glBufferSubData( GL_UNIFORM_BUFFER, 0,
                             sizeof( glm::mat4 ), &view[0][0] );

            glBufferSubData( GL_UNIFORM_BUFFER, 2 * sizeof( glm::mat4 ) ,
                             sizeof( glm::vec3 ), &(arcball.viewVec())[0] );

        glBindBuffer( GL_UNIFORM_BUFFER, 0 );

        // Make light move in a circle to get that whole dynamic light feel
        glm::vec4 lightRev = glm::vec4( 5.0 * cos( glfwGetTime() ), 0.0, 
                                        5.0 * sin( glfwGetTime() ), 1.0 );
        lightRev += lightPos;
        glBindBuffer( GL_UNIFORM_BUFFER, lightBuffer );
            glBufferSubData( GL_UNIFORM_BUFFER, 0,
                             sizeof( glm::vec4 ), &lightRev[0] );
        glBindBuffer( GL_UNIFORM_BUFFER, 0 );

        // Draw a cube around where the light is so we know where it's at
        glm::mat4 newPos( 1.0 );
        newPos = glm::translate( newPos, glm::vec3( lightRev ) );
        cube.setMatrix( newPos );        
        
        // Draw using basic bPhong
        bPhong.useProgram();            

            glUniform1i( bPuseWf, useWireframe );        

            plane.draw( GL_TRIANGLES );

        glUseProgram( 0 );

        // Draw control points and wire cages
        makePts.useProgram();

            cube.draw( GL_LINE_STRIP );

            if( useWireframe )
                teapot.drawCtrlPts( GL_POINTS );

        glUseProgram( 0 );

        // Draw the tessellated stuff
        teaTess.useProgram();

            glUniform1f( tTTessLvlLoc, tessLvl );
            glUniform1i( tTuseWf, useWireframe );

            //teapot.draw();

        glUseProgram( 0 );

        texPhong.useProgram();

            glUniform1f( tPTessLvlLoc, tessLvl );
            teapot.draw();

        glUseProgram( 0 );
        
        glfwSwapBuffers( window );
    }

    glfwDestroyWindow( window );
    glfwTerminate();

	return 0;
}

GLFWwindow* setupGLFW( int wWidth, int wHeight ) {

    glfwSetErrorCallback( errorCallback );

    // Fire up GLFW, if it fails kill the program
    if( !glfwInit() ) {

        std::cout << "Error! Failed to initialize glfw!" << std::endl;
        return NULL;
    }
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    //glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

    GLFWwindow* window = NULL;
    window = glfwCreateWindow( wWidth, wHeight, "Procedural Textures", NULL, NULL );

    glfwMakeContextCurrent( window );

    int fbWidth, fbHeight;
    glfwGetFramebufferSize( window, &fbWidth, &fbHeight );

    glViewport( 0, 0, fbWidth, fbHeight );

    glfwSetKeyCallback( window, keyCallback );
    glfwSetMouseButtonCallback( window, mClickCallback );
    glfwSetCursorPosCallback( window, mMoveCallback );
    glfwSetScrollCallback( window, mScrollCallback );
    glfwSetWindowSizeCallback( window, mWindowCallback );

    glfwSetWindowAspectRatio( window, 16, 9 );

    // The wonders of working with state machines and dynamic memory allocation
    return window;
}

bool setupOpenGL() {
    
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    glCullFace( GL_BACK );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

    glewExperimental = GL_TRUE; // I don't know what this black magic is
    GLenum err = glewInit();
    if( err != GLEW_OK ) {
        std::cout << "Error initializing GLEW: ";
        std::cout << glewGetErrorString( err ) << std::endl;
        return false;
    } else if( GLEW_VERSION_4_1 ) {
        std::cout << "Device supports OpenGL 4.1" << std::endl;
    } else {
        std::cout << "Device does not support OpenGL 4.1. Exiting." << std::endl;
        return false;
    }

    CSCI441::OpenGLUtils::printOpenGLInfo();

    return true;
}

// Anytime a GLFW error happens this function is called
void errorCallback( int error, const char* description ) {

    std::string errDesc = description;
    std::cout << "GLFW Error!: " << std::endl << errDesc << std::endl;
}

////////////////////////////
// USER INPUTS BELOW HERE //
////////////////////////////

void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods ) {
    
    if( action == GLFW_PRESS ) {
        if( key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q )
            glfwSetWindowShouldClose( window, true );

        if( key == GLFW_KEY_W ) {
            lightPos += glm::vec4( 0.0, 0.0, 1.0, 0.0 );
        }
        else if( key == GLFW_KEY_S ) {
            lightPos -= glm::vec4( 0.0, 0.0, 1.0, 0.0 );
        }

        if( key == GLFW_KEY_A ) {
            lightPos += glm::vec4( 1.0, 0.0, 0.0, 0.0 );
        }
        else if( key == GLFW_KEY_D ) {
            lightPos -= glm::vec4( 1.0, 0.0, 0.0, 0.0 );
        }

        if( key == GLFW_KEY_SPACE ) {
            lightPos += glm::vec4( 0.0, 1.0, 0.0, 0.0 );
        }
        else if( key == GLFW_KEY_LEFT_CONTROL ) {
            lightPos -= glm::vec4( 0.0, 1.0, 0.0, 0.0 );
        }
        else if( key == GLFW_KEY_F ) {
            useWireframe = !useWireframe;
        }
        else if( key == GLFW_KEY_MINUS ) {
            keyPressed[ LOWER_TESS_LVL ] = true;
        }
        else if( key == GLFW_KEY_EQUAL ) {
            keyPressed[ RAISE_TESS_LVL ] = true;
        }
    }
    else if( action == GLFW_RELEASE ) {
        if( key == GLFW_KEY_MINUS ) {
            keyPressed[ LOWER_TESS_LVL ] = false;
        }
        else if( key == GLFW_KEY_EQUAL ) {
            keyPressed[ RAISE_TESS_LVL ] = false;
        }
    }
        

}

void mClickCallback( GLFWwindow* window, int button, int action, int mods ) {

    if( action == GLFW_PRESS )
        buttonPressed = true;
    else if( action == GLFW_RELEASE )
        buttonPressed = false;
}

void mMoveCallback( GLFWwindow* window, double xPos, double yPos ) {

    if( buttonPressed ) {
        arcball.move( xPos - lastX, yPos - lastY );
    }

    lastX = xPos;
    lastY = yPos;
}

void mScrollCallback( GLFWwindow* window, double xOffset, double yOffset ) {

    arcball.zoom( yOffset );
}

void mWindowCallback( GLFWwindow* window, int width, int height ) {

    wWidth = width;
    wHeight = height;

    glViewport( 0, 0, width, height );
}