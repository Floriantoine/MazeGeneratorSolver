#pragma once

#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>

using Map = std::vector<std::string>;
class Maze
{
private:
    sf::Vector2i _firstPos;
    sf::Vector2i _mapSize;
    Map _map;
    std::vector<sf::Vector2i> _posList;
    sf::Vector2i _nextPos;
public:
enum maze_elements {
        TO_VISIT = '*',
        VISITED = 'v',
        WALL = 'X',
        PATH = 'o',
    };
    Maze(sf::Vector2i size);
    ~Maze() = default;
    int body();

    int check_that(int x, int y);
    int check_pos();
    int check_all();
    int check_posibility(int x, int y);
    int check_that_all(int x, int y);

    void take_new_pos();
    int check_new_pos(sf::Vector2i pos);
    int force_pos();

    sf::Vector2i getMapSize() { return _mapSize; };
    Map getMap() { return _map; };

    int backtracking_solve(sf::Vector2i pos, int i);
    int solver();
};
