#include "../../include/opengl/Texture.hpp"

namespace opengl
{

    GLuint Texture::loadTexture(std::string path)
    {
        GLuint textureID;

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        int x = 0, y = 0;

        std::unique_ptr<utils::Image> texture = utils::loadImage(path);

        if (texture != nullptr)
        {
            x = texture->getWidth();
            y = texture->getHeight();
        }

        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGB,
                     x,
                     y,
                     0,
                     GL_RGB,
                     GL_UNSIGNED_BYTE,
                     texture->getPixels());
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        return textureID;
    }

    GLuint Texture::loadCubeMapTexture(iterator::Container<std::string> faces)
    {
        unsigned int textureID;

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        int x = 0, y = 0, i = 0;

        iterator::Iterator<std::string, iterator::Container<std::string>> *it = faces.CreateIterator();
        for (it->first(); !it->isDone(); it->next())
        {
            std::unique_ptr<utils::Image> sideTexture = utils::loadImage(faces.at(i));

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

            i++;
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

        return textureID;
    }

} // namespace opengl