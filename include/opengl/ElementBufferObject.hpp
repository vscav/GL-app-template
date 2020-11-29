#pragma once
#ifndef _ElementBufferObject_HPP_
#define _ElementBufferObject_HPP_

#include "../iterator/Container.hpp"

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace opengl
{

    /// \class ElementBufferObject
    /// \brief Class used to represent an OpenGL EBO.
    class ElementBufferObject
    {
    private:
        GLuint m_index;

    public:
        ///\brief Constructor.
        ElementBufferObject();

        ///\brief Destructor.
        ~ElementBufferObject();

        ///\brief Bind this EBO.
        void bind();

        ///\brief Unbind the EBO.
        void unbind();

        ///\brief Creates and initializes a buffer object's data store.
        ///\param indices : Specifies a pointer to indices data that will be copied into the data store for initialization.
        ///\param drawType : Specifies the expected usage pattern of the data store.
        void setData(const iterator::Container<glm::uvec3> &indices, const GLenum &drawType);

        ///\brief Return the ID of the EBO.
        inline GLuint getId() const { return m_index; };
    };

} // namespace opengl

#endif /* _ElementBufferObject_HPP_ */