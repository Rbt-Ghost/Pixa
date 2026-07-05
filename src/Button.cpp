#include "Button.hpp"
#include <iostream>


Button::Button(const sf::Vector2f position, const sf::Vector2f size, const std::string& buttonText) : text(font) {

    if(!font.openFromFile("../assets/cheese_milky/Cheese Milky.otf"))
    {
        std::cerr << "Could not open Cheese Milky.otf" << std::endl;
    }

    this->setPosition(position);
    this->setSize(size);

    rect.setPosition(position);
    rect.setSize(size);
    rect.setFillColor(sf::Color::Green);

    text.setFont(font);
    text.setCharacterSize(25);
    text.setString(buttonText);

    // --- NEW ALIGNMENT CODE ---

    // 1. Get the bounding box of the text
    sf::FloatRect textRect = text.getLocalBounds();

    // 2. Set the origin to the exact center of the text
    // We add textRect.left and textRect.top to account for the font's baseline offset
    text.setOrigin(textRect.getCenter());

    // 3. Set the position to the center of the button rectangle
    text.setPosition(sf::Vector2f(position.x + size.x / 2.0f,
                     position.y + size.y / 2.0f));
}

Button::~Button() = default;

void Button::setPosition(const sf::Vector2f position) {
    if (position.x > 0 && position.y > 0) {
        this->position = position;
    }
}

void Button::setSize(const sf::Vector2f size) {
    if (size.x > 0 && size.y > 0) {
        this->size = size;
    }
}

sf::RectangleShape Button::getRectangle() {
    return rect;
}

sf::Text Button::getText() {
    return text;
}


