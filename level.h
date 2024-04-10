#ifndef __BACKGROUND_H
#define __BACKGROUND_H

struct LevelData {
	std::vector<int> data;
	sf::Vector2u player_pos;
};

namespace sf {
	void from_json(const nlohmann::json& j, Vector2u& data);
}

void from_json(const nlohmann::json& j, LevelData& data);

class Level : public sf::Drawable, public sf::Transformable {
public:
	enum {
		GRASS								= 0,
		GRASS_BORDER_BOTTOM_LEFT			= 1,
		GRASS_BORDER_BOTTOM_LEFT_INVERT		= 2,
		GRASS_BORDER_BOTTOM_RIGHT			= 3,
		GRASS_BORDER_BOTTOM_RIGHT_INVERT	= 4,
		GRASS_BORDER_EDGE_BOTTOM			= 5,
		GRASS_BORDER_EDGE_LEFT				= 6,
		GRASS_BORDER_EDGE_RIGHT				= 7,
		GRASS_BORDER_EDGE_TOP				= 8,
		GRASS_BORDER_TOP_LEFT				= 9,
		GRASS_BORDER_TOP_LEFT_INVERT		= 10,
		GRASS_BORDER_TOP_RIGHT				= 11,
		GRASS_BORDER_TOP_RIGHT_INVERT		= 12,
		GRASS_FLOWERS						= 13,
		BACKGROUND							= 14,
		BACKGROUND_SHADOW_CORNER			= 15,
		BACKGROUND_SHADOW_VERTICAL			= 16,
		BACKGROUND_SHADOW_HORIZONTAL		= 17,
	};

	Level();

	void load(const std::string& level);

	const sf::Vector2f getPlayerPos() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<int> loadLevelFromDisk(const std::string& level);

private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	LevelData m_level_data;
};

#endif /* __BACKGROUND_H */