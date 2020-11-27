#pragma once
#ifndef _Program_HPP_
#define _Program_HPP_

#include "ProgramShader.hpp"
#include "FilePath.hpp"

#include <GL/glew.h>

#include <stdexcept>

class Program
{
private:
	Program(const Program &);
	Program &operator=(const Program &);

	GLuint m_nGLId;

public:
	Program();
	~Program();
	Program(Program &&rvalue);

	Program &operator=(Program &&rvalue)
	{
		m_nGLId = rvalue.m_nGLId;
		rvalue.m_nGLId = 0;
		return *this;
	}

	inline GLuint getGLId() const { return m_nGLId; };

	void attachShader(const ProgramShader &shader);

	bool link();

	const std::string getInfoLog() const;

	void use() const;
};

// Build a GLSL program from source code
Program buildProgram(const GLchar *vsSrc, const GLchar *fsSrc);

// Load source code from files and build a GLSL program
Program loadProgram(const FilePath &vsFile, const FilePath &fsFile);

#endif /* _Program_HPP_ */
