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
    sf::Image inputImage;

    sf::Texture outputTexture;
    sf::Sprite outputSprite(inputTexture);
    sf::Image outputImage;

    Button loadButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*1), Constants::BASE_BUTTON_SIZE, "Load Button");
    Button saveButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*2), Constants::BASE_BUTTON_SIZE, "Save Button");
    Button binarizationButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*3), Constants::BASE_BUTTON_SIZE, "Binarization");
    Button edgeDetectionButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*4), Constants::BASE_BUTTON_SIZE, "Edge Detection");

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

        auto mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

        if (window.getSize().x > 1660 || window.getSize().y > 840)
        {
            mousePos.x = mousePos.x / static_cast<float>(window.getSize().x) * 1660.f;
            mousePos.y = mousePos.y / static_cast<float>(window.getSize().y) * 840.f;
        }

        loadButton.handleButton(mousePos);
        saveButton.handleButton(mousePos);
        binarizationButton.handleButton(mousePos);
        edgeDetectionButton.handleButton(mousePos);

        if (loadButton.getIsPressedInside()) {
            std::string path = openImageDialog();
            sf::sleep(sf::milliseconds(300 ));

            if (!path.empty())
            {
                if (!inputTexture.loadFromFile(path)) {
                    return -1;
                }

                scaleSprite(inputSprite, inputTexture);
                inputSprite.setPosition(sf::Vector2f(static_cast<int>(Constants::APP_WIDTH / 8), static_cast<int>(Constants::BASE_BUTTON_HEIGHT - (Constants::BASE_BUTTON_SIZE.y/2))));
            }
        }

        if (edgeDetectionButton.getIsPressedInside()) {
            inputImage = inputTexture.copyToImage();
            outputImage = EdgeDetection(inputImage);

            if (!outputTexture.loadFromImage(outputImage)) {
                return -1;
            }

            scaleSprite(outputSprite, outputTexture);
            outputSprite.setPosition(sf::Vector2f(static_cast<int>(Constants::APP_WIDTH / 1.8f), static_cast<int>(Constants::BASE_BUTTON_HEIGHT - (Constants::BASE_BUTTON_SIZE.y/2))));
        }

        window.clear();
        window.draw(loadButton.getRectangle());
        window.draw(loadButton.getText());
        window.draw(saveButton.getRectangle());
        window.draw(saveButton.getText());
        window.draw(binarizationButton.getRectangle());
        window.draw(binarizationButton.getText());
        window.draw(edgeDetectionButton.getRectangle());
        window.draw(edgeDetectionButton.getText());
        window.draw(inputSprite);
        window.draw(outputSprite);
        window.display();
    }
}
