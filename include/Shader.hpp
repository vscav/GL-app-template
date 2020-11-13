#pragma once
#ifndef _Shader_HPP_
#define _Shader_HPP_

#include "FilePath.hpp"

#include <GL/glew.h>

#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>

#define GLIMAC_SHADER_SRC(str) #str

class Shader
{
private:
	Shader(const Shader &);
	Shader &operator=(const Shader &);

	GLuint m_nGLId;

public:
	Shader(GLenum type) : m_nGLId(glCreateShader(type))
	{
	}

	~Shader()
	{
		glDeleteShader(m_nGLId);
	}

	Shader(Shader &&rvalue) : m_nGLId(rvalue.m_nGLId)
	{
		rvalue.m_nGLId = 0;
	}

	Shader &operator=(Shader &&rvalue)
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
Shader loadShader(GLenum type, const FilePath &filepath);

#endif /* _Shader_HPP_ */
