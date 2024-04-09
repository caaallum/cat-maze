#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

#include <nlohmann/json.hpp>
#include "animation.h"
#include "level.h"


int main()
{
    auto window = sf::RenderWindow{ { 800u, 576u}, "Cat Maze" };
    window.setFramerateLimit(144);

    auto texture = sf::Texture{};
    texture.loadFromFile("assets/spritesheet.png");

    auto sprite = sf::Sprite{ texture, sf::IntRect(0, 0, 32, 32)};

    auto animation = Animation{ sprite };
    animation.addFrame({ sf::IntRect(32 * 1, 0, 32, 32), 0.1 });
    animation.addFrame({ sf::IntRect(32 * 2, 0, 32, 32), 0.1 });
    animation.addFrame({ sf::IntRect(32 * 3, 0, 32, 32), 0.1 });
    animation.addFrame({ sf::IntRect(32 * 4, 0, 32, 32), 0.2 });
    animation.addFrame({ sf::IntRect(32 * 3, 0, 32, 32), 0.1 });
    animation.addFrame({ sf::IntRect(32 * 2, 0, 32, 32), 0.1 });
    animation.addFrame({ sf::IntRect(32 * 1, 0, 32, 32), 0.1 });
    animation.addFrame({ sf::IntRect(0, 0, 32, 32), 0.1 });
    
    //const int level[] = {
    //    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    //    0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
    //    1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
    //    0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
    //    0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
    //    0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
    //    2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
    //    0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    //};
    const int level[] = {
        0,  0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
        0, 13, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 0,
        0,  0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
        0,  0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
        0,  0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
        0,  0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
        0,  0, 0, 0, 0, 0, 0, 0, 0,  4,  5,  5,  5,  2, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
        0,  0, 0, 0, 0, 0, 0, 0, 0,  7, 14, 14, 14,  6, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
        0,  0, 0, 0, 0, 0, 0, 0, 0,  7, 14, 14, 14,  6, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
        0,  0, 0, 0, 0, 0, 0, 0, 0,  7, 14, 14, 14,  6, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
        0,  0, 0, 0, 0, 0, 0, 0, 0, 12,  8,  8,  8, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
        0,  0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
        0,  0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
        0,  0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
        0,  0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
        0,  0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
        0, 13, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 0,
        0,  0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0,
    };
    auto background = Level{};
    background.load("assets/levels/01.lvl");

    sprite.setPosition(background.getPlayerPos());

    sf::Clock clock;
    while (window.isOpen()) {
        auto elapsed = clock.restart();

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
            auto& pos = sprite.getPosition();
            switch (event.type) {
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    sprite.setPosition(pos.x - 5, pos.y);
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    sprite.setPosition(pos.x + 5, pos.y);
                    break;
                }
                break;
            }
        }

        window.clear();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            animation.update(elapsed.asSeconds());
        }

        window.draw(background);
        window.draw(sprite);
        window.display();
    }
}