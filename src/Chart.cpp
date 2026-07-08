#include "Chart.hpp"

Chart::Chart(const sf::Vector2f position, const sf::Vector2f size) :
verticesR(sf::PrimitiveType::Lines),
verticesG(sf::PrimitiveType::Lines),
verticesB(sf::PrimitiveType::Lines){

    setPosition(position);
    setSize(size);

    background.setPosition(position);
    background.setSize(size);
    background.setFillColor(sf::Color(30,30,30,200));
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(1.f);
}

Chart::~Chart() = default;

void Chart::setPosition(sf::Vector2f position) {
    if (position.x >= 0 && position.y >= 0) {
        this->position = position;
    }
}

void Chart::setSize(sf::Vector2f size) {
    if (size.x > 0 && size.y > 0) {
        this->size = size;
    }
}

void Chart::Histogram(const sf::Image &image) {

    int maxFreq = 0;
    constexpr int L = 256;
    int histoR[L] = {0};
    int histoG[L] = {0};
    int histoB[L] = {0};

    for (int y = 0; y < image.getSize().y; y++) {
        for (int x = 0; x < image.getSize().x; x++) {
            const sf::Color color = image.getPixel(sf::Vector2u(x, y));
            histoR[color.r]++;
            histoG[color.g]++;
            histoB[color.b]++;
        }
    }

    for (int i = 0; i < L; i++) {
        if (histoR[i] > maxFreq) maxFreq = histoR[i];
        if (histoG[i] > maxFreq) maxFreq = histoG[i];
        if (histoB[i] > maxFreq) maxFreq = histoB[i];
    }

    if (maxFreq == 0) maxFreq = 1;

    verticesR.clear();
    verticesG.clear();
    verticesB.clear();

    const float stepX = size.x / (L * 1.f);

    for (int i = 0; i < L; ++i) {
        const float x = position.x + (static_cast<float>(i) * stepX);

        const float hR = (static_cast<float>(histoR[i]) / static_cast<float>(maxFreq)) * size.y;
        const float hG = (static_cast<float>(histoG[i]) / static_cast<float>(maxFreq)) * size.y;
        const float hB = (static_cast<float>(histoB[i]) / static_cast<float>(maxFreq)) * size.y;

        sf::Color cR(255, 0, 0, 150);
        sf::Color cG(0, 255, 0, 150);
        sf::Color cB(0, 150, 255, 150);

        verticesR.append(sf::Vertex{sf::Vector2f(x, position.y + size.y), cR});
        verticesR.append(sf::Vertex{sf::Vector2f(x, position.y + size.y - hR), cR});

        verticesG.append(sf::Vertex{sf::Vector2f(x, position.y + size.y), cG});
        verticesG.append(sf::Vertex{sf::Vector2f(x, position.y + size.y - hG), cG});

        verticesB.append(sf::Vertex{sf::Vector2f(x, position.y + size.y), cB});
        verticesB.append(sf::Vertex{sf::Vector2f(x, position.y + size.y - hB), cB});
    }
}

void Chart::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    target.draw(background, states);

    target.draw(verticesR, states);
    target.draw(verticesG, states);
    target.draw(verticesB, states);
}
