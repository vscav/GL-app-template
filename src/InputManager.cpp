#include "../include/InputManager.hpp"
#include "../include/TimeManager.hpp"

void InputManager::keyPressed(InputCodes code)
{
    if (m_camera == nullptr)
        return;

    switch (code)
    {
    case Up:
    case W:
    case w:
        m_camera->moveFront(m_camera->getSpeed() * TimeManager::Instance().deltaTime);
        break;
    case Down:
    case S:
    case s:
        m_camera->moveFront(-1 * m_camera->getSpeed() * TimeManager::Instance().deltaTime);
        break;
    case Left:
    case A:
    case a:
        m_camera->moveLeft(m_camera->getSpeed() * TimeManager::Instance().deltaTime);
        break;
    case Right:
    case D:
    case d:
        m_camera->moveLeft(-1 * m_camera->getSpeed() * TimeManager::Instance().deltaTime);
        break;
    }
}

// This sends in an updated mouse x and y position that should be a delta from (0, 0)
void InputManager::mouseMoved(float mouseX, float mouseY)
{
	// Return if we don't have a valid camera assigned
	if ( m_camera == nullptr )
		return;

	// Have our manager send the mouse x and y deltas to our camera to process the rotations
	m_camera->rotateLeft(mouseX);
    m_camera->rotateUp(mouseY);
}