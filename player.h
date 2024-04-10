#ifndef __PLAYER_H
#define __PLAYER_H

class Player : sf::Drawable {

public:
	Player();

	virtual ~Player();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void reset(const sf::Vector2f& newPos);

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	Animation m_blink;
};

#endif /* __PLAYER_H */