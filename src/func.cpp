#include "func.hpp"

#include <windows.h>
#include <commdlg.h>
#include <iostream>

#include "Constants.hpp"

std::string openImageDialog() {
    char fileName[MAX_PATH] = "";

    OPENFILENAMEA ofn{};
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;

    ofn.lpstrFilter =
        "Image Files\0*.png;*.jpg;*.jpeg;*.bmp;*.tga\0"
        "All Files\0*.*\0";

    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn))
        return fileName;

    return "";
}

void scaleSprite(sf::Sprite& sprite, const sf::Texture& texture) {
    sprite.setTexture(texture, true);

    const sf::Vector2u textureSize = texture.getSize();

    const float scaleX = Constants::MAX_IMAGE_WIDTH / static_cast<float>(textureSize.x);
    const float scaleY = Constants::MAX_IMAGE_HEIGHT / static_cast<float>(textureSize.y);

    float finalScale = std::min(scaleX, scaleY);

    if (finalScale > 1.f) {
        finalScale = 1.f;
    }

    sprite.setScale(sf::Vector2f(finalScale, finalScale));
}

sf::Image EdgeDetection(const sf::Image& image) {
    sf::Image edgeImage;
    edgeImage.resize(sf::Vector2u(image.getSize().x, image.getSize().y));

    for (int y = 0; y <image.getSize().y; y++) {
        for (int x = 0; x <image.getSize().x; x++) {
            double totalR = 0, totalG = 0, totalB = 0;
            double totalR2 = 0, totalG2 = 0, totalB2 = 0;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    const int srcX = x + i - 1;
                    const int srcY = y + j - 1;

                    if (srcX >= 0 && srcY >= 0 && srcX < image.getSize().x && srcY < image.getSize().y) {
                        constexpr double kernel[3][3] = {
                            { 0, 0, 0 },
                            { -1, 1, 0 },
                            { 0, 0, 0 }
                        };
                        constexpr double kernel2[3][3] = {
                            { 0, -1, 0 },
                            { 0, 1, 0 },
                            { 0, 0, 0 }
                        };
                        const sf::Color pixel = image.getPixel(sf::Vector2u(srcX, srcY));

                        totalR += kernel[i][j] * pixel.r;
                        totalG += kernel[i][j] * pixel.g;
                        totalB += kernel[i][j] * pixel.b;

                        totalR2 += kernel2[i][j] * pixel.r;
                        totalG2 += kernel2[i][j] * pixel.g;
                        totalB2 += kernel2[i][j] * pixel.b;
                    }
                }
            }

            const int finalR = 255 - static_cast<int>(std::sqrt(totalR * totalR + totalR2 * totalR2));
            const int finalG = 255 - static_cast<int>(std::sqrt(totalG * totalG + totalG2 * totalG2));
            const int finalB = 255 - static_cast<int>(std::sqrt(totalB * totalB + totalB2 * totalB2));

            edgeImage.setPixel(sf::Vector2u(x, y), sf::Color(finalR, finalG, finalB));
        }
    }

    return edgeImage;
}

sf::Image ColorFilter(const sf::Image& image, const sf::Color color) {
    sf::Image monoColorImage;
    monoColorImage.resize(sf::Vector2u(image.getSize().x, image.getSize().y));

    for (int y = 0; y < image.getSize().y; y++) {
        for (int x = 0; x < image.getSize().x; x++) {
            sf::Color pixel = image.getPixel(sf::Vector2u(x, y));

            if (color == sf::Color::Red) {
                monoColorImage.setPixel(sf::Vector2u(x, y), sf::Color(pixel.r, 0, 0));
            }
            else if (color == sf::Color::Green) {
                monoColorImage.setPixel(sf::Vector2u(x, y), sf::Color(0, pixel.g, 0));
            }
            else if (color == sf::Color::Blue) {
                monoColorImage.setPixel(sf::Vector2u(x, y), sf::Color(0, 0, pixel.b));
            }
        }
    }

    return monoColorImage;
}

