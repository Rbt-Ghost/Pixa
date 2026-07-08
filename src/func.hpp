#ifndef PIXA_FUNC_HPP
#define PIXA_FUNC_HPP

#include <string>
#include "SFML/Graphics.hpp"

/**
 * @brief Opens a native Windows file dialog to let the user select an image file.
 * @return std::string containing the absolute file path of the selected image, or an empty string if the user cancels.
 */
std::string openImageDialog();

/**
 * @brief Uniformly scales a sprite to fit within the maximum allowed image dimensions while maintaining its original aspect ratio.
 * @param sprite A reference to the sf::Sprite that will be scaled and updated.
 * @param texture A constant reference to the sf::Texture to apply to the sprite.
 */
void scaleSprite(sf::Sprite& sprite, const sf::Texture& texture);

/**
 * @brief Applies a custom edge detection algorithm using 3x3 convolution kernels to the provided image.
 * @param image A constant reference to the source sf::Image to be processed.
 * @return A new sf::Image containing the edge-detected result.
 */
sf::Image EdgeDetection(const sf::Image& image);

#endif //PIXA_FUNC_HPP