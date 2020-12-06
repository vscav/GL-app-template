#pragma once
#ifndef _InputManager_HPP_
#define _InputManager_HPP_

#include "TimeManager.hpp"

#include "../dependencies/glm.hpp"

#include <functional>
#include <map>
#include <vector>

namespace manager
{

	/// \brief A standardized enum to code for keyboard inputs.
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

	/// \class InputManager
	/// \brief Class used to represent the input manager of the application. It allows us to abstract the input away from the WindowManager.
	class InputManager
	{
	public:
		/// \brief This fires an action depending on the key code received.
		/// \param code : The key code captured.
		void keyPressed(InputCodes code);
		/// \brief This sends in an updated mouse x and y position that should be a delta from (0, 0).
		/// \param mouseX : The X position of the mouse relative to the screen.
		/// \param mouseY : The Y position of the mouse relative to the screen..
		void mouseMoved(float mouseX, float mouseY);
	};

} // namespace manager

#endif /* _InputManager_HPP_ */