sf::Image ImageConvolution(const sf::Image& image) {
    sf::Image smoothImage;
    smoothImage.resize(sf::Vector2u(image.getSize().x, image.getSize().y));

    for (int y = 0; y <image.getSize().y; y++) {
        for (int x = 0; x <image.getSize().x; x++) {
            double totalR = 0, totalG = 0, totalB = 0;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    const int srcX = x + i - 1;
                    const int srcY = y + j - 1;

                    if (srcX >= 0 && srcY >= 0 && srcX < image.getSize().x && srcY < image.getSize().y) {
                        constexpr double kernel[3][3] = {
                            { 1.0/10, 1.0/10, 1.0/10 },
                            { 1.0/10, 2.0/10, 1.0/10 },
                            { 1.0/10, 1.0/10, 1.0/10 }
                        };
                        const sf::Color pixel = image.getPixel(sf::Vector2u(srcX, srcY));

                        totalR += kernel[i][j] * pixel.r;
                        totalG += kernel[i][j] * pixel.g;
                        totalB += kernel[i][j] * pixel.b;
                    }
                }
            }

            const int finalR = std::max(0, std::min(255, static_cast<int>(totalR)));
            const int finalG = std::max(0, std::min(255, static_cast<int>(totalG)));
            const int finalB = std::max(0, std::min(255, static_cast<int>(totalB)));

            smoothImage.setPixel(sf::Vector2u(x, y), sf::Color(finalR, finalG, finalB));
        }
    }

    return smoothImage;
}

sf::Image Mosaic(const sf::Image& image, const int mosaicSize) {
    sf::Image mosaicImage;
    mosaicImage.resize(sf::Vector2u(image.getSize().x, image.getSize().y));

    for (int y = 0; y < image.getSize().y; y++) {
        for (int x = 0 ; x < image.getSize().x; x++) {
            const int newX = mosaicSize - x % mosaicSize;
            const int newY = mosaicSize - y % mosaicSize;

            if (x + newX > 0 && y + newY > 0 && x + newX < image.getSize().x && y + newY < image.getSize().y) {
                const sf::Color pixel = image.getPixel(sf::Vector2u(x + newX, y + newY));

                const int red = pixel.r;
                const int green = pixel.g;
                const int blue = pixel.b;
                mosaicImage.setPixel(sf::Vector2u(x, y), sf::Color(red, green, blue));
            }
            else {
                constexpr int red = 0;
                constexpr int green = 0;
                constexpr int blue = 0;
                mosaicImage.setPixel(sf::Vector2u(x, y), sf::Color(red, green, blue));
            }
        }
    }

    return mosaicImage;
}

sf::Image GrayScale(const sf::Image& image) {
    sf::Image grayImage;
    grayImage.resize(sf::Vector2u(image.getSize().x, image.getSize().y));

    for (int y = 0; y < image.getSize().y; y++) {
        for (int x = 0; x < image.getSize().x; x++) {
            const sf::Color pixel = image.getPixel(sf::Vector2u(x, y));
            const int gray = static_cast<int>(0.2126 * pixel.r + 0.7152 * pixel.g + 0.0722 * pixel.b);

            grayImage.setPixel(sf::Vector2u(x, y), sf::Color(gray, gray, gray));
        }
    }

    return grayImage;
}

sf::Image Negative(const sf::Image& image) {
    sf::Image negativeImage;
    negativeImage.resize(sf::Vector2u(image.getSize().x, image.getSize().y));

    constexpr int L = 256;
    double LUT[L] = { 0 };

    for (int i = 0; i < L; i++)
        LUT[i] = (L - 1) - ((log(1 + i) / log(L)) * (L - 1));

    for (int y = 0; y < image.getSize().y; y++) {
        for (int x = 0; x < image.getSize().x; x++) {
            const sf::Color pixel = image.getPixel(sf::Vector2u(x, y));

            const int red = static_cast<int>(LUT[pixel.r]);
            const int green = static_cast<int>(LUT[pixel.g]);
            const int blue = static_cast<int>(LUT[pixel.b]);

            negativeImage.setPixel(sf::Vector2u(x, y), sf::Color(red, green, blue));
        }
    }

    return negativeImage;
}

sf::Image Binarization(const sf::Image& image, const int threshold) {
    sf::Image binarizationImage;
    binarizationImage.resize(sf::Vector2u(image.getSize().x, image.getSize().y));

    for (int y = 0; y < image.getSize().y; y++) {
        for (int x = 0; x < image.getSize().x; x++) {
            const sf::Color pixel = image.getPixel(sf::Vector2u(x, y));
            const int val = static_cast<int>(0.333 * pixel.r + 0.333 * pixel.g + 0.333 * pixel.b);

            if (val > threshold * 255.0 / 100) {
                binarizationImage.setPixel(sf::Vector2u(x, y), sf::Color(255, 255, 255));
            }
            else {
                binarizationImage.setPixel(sf::Vector2u(x, y), sf::Color(0, 0, 0));
            }
        }
    }

    return binarizationImage;
}