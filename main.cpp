#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Centered Circle"
    );

    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Green);

    // Set origin to the center of the circle
    circle.setOrigin({50.f, 50.f});

    // Place it at the center of the window
    circle.setPosition({400.f, 300.f});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(circle);
        window.display();
    }
}