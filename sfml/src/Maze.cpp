#include "Maze.hpp"
#include "toolbox.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <iostream>

bool toClean = false;

Maze::Maze(sf::Vector2i size)
    : _map(size.x, std::string(size.y, 'X')), _mapSize(size)
{
    _nextPos = {randy(0, size.x, -1), randy(0, size.y, -1)};
    _posList.push_back(_nextPos);
    _firstPos = _nextPos;
};

int Maze::check_new_pos(sf::Vector2i pos)
{
    int out = 0;

    if (pos.x < 0 || pos.y < 0 || pos.x > _mapSize.x - 1 ||
        pos.y > _mapSize.y - 1)
        return (1);
    if (_map[pos.x][pos.y] != 'X')
        return (1);
    out += check_that_all(pos.x - 1, pos.y);
    out += check_that_all(pos.x + 1, pos.y);
    out += check_that_all(pos.x, pos.y + 1);
    out += check_that_all(pos.x, pos.y - 1);
    if (4 - out < 3)
        return (1);
    return (0);
}

int Maze::force_pos()
{
    sf::Vector2i last = _posList.back();

    if (((last.x == _mapSize.x - 2 && last.y == _mapSize.y - 1) ||
            (last.x == _mapSize.x - 1 && last.y == _mapSize.y - 2)) &&
        _map[_mapSize.x - 1][_mapSize.y - 1] == 'X') {
        _nextPos.x = _mapSize.x - 1;
        _nextPos.y = _mapSize.y - 1;
        return (1);
    }
    return (0);
}

void Maze::take_new_pos()
{
    int tab[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int side = randy(0, 4, -1);
    sf::Vector2i last = _posList.back();

    if (force_pos() == 0) {
        last.x += tab[side][0];
        last.y += tab[side][1];
        side = 0;
        while (side < 4 && check_new_pos(last) == 1) {
            last.x = _posList.back().x + tab[side][0];
            last.y = _posList.back().y + tab[side][1];
            side++;
        }
        _nextPos = last;
    }
}

int Maze::check_that_all(int x, int y)
{
    if (x < 0 || y < 0 || x > _mapSize.x - 1 || y > _mapSize.y - 1)
        return (0);
    if (_map[x][y] != 'X')
        return (1);
    return (0);
}

int Maze::check_posibility(int x, int y)
{
    int out = 0;

    if (x < 0 || y < 0 || x > _mapSize.x - 1 || y > _mapSize.y - 1)
        return (1);
    if (_map[x][y] != 'X')
        return (1);
    out += check_that_all(x + 1, y);
    out += check_that_all(x - 1, y);
    out += check_that_all(x, y - 1);
    out += check_that_all(x, y + 1);
    if ((4 - out) < 3)
        return (1);
    return (0);
}

int Maze::check_all()
{
    int out = 0;
    sf::Vector2i last = _posList[_posList.size() - 1];

    out += check_posibility(last.x - 1, last.y);
    out += check_posibility(last.x + 1, last.y);
    out += check_posibility(last.x, last.y + 1);
    out += check_posibility(last.x, last.y - 1);
    if ((4 - out) < 1)
        return (1);
    return (0);
}

int Maze::check_that(int x, int y)
{
    if (x < 0 || y < 0 || x > _mapSize.x - 1 || y > _mapSize.y - 1)
        return (0);
    if (_map[x][y] != 'X')
        return (1);
    return (0);
}

int Maze::check_pos()
{
    int out = 0;

    if (_nextPos.x < 0 || _nextPos.y < 0 || _nextPos.x > _mapSize.x - 1 ||
        _nextPos.y > _mapSize.y - 1)
        return (1);
    if (_map[_nextPos.x][_nextPos.y] != 'X')
        return (1);
    out += check_that(_nextPos.x + 1, _nextPos.y);
    out += check_that(_nextPos.x - 1, _nextPos.y);
    out += check_that(_nextPos.x, _nextPos.y - 1);
    out += check_that(_nextPos.x, _nextPos.y + 1);
    if ((4 - out) < 3)
        return (1);
    return (0);
}

int Maze::body()
{
    sfmlClass sfmlInf;
    while (_posList.size() > 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            return -1;
        if (check_pos() == 0) {
            _posList.push_back(_nextPos);
            print_caract(sf::Color::Red, _posList.back(), _mapSize, &sfmlInf);
            _map[_nextPos.x][_nextPos.y] = '*';
        } else if (check_all()) {
            _posList.pop_back();
            print_caract(sf::Color::Green, _posList.back(), _mapSize, &sfmlInf);
            _nextPos = _posList.back();
        } else {
            print_caract(sf::Color::Green, _posList.back(), _mapSize, &sfmlInf);
            _nextPos = _posList.back();
        }
        take_new_pos();
    }
    return (0);
}

int Maze::solver()
{
    return (backtracking_solve({_firstPos.x, _firstPos.y}, 0));
};

int Maze::backtracking_solve(sf::Vector2i pos, int i)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        std::cout << "cc" << std::endl;
        toClean = !toClean;
    }
    // while (window.pollEvent(event)) {
    //     if (event.type == sf::Event::Closed)
    //         window.close();
    //     if (event.type == sf::Event::KeyPressed &&
    //         event.KeyPressed == sf::Keyboard::Escape)
    //         window.close();
    // }

    _map[pos.x][pos.y] = PATH;
    print_sfml(sf::Color::White, pos.x, pos.y, _mapSize);
    if (pos.x == _mapSize.x - 1 && pos.y == _mapSize.y - 1)
        return (0);
    if (pos.x - 1 >= 0 && _map[pos.x - 1][pos.y] == TO_VISIT) {
        if (backtracking_solve({pos.x - 1, pos.y}, i + 1) == 0)
            return (0);
    }
    if (pos.y - 1 >= 0 && _map[pos.x][pos.y - 1] == TO_VISIT) {
        if (backtracking_solve({pos.x, pos.y - 1}, i + 1) == 0)
            return (0);
    }
    if (pos.x + 1 < _mapSize.x && _map[pos.x + 1][pos.y] == TO_VISIT) {
        if (backtracking_solve({pos.x + 1, pos.y}, i + 1) == 0)
            return (0);
    }
    if (pos.y + 1 < _mapSize.y && _map[pos.x][pos.y + 1] == TO_VISIT) {
        if (backtracking_solve({pos.x, pos.y + 1}, i + 1) == 0)
            return (0);
    }
    _map[pos.x][pos.y] = VISITED;
    if (toClean)
        print_sfml(sf::Color::Black, pos.x, pos.y, _mapSize);
    else
        print_sfml(sf::Color::Magenta, pos.x, pos.y, _mapSize);
    return (1);
}
