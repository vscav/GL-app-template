#include "../header/InputManager.hpp"
#include "../header/TimeManager.hpp"

void InputManager::KeyPressed(InputCodes code)
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