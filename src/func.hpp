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

/**
 * @brief Applies a single-color channel filter to an image, isolating the Red, Green, or Blue components.
 * @param image A constant reference to the source sf::Image to be processed.
 * @param color The target sf::Color (typically sf::Color::Red, sf::Color::Green, or sf::Color::Blue) indicating which channel to preserve.
 * @return A new sf::Image containing only the preserved color channel.
 */
sf::Image ColorFilter(const sf::Image& image, sf::Color color);

/**
 * @brief Applies a custom Blur (or Smoothing) Filter, achieved through a process called Image Convolution. The algorithm use 3x3 convolution kernels to the provided image.
 * @param image A constant reference to the source sf::Image to be processed.
 * @return A new sf::Image containing the result of Smoothing Filter.
 */
sf::Image ImageConvolution(const sf::Image& image);

/**
 * @brief Applies a pixelation (mosaic) effect to the image by grouping pixels into square blocks.
 * @param image A constant reference to the source sf::Image to be processed.
 * @param mosaicSize The width and height in pixels of each mosaic block, which determines the intensity of the pixelation. Defaults to 8.
 * @return A new sf::Image containing the mosaic-filtered result.
 */
sf::Image Mosaic(const sf::Image& image, int mosaicSize = 8);

/**
 * @brief Converts an image to grayscale using standard BT.709 luminance weights.
 * @param image A constant reference to the source sf::Image to be processed.
 * @return A new sf::Image containing the grayscale result.
 */
sf::Image GrayScale(const sf::Image& image);

sf::Image Negative(const sf::Image& image);

#endif //PIXA_FUNC_HPP