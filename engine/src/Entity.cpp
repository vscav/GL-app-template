#include <engine/Entity.hpp>

namespace engine
{
    
    Entity::Entity(
        const Model &model,
        const bool isStatic,
        const Transform &transform)
        : m_model(model), m_isStatic(isStatic),
          m_position(transform.m_position), m_scale(transform.m_scale), m_rotation(transform.m_rotation)
    {
    }

    Entity::Entity(const Entity &other)
        : m_model(other.m_model),
          m_isStatic(other.m_isStatic),
          m_position(other.m_position),
          m_scale(other.m_scale),
          m_rotation(other.m_rotation)
    {
    }

    const glm::mat4 Entity::getMatrix()
    {
        if (m_isStatic && m_hasMatrix)
        {
            return m_transformMatrix;
        }

        glm::mat4 entityMatrix = glm::mat4(1);

        entityMatrix = glm::rotate(entityMatrix, m_rotation[0], -glm::vec3(0.0f, 0.0f, -1.0f));
        entityMatrix = glm::rotate(entityMatrix, m_rotation[1], -glm::vec3(-1.0f, 0.0f, 0.0f));
        entityMatrix = glm::rotate(entityMatrix, m_rotation[2], -glm::vec3(0.0f, 1.0f, 0.0f));

        if (m_isStatic)
        {
            m_transformMatrix = entityMatrix;
            m_hasMatrix = true;
        }
        return entityMatrix;
    }

    void Entity::render()
    {
        // Render the model (be careful with matrix: use matrix of entity, not model)
    }

} // namespace engine
