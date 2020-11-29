#include "../../include/manager/InputManager.hpp"
#include "../../include/GLApplication.hpp"

namespace manager
{

	void InputManager::keyPressed(InputCodes code)
	{
		if (GLApplication::getInstance().getCamera() == nullptr)
			return;

		switch (code)
		{
		case Up:
		case W:
		case w:
			GLApplication::getInstance().getCamera()->moveFront(GLApplication::getInstance().getCamera()->getSpeed() * getCurrentDeltaTime());
			break;
		case Down:
		case S:
		case s:
			GLApplication::getInstance().getCamera()->moveFront(-1 * GLApplication::getInstance().getCamera()->getSpeed() * getCurrentDeltaTime());
			break;
		case Left:
		case A:
		case a:
			GLApplication::getInstance().getCamera()->moveLeft(GLApplication::getInstance().getCamera()->getSpeed() * getCurrentDeltaTime());
			break;
		case Right:
		case D:
		case d:
			GLApplication::getInstance().getCamera()->moveLeft(-1 * GLApplication::getInstance().getCamera()->getSpeed() * getCurrentDeltaTime());
			break;
		default:
			break;
		}
	}

	// This sends in an updated mouse x and y position that should be a delta from (0, 0)
	void InputManager::mouseMoved(float mouseX, float mouseY)
	{
		// Return if we don't have a valid camera assigned
		if (GLApplication::getInstance().getCamera() == nullptr)
			return;

		// Have our manager send the mouse x and y deltas to our camera to process the rotations
		GLApplication::getInstance().getCamera()->rotateLeft(mouseX);
		GLApplication::getInstance().getCamera()->rotateUp(mouseY);
	}

} // namespace manager