#include "../include/CubeMap.hpp"

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

    int n = sizeof(vertices) / sizeof(vertices[0]);

    std::vector<GLfloat> dest(vertices, vertices + n);

    m_vertices = dest;

    buildVBO();
    buildVAO();

    m_faces.push_back(cubeRight);
    m_faces.push_back(cubeLeft);
    m_faces.push_back(cubeTop);
    m_faces.push_back(cubeBottom);
    m_faces.push_back(cubeFront);
    m_faces.push_back(cubeBack);

    m_cubeMapTexture = loadCubeMap(m_faces);
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

GLuint CubeMap::loadCubeMap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int x, y;

    for (unsigned int i = 0; i < faces.size(); i++)
    {
        std::unique_ptr<glimac::Image> sideTexture = glimac::loadImage(faces[i]);

        if (sideTexture != nullptr)
        {
            x = sideTexture->getWidth();
            y = sideTexture->getHeight();
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                     0,
                     GL_RGBA,
                     x,
                     y,
                     0,
                     GL_RGBA,
                     GL_FLOAT,
                     sideTexture->getPixels());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void CubeMap::render(const Camera *camera, Shader &shader, float time)
{
    // Remove the translation section of the MVMatrix
    glm::mat4 MVMatrix = glm::mat4(glm::mat3(camera->getViewMatrix()));
    glm::mat4 ProjectionMatrix = camera->getProjectionMatrix();

    shader.bind();

    shader.setMat4("uMVMatrix", MVMatrix);
    shader.setMat4("uNormalMatrix", glm::transpose(glm::inverse(MVMatrix)));
    shader.setMat4("uMVPMatrix", ProjectionMatrix * MVMatrix);

    m_vao.bind();

    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMapTexture);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    m_vao.unbind();

    shader.unbind();
}