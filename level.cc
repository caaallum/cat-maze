#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "level.h"
#include <fstream>
#include <sstream>

static constexpr unsigned int tile_size = 32;
static constexpr unsigned int width  = 25;
static constexpr unsigned int height = 18;

Level::Level() {
    m_tileset.loadFromFile("assets/textures/spritesheet_background.png");
}

void 
Level::load(const std::string& level) {
    std::ifstream file(level);
    m_level_data = nlohmann::json::parse(file).get<LevelData>();

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(width * height * 6);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = m_level_data.data[i + j * width];

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tile_size);
            int tv = tileNumber / (m_tileset.getSize().x / tile_size);

            // get a pointer to the triangles' vertices of the current tile
            sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];

            // define the 6 corners of the two triangles
            triangles[0].position = sf::Vector2f(i * tile_size, j * tile_size);
            triangles[1].position = sf::Vector2f((i + 1) * tile_size, j * tile_size);
            triangles[2].position = sf::Vector2f(i * tile_size, (j + 1) * tile_size);
            triangles[3].position = sf::Vector2f(i * tile_size, (j + 1) * tile_size);
            triangles[4].position = sf::Vector2f((i + 1) * tile_size, j * tile_size);
            triangles[5].position = sf::Vector2f((i + 1) * tile_size, (j + 1) * tile_size);

            // define the 6 matching texture coordinates
            triangles[0].texCoords = sf::Vector2f(tu * tile_size, tv * tile_size);
            triangles[1].texCoords = sf::Vector2f((tu + 1) * tile_size, tv * tile_size);
            triangles[2].texCoords = sf::Vector2f(tu * tile_size, (tv + 1) * tile_size);
            triangles[3].texCoords = sf::Vector2f(tu * tile_size, (tv + 1) * tile_size);
            triangles[4].texCoords = sf::Vector2f((tu + 1) * tile_size, tv * tile_size);
            triangles[5].texCoords = sf::Vector2f((tu + 1) * tile_size, (tv + 1) * tile_size);
        }
    }
}

const 
sf::Vector2f Level::getPlayerPos() const
{
    sf::Vector2f pos{ m_level_data.player_pos };
    pos.x *= tile_size;
    pos.y *= tile_size;
    return pos;
}

void
sf::from_json(const nlohmann::json& j, Vector2u& data) {
    j.at("x").get_to(data.x);
    j.at("y").get_to(data.y);
}

void
from_json(const nlohmann::json& j, LevelData& data) {
    j.at("data").get_to(data.data);
    j.at("player").get_to(data.player_pos);
}

void
Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}

std::vector<int> Level::loadLevelFromDisk(const std::string& level_file)
{
    std::vector<int> level_data;
    std::ifstream file(level_file);
    bool level = false, player = false;
    int level_offset = height;
    for (std::string line; getline(file, line);) {

        // Ignore comments
        if (line.rfind("//", 0) == 0) {
            continue;
        }

        // Ignore blank lines
        if (line.length() == 0) {
            continue;
        }

        // Check for value modifiers
        if (line == "[Level]") {
            level = true;
            continue;
        }

        if (line == "[Player]") {
            player = true;
        }

        if (level) {
            if (level_offset == 0) {
                level = false;
            }
            std::istringstream ss(line);
            for (std::string c; getline(ss, c, ' ');) {
                level_data.push_back(std::stoi(c));
            }
            level_offset--;
        }

        if (player) {
            player = false;

            std::istringstream ss(line);
            unsigned int pos[2];
            std::vector<unsigned int> pos_points;
            for (std::string c; getline(ss, c, ' ');) {
                pos_points.push_back(std::stoi(c));
            }


        }
    }
    return level_data;
}
