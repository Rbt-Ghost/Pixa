#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/Button.hpp"
#include "src/Chart.hpp"
#include "src/Constants.hpp"
#include "src/func.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({Constants::APP_WIDTH, Constants::APP_HEIGHT}),
        "Pixa"
    );
    window.setFramerateLimit(60);

    sf::Font font;
    if(!font.openFromFile("../assets/cheese_milky/Cheese Milky.otf"))
    {
        std::cerr << "Could not open Cheese Milky.otf" << std::endl;
    }

    sf::Texture inputTexture;
    sf::Sprite inputSprite(inputTexture);
    sf::Image inputImage;

    sf::Texture outputTexture;
    sf::Sprite outputSprite(inputTexture);
    sf::Image outputImage;

    Button loadButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*1), Constants::BASE_BUTTON_SIZE, font, "Load Button");
    Button saveButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*2), Constants::BASE_BUTTON_SIZE, font, "Save Button");
    Button moveButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*3), Constants::BASE_BUTTON_SIZE, font, "Img1 <- Img2");
    Button redFilterButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*4), Constants::BASE_BUTTON_SIZE, font, "Red Filter");
    Button greenFilterButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*5), Constants::BASE_BUTTON_SIZE, font, "Green Filter");
    Button blueFilterButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*6), Constants::BASE_BUTTON_SIZE, font, "Blue Filter");
    Button mosaicButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*7), Constants::BASE_BUTTON_SIZE, font, "Mosaic");
    Button smoothingButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*8), Constants::BASE_BUTTON_SIZE, font, "Smoothing Filter");
    Button edgeDetectionButton(sf::Vector2f(Constants::BASE_BUTTON_WIDTH,Constants::BASE_BUTTON_HEIGHT*9), Constants::BASE_BUTTON_SIZE, font, "Edge Detection");

    Chart inputHistogram(sf::Vector2f(static_cast<int>(Constants::APP_WIDTH / 8.f), Constants::BASE_BUTTON_HEIGHT + Constants::MAX_IMAGE_HEIGHT), sf::Vector2f(Constants::MAX_IMAGE_WIDTH, Constants::MAX_IMAGE_HEIGHT));
    Chart outputHistogram(sf::Vector2f(static_cast<int>(Constants::APP_WIDTH / 1.8f), Constants::BASE_BUTTON_HEIGHT + Constants::MAX_IMAGE_HEIGHT), sf::Vector2f(Constants::MAX_IMAGE_WIDTH, Constants::MAX_IMAGE_HEIGHT));

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
        moveButton.handleButton(mousePos);
        smoothingButton.handleButton(mousePos);
        edgeDetectionButton.handleButton(mousePos);
        redFilterButton.handleButton(mousePos);
        greenFilterButton.handleButton(mousePos);
        blueFilterButton.handleButton(mousePos);
        mosaicButton.handleButton(mousePos);

        if (loadButton.getIsPressedInside()) {
            std::string path = openImageDialog();
            sf::sleep(sf::milliseconds(300 ));

            if (!path.empty())
            {
                if (!inputTexture.loadFromFile(path)) {
                    return -1;
                }

                inputImage = inputTexture.copyToImage();
                inputHistogram.Histogram(inputImage);

                scaleSprite(inputSprite, inputTexture);
                inputSprite.setPosition(sf::Vector2f(static_cast<int>(Constants::APP_WIDTH / 8.f), static_cast<int>(Constants::BASE_BUTTON_HEIGHT - (Constants::BASE_BUTTON_SIZE.y/2))));
            }
        }

        if (smoothingButton.getIsPressedInside() && inputTexture.getSize() != sf::Vector2u(0,0)) {
            outputImage = ImageConvolution(inputImage);
            outputHistogram.Histogram(outputImage);

            if (!outputTexture.loadFromImage(outputImage)) {
                return -1;
            }

            scaleSprite(outputSprite, outputTexture);
            outputSprite.setPosition(sf::Vector2f(static_cast<int>(Constants::APP_WIDTH / 1.8f), static_cast<int>(Constants::BASE_BUTTON_HEIGHT - (Constants::BASE_BUTTON_SIZE.y/2))));
        }

        if (edgeDetectionButton.getIsPressedInside() && inputTexture.getSize() != sf::Vector2u(0,0)) {
            outputImage = EdgeDetection(inputImage);
            outputHistogram.Histogram(outputImage);

            if (!outputTexture.loadFromImage(outputImage)) {
                return -1;
            }

            scaleSprite(outputSprite, outputTexture);
            outputSprite.setPosition(sf::Vector2f(static_cast<int>(Constants::APP_WIDTH / 1.8f), static_cast<int>(Constants::BASE_BUTTON_HEIGHT - (Constants::BASE_BUTTON_SIZE.y/2))));
        }

        if (moveButton.getIsPressedInside() && outputTexture.getSize() != sf::Vector2u(0,0)) {
            inputTexture = outputTexture;
            //copy the new texture to inputImage
            inputImage = inputTexture.copyToImage();
            //re draw the histogram
            inputHistogram.Histogram(inputImage);
        }

        if (mosaicButton.getIsPressedInside() && inputTexture.getSize() != sf::Vector2u(0,0)) {
            outputImage = Mosaic(inputImage);
            outputHistogram.Histogram(outputImage);

            if (!outputTexture.loadFromImage(outputImage)) {
                return -1;
            }

            scaleSprite(outputSprite, outputTexture);
            outputSprite.setPosition(sf::Vector2f(static_cast<int>(Constants::APP_WIDTH / 1.8f), static_cast<int>(Constants::BASE_BUTTON_HEIGHT - (Constants::BASE_BUTTON_SIZE.y/2))));
        }

        if (redFilterButton.getIsPressedInside() && inputTexture.getSize() != sf::Vector2u(0,0)) {
            outputImage = ColorFilter(inputImage, sf::Color::Red);
            outputHistogram.Histogram(outputImage);

            if (!outputTexture.loadFromImage(outputImage)) {
                return -1;
            }

            scaleSprite(outputSprite, outputTexture);
            outputSprite.setPosition(sf::Vector2f(static_cast<int>(Constants::APP_WIDTH / 1.8f), static_cast<int>(Constants::BASE_BUTTON_HEIGHT - (Constants::BASE_BUTTON_SIZE.y/2))));
        }

        if (greenFilterButton.getIsPressedInside() && inputTexture.getSize() != sf::Vector2u(0,0)) {
            outputImage = ColorFilter(inputImage, sf::Color::Green);
            outputHistogram.Histogram(outputImage);

            if (!outputTexture.loadFromImage(outputImage)) {
                return -1;
            }

            scaleSprite(outputSprite, outputTexture);
            outputSprite.setPosition(sf::Vector2f(static_cast<int>(Constants::APP_WIDTH / 1.8f), static_cast<int>(Constants::BASE_BUTTON_HEIGHT - (Constants::BASE_BUTTON_SIZE.y/2))));
        }

        if (blueFilterButton.getIsPressedInside() && inputTexture.getSize() != sf::Vector2u(0,0)) {
            outputImage = ColorFilter(inputImage, sf::Color::Blue);
            outputHistogram.Histogram(outputImage);

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
        window.draw(moveButton.getRectangle());
        window.draw(moveButton.getText());
        window.draw(redFilterButton.getRectangle());
        window.draw(redFilterButton.getText());
        window.draw(greenFilterButton.getRectangle());
        window.draw(greenFilterButton.getText());
        window.draw(blueFilterButton.getRectangle());
        window.draw(blueFilterButton.getText());
        window.draw(mosaicButton.getRectangle());
        window.draw(mosaicButton.getText());
        window.draw(smoothingButton.getRectangle());
        window.draw(smoothingButton.getText());
        window.draw(edgeDetectionButton.getRectangle());
        window.draw(edgeDetectionButton.getText());
        window.draw(inputSprite);
        window.draw(outputSprite);
        window.draw(inputHistogram);
        window.draw(outputHistogram);
        window.display();
    }
}
