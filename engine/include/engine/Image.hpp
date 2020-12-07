#pragma once

#include <engine/dependencies/glm.hpp>
#include <engine/FilePath.hpp>

#include <vector>
#include <memory>
#include <unordered_map>

namespace engine
{

    class Image
    {
    private:
        unsigned int m_nWidth = 0u;  /*!< The width of the image. */
        unsigned int m_nHeight = 0u;  /*!< The height of the image. */
        std::unique_ptr<glm::vec4[]> m_Pixels; /*!< A unique pointer of the array containing the pixels of the image. */

    public:
        /// \brief Constructor.
        Image(unsigned int width, unsigned int height);

        /// \brief Gets the width of the image.
        /// \return The width of the image.
        inline unsigned int getWidth() const { return m_nWidth; };

        /// \brief Gets the height of the image.
        /// \return The height of the image.
        inline unsigned int getHeight() const { return m_nHeight; };

        /// \brief Gets the pixels of the image.
        /// \return A pointer to the pixels data of the image.
        inline const glm::vec4 *getPixels() const { return m_Pixels.get(); };

        /// \brief Gets the pixels of the image.
        /// \return A pointer to the pixels data of the image.
        inline glm::vec4 *getPixels() { return m_Pixels.get(); };
    };

    /// \brief Loads an image.
    /// \param filepath : The filepath (FilePath object) to the image.
    /// \return A unique pointer to the loaded image.
    std::unique_ptr<Image> loadImage(const FilePath &filepath);

    class ImageManager
    {
    private:
        static std::unordered_map<FilePath, std::unique_ptr<Image>> m_ImageMap; /*!< A map to store already loaded images. */

    public:
        /// \brief Loads the image from a filepath object.
        static const Image *loadImage(const FilePath &filepath);
    };

} // namespace engine
