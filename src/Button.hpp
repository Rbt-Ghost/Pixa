#pragma once
#include <SFML/Graphics.hpp>

#ifndef PIXA_BUTTON_HPP
#define PIXA_BUTTON_HPP

class Button : public sf::Drawable{
private:
    sf::RectangleShape rect;
    sf::Text text;
    std::string buttonText;
    sf::Vector2f position;
    sf::Vector2f size;

    bool isPressedInside = false;
    bool isMousePressed = false;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    /**
     * @brief Initializes a new Button object with a specific position, size, font, and text label.
     * @param position The (x, y) coordinates for the center of the button.
     * @param size The width and height dimensions of the button.
     * @param font A constant reference to the sf::Font used to render the button's text.
     * @param buttonText The string displayed inside the button.
     */
    Button(sf::Vector2f position, sf::Vector2f size, const sf::Font& font, const std::string& buttonText);

    /**
     * @brief Default destructor for the Button class.
     */
    ~Button() override;

    /**
     * @brief Sets or updates the target position of the button.
     * @param _position The new (x, y) coordinates.
     */
    void setPosition(sf::Vector2f _position);

    /**
     * @brief Sets or updates the target dimensions of the button.
     * @param _size The new width and height.
     */
    void setSize(sf::Vector2f _size);

    /**
     * @brief Sets or updates the text string displayed on the button.
     * @param _buttonText The new string to display.
     */
    void setButtonText(const std::string& _buttonText);

    /**
     * @brief Retrieves the underlying SFML RectangleShape of the button.
     * @return sf::RectangleShape representing the button's visual background.
     */
    sf::RectangleShape getRectangle();

    /**
     * @brief Retrieves the underlying SFML Text object of the button.
     * @return sf::Text representing the button's visual label.
     */
    sf::Text getText();

    /**
     * @brief Checks if the button was successfully clicked (pressed and released) inside its boundaries.
     * @return Boolean indicating whether a valid click occurred.
     */
    bool getIsPressedInside() const;

    /**
     * @brief Resets the button to its default visual state (standard size and color).
     */
    void defaultButton();

    /**
     * @brief Applies the hover visual state (slightly enlarged and different color) to the button.
     */
    void hoverButton();

    /**
     * @brief Handles internal logic for mouse interactions, updating states (default/hover/clicked) based on mouse position.
     * @param mousePos The current (x, y) coordinates of the mouse cursor relative to the window.
     */
    void handleButton(sf::Vector2f mousePos);

};

#endif //PIXA_BUTTON_HPP