#include <engine/CubeMap.hpp>
#include <engine/Texture.hpp>

namespace engine
{

    CubeMap::CubeMap(const char *cubeFront, const char *cubeLeft, const char *cubeBack, const char *cubeBottom, const char *cubeRight, const char *cubeTop)
    {
        GLfloat vertices[] = {
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f};

        Container<GLfloat> dest;
        for (GLfloat i : vertices)
        {
            dest.add(i);
        }

        m_vertices = dest;

        buildVBO();
        buildVAO();

        m_faces.add(cubeRight);
        m_faces.add(cubeLeft);
        m_faces.add(cubeTop);
        m_faces.add(cubeBottom);
        m_faces.add(cubeFront);
        m_faces.add(cubeBack);

        // m_cubeMapTexture = loadCubeMap(m_faces);
        m_cubeMapTexture = Texture::loadCubeMapTexture(m_faces);
    }

    void CubeMap::buildVBO()
    {
        m_vbo.bind();
        m_vbo.setData(getVertices(), GL_STATIC_DRAW);
        m_vbo.unbind();
    }

    void CubeMap::buildVAO()
    {
        m_vao.bind();

        const GLuint VERTEX_ATTR_POSITION = 0;

        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

        m_vbo.bind();

        m_vbo.setVertexAttrib(VERTEX_ATTR_POSITION, 3, GL_FLOAT, 3 * sizeof(GLfloat), 0);

        m_vbo.unbind();

        m_vao.unbind();
    }

    void CubeMap::render(const Camera *camera, Shader &shader, float time)
    {
        // Remove the translation section of the MVMatrix
        glm::mat4 MVMatrix = glm::mat4(glm::mat3(camera->getViewMatrix()));
        glm::mat4 ProjectionMatrix = camera->getProjectionMatrix();

        shader.bind();

        shader.setMat4("uMVMatrix", MVMatrix);
        shader.setMat4("uMVPMatrix", ProjectionMatrix * MVMatrix);

        m_vao.bind();

        glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMapTexture);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        m_vao.unbind();

        shader.unbind();
    }

} // namespace engine