#ifndef PIXA_FUNC_HPP
#define PIXA_FUNC_HPP

#include <string>
#include "SFML/Graphics.hpp"

std::string openImageDialog();
void scaleSprite(sf::Sprite& sprite, const sf::Texture& texture);
sf::Image EdgeDetection(const sf::Image& image);

#endif //PIXA_FUNC_HPP
