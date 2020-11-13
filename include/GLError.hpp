#pragma once#pragma once
#ifndef _GLError_HPP_
#define _GLError_HPP_

#include <GL/glew.h>

#include <iostream>
#include <string>

void glCheckError(const char *file, unsigned int line);

#endif /* _GLError_HPP_ */
