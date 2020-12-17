#include <engine/Texture.hpp>
#include <engine/utils/common.hpp>
// #define STB_IMAGE_IMPLEMENTATION
#include <engine/dependencies/stb_image.h>

#include <iostream>

namespace engine
{

    Texture::Texture(unsigned int width, unsigned int height)
        : m_nWidth(width), m_nHeight(height), m_Pixels(new glm::vec4[width * height])
    {
    }

    std::unique_ptr<Texture> loadImage(const FilePath &filepath)
    {
        int x, y, n;
        unsigned char *data = stbi_load(filepath.c_str(), &x, &y, &n, 4);
        if (!data)
        {
            if(debug) std::cerr << "[Texture] ERROR: Loading image " << filepath << ": " << stbi_failure_reason() << std::endl;
            return std::unique_ptr<Texture>();
        }
        std::unique_ptr<Texture> pImage(new Texture(x, y));
        unsigned int size = x * y;
        auto scale = 1.f / 255;
        auto ptr = pImage->getPixels();
        for (auto i = 0u; i < size; ++i)
        {
            auto offset = 4 * i;
            ptr->r = (float)data[offset] * scale;
            ptr->g = (float)data[offset + 1] * scale;
            ptr->b = (float)data[offset + 2] * scale;
            ptr->a = (float)data[offset + 3] * scale;
            ++ptr;
        }
        stbi_image_free(data);
        return pImage;
    }

    std::unordered_map<FilePath, std::unique_ptr<Texture>> TextureManager::m_textureMap;

    const Texture *TextureManager::loadImage(const FilePath &filepath)
    {
        auto it = m_textureMap.find(filepath);
        if (it != std::end(m_textureMap))
        {
            return (*it).second.get();
        }
        auto pImage = engine::loadImage(filepath);
        if (!pImage)
        {
            return nullptr;
        }
        auto &img = m_textureMap[filepath] = std::move(pImage);
        return img.get();
    }

} // namespace engine