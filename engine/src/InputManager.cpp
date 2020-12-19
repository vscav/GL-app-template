#include <engine/InputManager.hpp>
#include <engine/GLApplication.hpp>

namespace engine
{

	void InputManager::keyPressed(InputCodes code)
	{
		if (GLApplication::getInstance().getCamera() == nullptr)
			return;

		switch (code)
		{
		case Up:
			GLApplication::getInstance().getCamera()->moveFront(GLApplication::getInstance().getCamera()->getSpeed());
			break;
		case Down:
			GLApplication::getInstance().getCamera()->moveFront(-1 * GLApplication::getInstance().getCamera()->getSpeed());
			break;
		case Left:
			// GLApplication::getInstance().getCamera()->moveLeft(GLApplication::getInstance().getCamera()->getSpeed());
			break;
		case Right:
			// GLApplication::getInstance().getCamera()->moveLeft(-1 * GLApplication::getInstance().getCamera()->getSpeed());
			break;
		default:
			break;
		}
	}

	void InputManager::mouseMoved(float mouseX, float mouseY)
	{
		// Return if we don't have a valid camera assigned
		if (GLApplication::getInstance().getCamera() == nullptr)
			return;

		// Apply camera sensitivity
		mouseX *= GLApplication::getInstance().getCamera()->getSensitivity();
		mouseY *= GLApplication::getInstance().getCamera()->getSensitivity();

		// Have our manager send the mouse x and y deltas to our camera to process its rotations
		GLApplication::getInstance().getCamera()->rotateLeft(mouseX);
		GLApplication::getInstance().getCamera()->rotateUp(mouseY);
	}

} // namespace engine