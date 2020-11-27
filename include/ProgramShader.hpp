#pragma once
#ifndef _ProgramShader_HPP_
#define _ProgramShader_HPP_

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
	ProgramShader(GLenum type);
	~ProgramShader();
	ProgramShader(ProgramShader &&rvalue);

	ProgramShader &operator=(ProgramShader &&rvalue)
	{
		m_nGLId = rvalue.m_nGLId;
		rvalue.m_nGLId = 0;
		return *this;
	}

	inline GLuint getGLId() const { return m_nGLId; };

	void setSource(const char *src);

	bool compile();

	const std::string getInfoLog() const;
};

// Load a shader (but does not compile it)
ProgramShader loadShader(GLenum type, const FilePath &filepath);

#endif /* _ProgramShader_HPP_ */
