#include <engine/Sphere.hpp>
#include <engine/Camera.hpp>

namespace engine
{

    Sphere::Sphere(GLfloat radius, GLsizei discLat, GLsizei discLong) : m_nVertexCount(0)
    {
        build(radius, discLat, discLong);

        buildVBO();
        buildVAO();
    }

    void Sphere::buildVBO()
    {
        m_vbo.bind();
        m_vbo.setData(getVertices(), GL_STATIC_DRAW);
        m_vbo.unbind();
    }

    void Sphere::buildVAO()
    {
        m_vao.bind();

        const GLuint VERTEX_ATTR_POSITION = 0;
        const GLuint VERTEX_ATTR_NORMAL = 1;
        const GLuint VERTEX_ATTR_TEXCOORD = 2;

        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORD);

        m_vbo.bind();

        m_vbo.setVertexAttrib(VERTEX_ATTR_POSITION, 3, GL_FLOAT, sizeof(ShapeVertex), offsetof(ShapeVertex, position));
        m_vbo.setVertexAttrib(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, sizeof(ShapeVertex), offsetof(ShapeVertex, normal));
        m_vbo.setVertexAttrib(VERTEX_ATTR_TEXCOORD, 3, GL_FLOAT, sizeof(ShapeVertex), offsetof(ShapeVertex, texCoords));

        m_vbo.unbind();

        m_vao.unbind();
    }

    void Sphere::render(const Camera *camera, Shader &shader, float time)
    {
        glm::mat4 MVMatrix = camera->getViewMatrix();
        glm::mat4 ProjectionMatrix = camera->getProjectionMatrix();

        shader.bind();

        shader.setMat4("uMVMatrix", MVMatrix);
        shader.setMat4("uNormalMatrix", glm::transpose(glm::inverse(MVMatrix)));
        shader.setMat4("uMVPMatrix", ProjectionMatrix * MVMatrix);

        // shader.setVec3f("uCameraPosition", camera->getPosition());

        // Directional light
        glm::mat4 lightMVMatrix = glm::rotate(MVMatrix, time, glm::vec3(0, 1, 0));
        glm::vec3 lightDir_vs(lightMVMatrix * glm::vec4(1, 1, 1, 0));

        shader.setVec3f("uLightIntensity", 1.0, 1.0, 1.0);
        shader.setVec3f("uLightDir_vs", lightDir_vs);
        shader.setVec3f("uKd", 0, 0.5, 0.8);
        shader.setVec3f("uKs", 0, 0, 0.25);
        shader.setFloat("uShininess", 2.75);

        m_vao.bind();

        glDrawArrays(GL_TRIANGLES, 0, this->getVertexCount());

        m_vao.unbind();

        shader.unbind();
    }

    void Sphere::build(GLfloat r, GLsizei discLat, GLsizei discLong)
    {
        GLfloat rcpLat = 1.f / discLat, rcpLong = 1.f / discLong;
        GLfloat dPhi = 2 * glm::pi<float>() * rcpLat, dTheta = glm::pi<float>() * rcpLong;

        Container<ShapeVertex> data;

        for (GLsizei j = 0; j <= discLong; ++j)
        {
            GLfloat cosTheta = cos(-glm::pi<float>() / 2 + j * dTheta);
            GLfloat sinTheta = sin(-glm::pi<float>() / 2 + j * dTheta);

            for (GLsizei i = 0; i <= discLat; ++i)
            {
                ShapeVertex vertex;

                vertex.texCoords.x = i * rcpLat;
                vertex.texCoords.y = 1.f - j * rcpLong;

                vertex.normal.x = sin(i * dPhi) * cosTheta;
                vertex.normal.y = sinTheta;
                vertex.normal.z = cos(i * dPhi) * cosTheta;

                vertex.position = r * vertex.normal;

                data.add(vertex);
            }
        }

        m_nVertexCount = discLat * discLong * 6;

        for (GLsizei j = 0; j < discLong; ++j)
        {
            GLsizei offset = j * (discLat + 1);
            for (GLsizei i = 0; i < discLat; ++i)
            {
                m_vertices.add(data.at(offset + i));
                m_vertices.add(data.at(offset + (i + 1)));
                m_vertices.add(data.at(offset + discLat + 1 + (i + 1)));
                m_vertices.add(data.at(offset + i));
                m_vertices.add(data.at(offset + discLat + 1 + (i + 1)));
                m_vertices.add(data.at(offset + i + discLat + 1));
            }
        }
    }

} // namespace world
