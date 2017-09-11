#include "../include/ShaderProgram.h"

#include <stdio.h>
#include <string.h>

CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, 
									   const char *fragmentShaderFilename ) {
	registerShaderProgram( vertexShaderFilename, "", "", "", fragmentShaderFilename );
}

CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, 
									   const char *tesselationControlShaderFilename, 
									   const char *tesselationEvaluationShaderFilename, 
									   const char *geometryShaderFilename, 
									   const char *fragmentShaderFilename ) {
	registerShaderProgram( vertexShaderFilename, 
						   tesselationControlShaderFilename, 
						   tesselationEvaluationShaderFilename, 
						   geometryShaderFilename, 
						   fragmentShaderFilename );
}

CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, 
									   const char *geometryShaderFilename, 
									   const char *fragmentShaderFilename ) {
	registerShaderProgram( vertexShaderFilename, 
						   "", 
						   "", 
						   geometryShaderFilename, 
						   fragmentShaderFilename );
}

bool CSCI441::ShaderProgram::registerShaderProgram( const char *vertexShaderFilename, 
													const char *tesselationControlShaderFilename, 
													const char *tesselationEvaluationShaderFilename, 
													const char *geometryShaderFilename, 
													const char *fragmentShaderFilename ) {
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	printf( "\n[INFO]: /--------------------------------------------------------\\\n");

	/* compile each one of our shaders */
	printf( "[INFO]: | Vertex Shader: %39s |\n", vertexShaderFilename );
	_vertexShaderHandle = CSCI441::ShaderUtils::compileShader( vertexShaderFilename, 
															   GL_VERTEX_SHADER   );

	if( strcmp( tesselationControlShaderFilename, "" ) != 0 ) {
		printf( "[INFO]: | Tess Control Shader: %33s |\n", tesselationControlShaderFilename );
		if( major < 4 ) {
			printf( "[ERROR]:|   TESSELATION SHADER NOT SUPPORTED!!  UPGRADE TO v4.0+ |\n" );
			_tesselationControlShaderHandle = 0;
		} else {
			_tesselationControlShaderHandle = CSCI441::ShaderUtils::compileShader( tesselationControlShaderFilename, GL_TESS_CONTROL_SHADER );
		}
	} else {
		_tesselationControlShaderHandle = 0;
	}

	if( strcmp( tesselationEvaluationShaderFilename, "" ) != 0 ) {
		printf( "[INFO]: | Tess Evaluation Shader: %30s |\n", tesselationEvaluationShaderFilename );
		if( major < 4 ) {
			printf( "[ERROR]:|   TESSELATION SHADER NOT SUPPORTED!!  UPGRADE TO v4.0+ |\n" );
			_tesselationEvaluationShaderHandle = 0;
		} else {
			_tesselationEvaluationShaderHandle = CSCI441::ShaderUtils::compileShader( tesselationEvaluationShaderFilename, GL_TESS_EVALUATION_SHADER );
		}
	} else {
		_tesselationEvaluationShaderHandle = 0;
	}

	if( strcmp( geometryShaderFilename, "" ) != 0 ) {
		printf( "[INFO]: | Geometry Shader: %37s |\n", geometryShaderFilename );
		if( major < 3 ) {
			printf( "[ERROR]:|   GEOMETRY SHADER NOT SUPPORTED!!!    UPGRADE TO v3.0+ |\n" );
			_geometryShaderHandle = 0;
		} else {
			_geometryShaderHandle = CSCI441::ShaderUtils::compileShader( geometryShaderFilename, GL_GEOMETRY_SHADER );
		}
	} else {
		_geometryShaderHandle = 0;
	}

	printf( "[INFO]: | Fragment Shader: %37s |\n", fragmentShaderFilename );
	_fragmentShaderHandle = CSCI441::ShaderUtils::compileShader( fragmentShaderFilename, GL_FRAGMENT_SHADER );

	/* get a handle to a shader program */
	_shaderProgramHandle = glCreateProgram();

	/* attach the vertex and fragment shaders to the shader program */
	glAttachShader( _shaderProgramHandle, _vertexShaderHandle );
	if( _tesselationControlShaderHandle != 0 ) {
		glAttachShader( _shaderProgramHandle, _tesselationControlShaderHandle );
	}
	if( _tesselationEvaluationShaderHandle != 0 ) {
		glAttachShader( _shaderProgramHandle, _tesselationEvaluationShaderHandle );
	}
	if( _geometryShaderHandle != 0 ) {
		glAttachShader( _shaderProgramHandle, _geometryShaderHandle );
	}
	glAttachShader( _shaderProgramHandle, _fragmentShaderHandle );

	/* link all the programs together on the GPU */
	glLinkProgram( _shaderProgramHandle );

	printf( "[INFO]: | Shader Program: %41s", "|\n" );

	/* check the program log */
	CSCI441::ShaderUtils::printLog( _shaderProgramHandle );

	/* print shader info for uniforms & attributes */
	CSCI441::ShaderUtils::printShaderInfo( _shaderProgramHandle );

	/* return handle */
	return _shaderProgramHandle != 0;
}

// STUFF ADDED //
// Code to accomodate uniform block objects
GLuint CSCI441::ShaderProgram::getUniformBlockIndex( const char *uniformName ) {
	return glGetUniformBlockIndex( _shaderProgramHandle, uniformName );
}

void CSCI441::ShaderProgram::uniformBlockBinding( GLuint blockLoc, GLuint blockIndex ) {
	glUniformBlockBinding( _shaderProgramHandle, blockLoc, blockIndex );
}

void CSCI441::ShaderProgram::uniformBlockBinding( std::string blockName, GLuint blockIndex ) {

	GLuint blockLoc = getUniformBlockIndex( blockName.c_str() );
	uniformBlockBinding( blockLoc, blockIndex );
}

// End added stuff

GLint CSCI441::ShaderProgram::getUniformLocation( const char *uniformName ) {
	return glGetUniformLocation( _shaderProgramHandle, uniformName );
}


GLint CSCI441::ShaderProgram::getAttributeLocation( const char *attributeName ) {
	return glGetAttribLocation( _shaderProgramHandle, attributeName );
}

GLuint CSCI441::ShaderProgram::getSubroutineIndex( GLenum shaderStage, const char *subroutineName ) {
	return glGetSubroutineIndex( _shaderProgramHandle, shaderStage, subroutineName );
} 

GLuint CSCI441::ShaderProgram::getNumUniforms() {
	int numUniform = 0;
	glGetProgramiv( _shaderProgramHandle, GL_ACTIVE_UNIFORMS, &numUniform );
	return numUniform;
}

GLuint CSCI441::ShaderProgram::getNumAttributes() {
	int numAttr = 0;
	glGetProgramiv( _shaderProgramHandle, GL_ACTIVE_ATTRIBUTES, &numAttr );
	return numAttr;
}

void CSCI441::ShaderProgram::useProgram() {
	glUseProgram( _shaderProgramHandle );
}

CSCI441::ShaderProgram::ShaderProgram() {}

CSCI441::ShaderProgram::~ShaderProgram() {
	glDeleteShader( _vertexShaderHandle );
	glDeleteShader( _tesselationControlShaderHandle );
	glDeleteShader( _tesselationEvaluationShaderHandle );
	glDeleteShader( _geometryShaderHandle );
	glDeleteShader( _fragmentShaderHandle );
	glDeleteProgram( _shaderProgramHandle );
}
