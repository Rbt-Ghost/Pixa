#include <SFML/Graphics.hpp>
#include "src/Button.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1660, 840}),
        "Pixa"
    );

    Button loadButton(sf::Vector2f(100,50), sf::Vector2f(140,40), "Load Button");
    Button saveButton(sf::Vector2f(100,100), sf::Vector2f(140,40), "Save Button");
    Button binarizationButton(sf::Vector2f(100,150), sf::Vector2f(140,40), "Binarization");
    Button tstButton(sf::Vector2f(100,200), sf::Vector2f(140,40), "Tst");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(loadButton.getRectangle());
        window.draw(loadButton.getText());
        window.draw(saveButton.getRectangle());
        window.draw(saveButton.getText());
        window.draw(binarizationButton.getRectangle());
        window.draw(binarizationButton.getText());
        window.draw(tstButton.getRectangle());
        window.draw(tstButton.getText());
        window.display();
    }
}