#pragma once
#ifndef _ProgramShader_HPP_
#define _Shader_HPP_

#include "FilePath.hpp"

#include <GL/glew.h>

#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>

#define GLIMAC_SHADER_SRC(str) #str

class ProgramShader
{
private:
	ProgramShader(const ProgramShader &);
	ProgramShader &operator=(const ProgramShader &);

	GLuint m_nGLId;

public:
	ProgramShader(GLenum type) : m_nGLId(glCreateShader(type))
	{
	}

	~ProgramShader()
	{
		glDeleteShader(m_nGLId);
	}

	ProgramShader(ProgramShader &&rvalue) : m_nGLId(rvalue.m_nGLId)
	{
		rvalue.m_nGLId = 0;
	}

	ProgramShader &operator=(ProgramShader &&rvalue)
	{
		m_nGLId = rvalue.m_nGLId;
		rvalue.m_nGLId = 0;
		return *this;
	}

	GLuint getGLId() const
	{
		return m_nGLId;
	}

	void setSource(const char *src)
	{
		glShaderSource(m_nGLId, 1, &src, 0);
	}

	bool compile();

	const std::string getInfoLog() const;
};

// Load a shader (but does not compile it)
ProgramShader loadShader(GLenum type, const FilePath &filepath);

#endif /* _ProgramShader_HPP_ */
