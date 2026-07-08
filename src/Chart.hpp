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
    /**
     * @brief Draws the chart and its data to the render target. Overrides the sf::Drawable standard method.
     * @param target The render target (usually your sf::RenderWindow) where the chart will be drawn.
     * @param states The rendering states to use (transforms, blend modes, etc.).
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    /**
     * @brief Initializes a new Chart object with a specific position and size.
     * @param position The (x, y) coordinates for the top-left corner of the chart's background.
     * @param size The width and height dimensions of the chart.
     */
    Chart(sf::Vector2f position, sf::Vector2f size);

    /**
     * @brief Default destructor for the Chart class.
     */
    ~Chart() override;

    /**
     * @brief Sets or updates the target position of the chart on the screen.
     * @param _position The new (x, y) coordinates.
     */
    void setPosition(sf::Vector2f _position);

    /**
     * @brief Sets or updates the target dimensions of the chart.
     * @param _size The new width and height.
     */
    void setSize(sf::Vector2f _size);

    /**
     * @brief Calculates the RGB color frequencies of the provided image and updates the chart vertices to display them.
     * @param image A constant reference to the sf::Image to be analyzed.
     */
    void Histogram(const sf::Image& image);
};

#endif //PIXA_CHART_HPP