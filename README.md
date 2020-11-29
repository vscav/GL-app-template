# OpenGL application template

> CMake OpenGL application template using GLFW, Glew and glm.

## Table of Contents

* [Get started](#get-started)
  * [Repository](#repository)
  * [Linux requirements](#linux-requirements)
* [Usage](#usage)
* [Features](#features)
* [Resources](#resources)

## Get started

### Repository

The template uses submodules for its main libraries.

So to clone the repository, use the following command:

```
$ git clone --recursive https://github.com/vscav/GL-app-template.git
```

Alternatively, if you don't used the --recursive option, you can later run:

```
$ git submodule init
$ git submodule update
```

### Linux requirements

Update package database:

```
$ sudo apt update
```

Install the updates identified previously:

```
$ sudo apt upgrade
```

Install g++ (C++ compiler):

```
$ sudo apt install g++
```

Install CMake:

```
$ sudo apt install cmake
```

## Usage

In the apllication directory, create the build folder and move into it:

```
$ mkdir build && cd build
```

Build and compile the template:

```
$ cmake ..
```

Run the executable by using this pattern:

```
$ ./app
```

The template uses Doxygen as its main documentation generator. If you have previously installed Doxygen, run the following command:

```
$ make doc
```

The documentation can be found in `build/doc/doc`. It is generated as html and LaTeX files.

## Usage

## Resources

- [OpenGL](https://www.khronos.org/registry/OpenGL-Refpages/gl4/) - OpenGL documentation
- [GLFW](https://www.glfw.org/documentation.html) - GLFW documentation
- [Doxygen](https://www.doxygen.nl/manual/index.html) - Doxygen documentation
- [CMake](https://cmake.org/cmake/help/v3.19/) - CMake documentation

