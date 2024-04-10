#ifndef __GAME_H
#define __GAME_H

class Game : public sf::Drawable {
public:
	Game(Game const&) = delete;
	void operator = (Game const&) = delete;

	static Game& getInstance();

	void registerEvent(const sf::Event& event);

	void update(double elapsed);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Game();

private:
	Level m_current_level;
	sf::Texture m_player_texture;
	sf::Sprite m_player;

	Animation m_player_blink = Animation(m_player);
};

#endif /* __GAME_H */