#pragma once
#ifndef _InputManager_HPP_
#define _InputManager_HPP_

#include "FreeflyCamera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

// This is a standardized enum to code for keyboard input, since Win32 and GLFW use some different codes
enum InputCodes
{
	kEscape = 27,
	Space = 32,
	Left = 37,
	Up = 38,
	Right = 39,
	Down = 40,
	a = 97,
	A = 65,
	b = 98,
	B = 66,
	c = 99,
	C = 67,
	d = 100,
	D = 68,
	e = 101,
	E = 69,
	f = 102,
	F = 70,
	g = 103,
	G = 71,
	h = 104,
	H = 72,
	i = 105,
	I = 73,
	j = 106,
	J = 74,
	k = 107,
	K = 75,
	l = 108,
	L = 76,
	m = 109,
	M = 77,
	n = 110,
	N = 78,
	o = 111,
	O = 79,
	p = 112,
	P = 80,
	q = 113,
	Q = 81,
	r = 114,
	R = 82,
	s = 115,
	S = 83,
	t = 116,
	T = 84,
	u = 117,
	U = 85,
	v = 118,
	V = 86,
	w = 119,
	W = 87,
	x = 120,
	X = 88,
	y = 121,
	Y = 89,
	z = 122,
	Z = 90,
};

// This manager takes care of any input from the user and sent to the camera.
class InputManager
{
protected:
	FreeflyCamera *m_camera;

public:
	void keyPressed(InputCodes code);
	void mouseMoved(float mouseX, float mouseY);

	inline void setCamera(FreeflyCamera *pCamera) { m_camera = pCamera; }
	inline const FreeflyCamera *getCamera() const { return m_camera; }
};

#endif /* _InputManager_HPP_ */