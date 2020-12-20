#pragma once
#ifndef _Entity_HPP_
#define _Entity_HPP_

#include <engine/Model.hpp>
#include <engine/dependencies/glm.hpp>

#include <memory>

namespace engine
{

    /// \brief Structure fo representing the transformations of an entity
    struct Transform
    {
    public:
        const glm::vec3 &m_position = glm::vec3(0);
        const glm::vec3 &m_scale = glm::vec3(1);
        const glm::vec3 &m_rotation = glm::vec3(0);
        Transform(
            const glm::vec3 &position = glm::vec3(0),
            const glm::vec3 &scale = glm::vec3(1),
            const glm::vec3 &rotation = glm::vec3(0))
            : m_position(position), m_scale(scale), m_rotation(rotation){};
    };

    /// \brief Represents a renderable entity
    class Entity
    {
    protected:
        /// \brief 3D model of the entity
        std::shared_ptr<Model> m_model; // better to use refs because less mistakes ?

        /// \brief is the entity static (eg. the entity is unable to move) ?
        bool m_isStatic = false;

        /// \brief position of the entity
        glm::vec3 m_position;
        /// \brief scale of the entity
        glm::vec3 m_scale;
        /// \brief rotation of the entity
        glm::vec3 m_rotation;

        /// \brief stored transformation matrix of the entity in case the entity is static
        bool m_hasMatrix = false;
        glm::mat4 m_transformMatrix;

    public:
        /// \brief Parameterized constructor.
        /// \param model 	: The GLTF model of the entity.
        /// \param isStatic : Whether the entity is able to move or not.
        /// \param position : The position of the entity.
        /// \param scale 	: The scale of the entity.
        /// \param rotation : The rotation of the entity.
        Entity(
            Model *model,
            const bool isStatic = false,
            const Transform &transform = Transform());

        /// \brief Copy constructor.
        /// \param g : The entity to copy from.
        Entity(const Entity &other);

        /// \brief Destructor.
        ~Entity(){};

        /// \brief Returns the transform matrix of the entity.
        virtual const glm::mat4 getMatrix();

        void moveFront(float dt);
        void moveLeft(float dt);

        /// \brief Update the entity.
        void update(float time);

        /// \brief Render the entity.
        void render(const Camera *camera, Shader &shader, float time);

        /// \brief Get the position of the entity.
        inline const glm::vec3 &getPosition() const { return m_position; };
        /// \brief Set the position of the entity.
        inline void setPosition(glm::vec3 position) { m_position = position; };

        /// \brief Get the rotation of the entity as a const reference.
        inline const glm::vec3 &getRotation() const { return m_rotation; };
        /// \brief Get the rotation of the entity as a reference.
        inline void setRotation(glm::vec3 rotation) { m_rotation = rotation; };

        /// \brief Get the scale of the entity as a const reference.
        inline const glm::vec3 &getScale() const { return m_scale; };
        /// \brief Get the scale of the entity as a reference.
        inline void setScale(glm::vec3 scale) { m_scale = scale; };

        /// \brief Get the model of the entity as a const reference.
        inline const Model *getModel() const { return m_model.get(); };

        /// \brief Returns a boolean to tell whether the entity is able to move or not.
        inline const bool &isStatic() const { return m_isStatic; };
    };

} // namespace engine

#endif