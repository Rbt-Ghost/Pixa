#include <SFML/Graphics.hpp>
#include "src/Button.hpp"
#include "src/Constants.hpp"
#include "src/func.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({Constants::APP_WIDTH, Constants::APP_HEIGHT}),
        "Pixa"
    );

    sf::Texture inputTexture;
    sf::Sprite inputSprite(inputTexture);

    Button loadButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*1), Constants::BASE_BUTTON_SIZE, "Load Button");
    Button saveButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*2), Constants::BASE_BUTTON_SIZE, "Save Button");
    Button binarizationButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*3), Constants::BASE_BUTTON_SIZE, "Binarization");
    Button tstButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*4), Constants::BASE_BUTTON_SIZE, "Tst");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (event->is<sf::Event::Resized>()) {
                sf::View view(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
                window.setView(view);
            }

        }

        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

        if (window.getSize().x > 1660 || window.getSize().y > 840)
        {
            mousePos.x = mousePos.x / static_cast<float>(window.getSize().x) * 1660.f;
            mousePos.y = mousePos.y / static_cast<float>(window.getSize().y) * 840.f;
        }

        loadButton.handleButton(mousePos);
        saveButton.handleButton(mousePos);
        binarizationButton.handleButton(mousePos);
        tstButton.handleButton(mousePos);

        if (loadButton.getIsPressedInside()) {
            std::string path = openImageDialog();
            sf::sleep(sf::milliseconds(300 ));

            if (!path.empty())
            {
                if (!inputTexture.loadFromFile(path)) {
                    return -1;
                }
                inputSprite.setTexture(inputTexture, true);

                sf::Vector2u textureSize = inputTexture.getSize();

                float scaleX = Constants::MAX_IMAGE_WIDTH / static_cast<float>(textureSize.x);
                float scaleY = Constants::MAX_IMAGE_HEIGHT / static_cast<float>(textureSize.y);

                float finalScale = std::min(scaleX, scaleY);

                if (finalScale > 1.f) {
                    finalScale = 1.f;
                }

                inputSprite.setScale(sf::Vector2f(finalScale, finalScale));

                inputSprite.setPosition(sf::Vector2f(static_cast<int>(Constants::APP_WIDTH / 6), static_cast<int>(Constants::BASE_BUTTON_HEIGHT - (Constants::BASE_BUTTON_SIZE.y/2))));
            }
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
        window.draw(inputSprite);
        window.display();
    }
}
