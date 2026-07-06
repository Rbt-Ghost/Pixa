#pragma once
#include <SFML/Graphics.hpp>

#ifndef PIXA_BUTTON_HPP
#define PIXA_BUTTON_HPP


class Button {
private:
    sf::RectangleShape rect;
    sf::Font font;
    sf::Text text;
    std::string buttonText;
    sf::Vector2f position;
    sf::Vector2f size;

public:
    Button(sf::Vector2f position, sf::Vector2f size, const std::string& buttonText);
    ~Button();

    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    void setButtonText(const std::string& buttonText);

    sf::RectangleShape getRectangle();
    sf::Text getText();

    void defaultButton();
    void hoverButton();
    void activateButton();

};


#endif //PIXA_BUTTON_HPP
