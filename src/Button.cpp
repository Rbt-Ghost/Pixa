#include "Button.hpp"
#include <iostream>


Button::Button(const sf::Vector2f position, const sf::Vector2f size, const std::string& buttonText) :
text(font) {

    if(!font.openFromFile("../assets/cheese_milky/Cheese Milky.otf"))
    {
        std::cerr << "Could not open Cheese Milky.otf" << std::endl;
    }

    this->setPosition(position);
    this->setSize(size);
    this->setButtonText(buttonText);

    rect.setPosition(position);
    text.setPosition(position);

    defaultButton();
}

Button::~Button() = default;

void Button::setPosition(const sf::Vector2f position) {
    if (position.x >= 0 && position.y >= 0) {
        this->position = position;
    }
}

void Button::setSize(const sf::Vector2f size) {
    if (size.x > 0 && size.y > 0) {
        this->size = size;
    }
}

void Button::setButtonText(const std::string &buttonText) {
    if (!buttonText.empty()) {
        this->buttonText = buttonText;
    }
}

sf::RectangleShape Button::getRectangle() {
    return rect;
}

sf::Text Button::getText() {
    return text;
}

bool Button::getIsPressedInside() const {
    return isPressedInside;
}

void Button::defaultButton()
{
    rect.setSize(size);
    rect.setFillColor(sf::Color::Green);

    rect.setOrigin(sf::Vector2f(size.x / 2.f, size.y / 2.f));

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(25);
    text.setString(buttonText);

    const sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    ));
}

void Button::hoverButton()
{
    const sf::Vector2f hoverSize = size + sf::Vector2f(4.f, 4.f);
    rect.setSize(hoverSize);
    rect.setFillColor(sf::Color::Cyan);

    rect.setOrigin(sf::Vector2f(hoverSize.x / 2.f, hoverSize.y / 2.f));

    text.setCharacterSize(26);

    const sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    ));
}

void Button::activateButton() { const sf::Vector2f hoverSize = size + sf::Vector2f(2.f, 2.f);
    rect.setSize(hoverSize);
    rect.setFillColor(sf::Color::Red);

    rect.setOrigin(sf::Vector2f(hoverSize.x / 2.f, hoverSize.y / 2.f));

    text.setCharacterSize(26);

    const sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    ));
}

void Button::handleButton(const sf::Vector2f mousePos) {
    bool onMousePress   = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (!isMousePressed)
            onMousePress = true;
        isMousePressed = true;
    }
    else
    {
        isMousePressed = false;
    }

    if (this->getRectangle().getGlobalBounds().contains(mousePos)) {

        if (onMousePress) {
            isPressedInside = true;
        }

        if (isMousePressed and isPressedInside)
            this->activateButton();
        else
            this->hoverButton();
    }
    else
    {
        this->defaultButton();
    }

    if (not isMousePressed)
        isPressedInside = false;
}