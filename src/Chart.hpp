#pragma once
#include <SFML/Graphics.hpp>

#ifndef PIXA_CHART_HPP
#define PIXA_CHART_HPP


class Chart : public sf::Drawable {
private:
    sf::Vector2f position;
    sf::Vector2f size;

    sf::VertexArray verticesR;
    sf::VertexArray verticesG;
    sf::VertexArray verticesB;

    sf::RectangleShape background;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Chart(sf::Vector2f position, sf::Vector2f size);
    ~Chart() override;

    void setPosition(sf::Vector2f _position);
    void setSize(sf::Vector2f _size);

    void Histogram(const sf::Image& image);
};


#endif //PIXA_CHART_HPP
