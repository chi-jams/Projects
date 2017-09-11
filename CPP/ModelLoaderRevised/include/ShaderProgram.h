#pragma once

#include "ShaderUtils.h"

#include <GL/gl.h>
#include <string>

namespace CSCI441 {

	class ShaderProgram {
	public:
		ShaderProgram( const char *vertexShaderFilename,
					   const char *fragmentShaderFilename );

		ShaderProgram( const char *vertexShaderFilename,
					   const char *tesselationControlShaderFilename,
					   const char *tesselationEvaluationShaderFilename,
					   const char *geometryShaderFilename,
					   const char *fragmentShaderFilename );

		ShaderProgram( const char *vertexShaderFilename,
					   const char *geometryShaderFilename,
					   const char *fragmentShaderFilename );

		~ShaderProgram();

		// THIS WAS THROWN IN BY ME //
		// Code to accomodate uniform blocks
		GLuint getUniformBlockIndex( const char *uniformName );
		void uniformBlockBinding( GLuint blockLoc, GLuint blockIndex );
		void uniformBlockBinding( std::string blockName, GLuint blockIndex );

		GLint getUniformLocation( const char *uniformName );
		GLint getAttributeLocation( const char *attributeName );
		GLuint getSubroutineIndex( GLenum shaderStage, const char *subroutineName );

		GLuint getNumUniforms();
		GLuint getNumAttributes();

		void useProgram();
	private:
		ShaderProgram();

		GLuint _vertexShaderHandle;
		GLuint _tesselationControlShaderHandle;
		GLuint _tesselationEvaluationShaderHandle;
		GLuint _geometryShaderHandle;
		GLuint _fragmentShaderHandle;

		GLuint _shaderProgramHandle;

		bool registerShaderProgram( const char *vertexShaderFilename,
									const char *tesselationControlShaderFilename,
									const char *tesselationEvaluationShaderFilename,
									const char *geometryShaderFilename,
									const char *fragmentShaderFilename );
	};

}
