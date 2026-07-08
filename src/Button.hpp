#pragma once
#include <SFML/Graphics.hpp>

#ifndef PIXA_BUTTON_HPP
#define PIXA_BUTTON_HPP

class Button {
private:
    sf::RectangleShape rect;
    sf::Text text;
    std::string buttonText;
    sf::Vector2f position;
    sf::Vector2f size;

    bool isPressedInside = false;
    bool isMousePressed = false;

public:
    /**
        Description: Initializes a new Button object with a specific position, size, font, and text label.
        Params:
            position - The (x, y) coordinates for the center of the button.
            size - The width and height dimensions of the button.
            font - A constant reference to the sf::Font used to render the button's text.
            buttonText - The string displayed inside the button.
        Returns: None
    */
    Button(sf::Vector2f position, sf::Vector2f size, const sf::Font& font, const std::string& buttonText);

    /**
        Description: Default destructor for the Button class.
        Params: None
        Returns: None
    */
    ~Button();

    /**
        Description: Sets or updates the target position of the button.
        Params:
            position - The new (x, y) coordinates.
        Returns: None
    */
    void setPosition(sf::Vector2f _position);

    /**
        Description: Sets or updates the target dimensions of the button.
        Params:
            size - The new width and height.
        Returns: None
    */
    void setSize(sf::Vector2f _size);

    /**
        Description: Sets or updates the text string displayed on the button.
        Params:
            buttonText - The new string to display.
        Returns: None
    */
    void setButtonText(const std::string& _buttonText);

    /**
        Description: Retrieves the underlying SFML RectangleShape of the button.
        Params: None
        Returns: sf::RectangleShape representing the button's visual background.
    */
    sf::RectangleShape getRectangle();

    /**
        Description: Retrieves the underlying SFML Text object of the button.
        Params: None
        Returns: sf::Text representing the button's visual label.
    */
    sf::Text getText();

    /**
        Description: Checks if the button was successfully clicked (pressed and released) inside its boundaries.
        Params: None
        Returns: Boolean indicating whether a valid click occurred.
    */
    bool getIsPressedInside() const;

    /**
        Description: Resets the button to its default visual state (standard size and color).
        Params: None
        Returns: None
    */
    void defaultButton();

    /**
        Description: Applies the hover visual state (slightly enlarged and different color) to the button.
        Params: None
        Returns: None
    */
    void hoverButton();

    /**
        Description: Handles internal logic for mouse interactions, updating states (default/hover/clicked) based on mouse position.
        Params:
            mousePos - The current (x, y) coordinates of the mouse cursor relative to the window.
        Returns: None
    */
    void handleButton(sf::Vector2f mousePos);

};

#endif //PIXA_BUTTON_HPP