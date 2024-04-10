#include "common.h"


int main() {
    auto window = sf::RenderWindow{ { 800u, 576u}, "Cat Maze" };
    auto image = sf::Image{};
    image.loadFromFile("assets/icon.png");

    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    window.setFramerateLimit(144);
    
    auto& game = Game::getInstance();

    sf::Clock clock;
    while (window.isOpen()) {
        auto elapsed = clock.restart().asSeconds();

        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            game.registerEvent(event);
        }

        window.clear();
        game.update(elapsed);
        window.draw(game);
        window.display();
    }
}