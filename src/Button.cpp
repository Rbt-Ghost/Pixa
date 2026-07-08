#include "Button.hpp"


Button::Button(const sf::Vector2f position, const sf::Vector2f size, const sf::Font& font, const std::string& buttonText) :
text(font) {
    this->setPosition(position);
    this->setSize(size);
    this->setButtonText(buttonText);

    rect.setPosition(position);
    text.setPosition(position);
    text.setFillColor(sf::Color::Black);
    text.setString(buttonText);

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
    rect.setOrigin(rect.getGeometricCenter());

    text.setCharacterSize(25);

    // Set the text origin based on the button rectangular shape
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
    rect.setOrigin(rect.getGeometricCenter());

    text.setCharacterSize(26);

    // Set the text origin based on the button rectangular shape
    const sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    ));
}

void Button::handleButton(const sf::Vector2f mousePos)
{
    const bool onMousePress = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !isMousePressed;
    isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    if (rect.getGlobalBounds().contains(mousePos))
    {
        if (onMousePress)
            isPressedInside = true;

        if (!isMousePressed || !isPressedInside)
            hoverButton();
    }
    else
    {
        defaultButton();
    }

    if (!isMousePressed)
        isPressedInside = false;
}