#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "animation.h"

#include "level.h"

#include "game.h"

Game&
Game::getInstance() {
	static Game instance;

	return instance;
}

Game::Game() {
    m_player_texture.loadFromFile("assets/textures/spritesheet_player.png");
    m_player = sf::Sprite{ m_player_texture, sf::IntRect(0, 0, 32, 32) };

    m_player_blink.setMode(Animation::Mode::LOOP);
    m_player_blink.addFrame({ sf::IntRect(32 * 1, 0, 32, 32), 0.1 });
    m_player_blink.addFrame({ sf::IntRect(32 * 2, 0, 32, 32), 0.1 });
    m_player_blink.addFrame({ sf::IntRect(32 * 3, 0, 32, 32), 0.1 });
    m_player_blink.addFrame({ sf::IntRect(32 * 4, 0, 32, 32), 0.2 });
    m_player_blink.addFrame({ sf::IntRect(32 * 3, 0, 32, 32), 0.1 });
    m_player_blink.addFrame({ sf::IntRect(32 * 2, 0, 32, 32), 0.1 });
    m_player_blink.addFrame({ sf::IntRect(32 * 1, 0, 32, 32), 0.1 });
    m_player_blink.addFrame({ sf::IntRect(0, 0, 32, 32), 0.1 });

    m_current_level.load("assets/levels/01.lvl");
    m_player.setPosition(m_current_level.getPlayerPos());
}

void
Game::registerEvent(const sf::Event& event) {
    // Check for keypress events
    if (event.type == sf::Event::KeyPressed) {
        auto& pos = m_player.getPosition();

        switch (event.key.code) {
        case sf::Keyboard::Left:
        case sf::Keyboard::A:
            m_player.setPosition(pos.x - 5, pos.y);
            break;
        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            m_player.setPosition(pos.x + 5, pos.y);
            break;
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
            m_player.setPosition(pos.x, pos.y - 5);
            break;
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            m_player.setPosition(pos.x, pos.y + 5);
            break;
        }
    }
}

void
Game::update(double elapsed) {
    m_player_blink.update(elapsed);
}

void
Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_current_level, states);
    target.draw(m_player, states);
}