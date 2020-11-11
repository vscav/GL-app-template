#ifndef _Program_HPP_
#define _Program_HPP_

#include "Shader.hpp"
#include "FilePath.hpp"

#include <GL/glew.h>

class Program
{
private:
	Program(const Program &);
	Program &operator=(const Program &);

	GLuint m_nGLId;

public:
	Program() : m_nGLId(glCreateProgram())
	{
	}

	~Program()
	{
		glDeleteProgram(m_nGLId);
	}

	Program(Program &&rvalue) : m_nGLId(rvalue.m_nGLId)
	{
		rvalue.m_nGLId = 0;
	}

	Program &operator=(Program &&rvalue)
	{
		m_nGLId = rvalue.m_nGLId;
		rvalue.m_nGLId = 0;
		return *this;
	}

	GLuint getGLId() const
	{
		return m_nGLId;
	}

	void attachShader(const Shader &shader)
	{
		glAttachShader(m_nGLId, shader.getGLId());
	}

	bool link();

	const std::string getInfoLog() const;

	void use() const
	{
		glUseProgram(m_nGLId);
	}
};

// Build a GLSL program from source code
Program buildProgram(const GLchar *vsSrc, const GLchar *fsSrc);

// Load source code from files and build a GLSL program
Program loadProgram(const FilePath &vsFile, const FilePath &fsFile);

#endif /* _Program_HPP_ */
