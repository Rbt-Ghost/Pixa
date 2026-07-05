#pragma once
#include <SFML/Graphics.hpp>

#ifndef PICTUREIT_BUTTON_HPP
#define PICTUREIT_BUTTON_HPP


class Button {
private:
    sf::RectangleShape rect;
    sf::Font font;
    sf::Text text;
    sf::Vector2f position;
    sf::Vector2f size;

public:
    Button(sf::Vector2f position, sf::Vector2f size, const std::string& buttonText);
    ~Button();

    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);

    sf::RectangleShape getRectangle();
    sf::Text getText();
};


#endif //PICTUREIT_BUTTON_HPP
