/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main for Dante solver
*/

#include "Maze.hpp"
#include "sfmlClass.hpp"
#include "toolbox.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <iostream>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML window");
sf::Event event;
sf::RectangleShape rectangle(sf::Vector2f(20, 20));

void onScreen(sf::Vector2f entry, sf::Color color)
{
    rectangle.setFillColor(color);
    rectangle.setPosition(entry);
    window.draw(rectangle);
}

void print_caract(sf::Color color, sf::Vector2i lastPos, sf::Vector2i mapSize,
    sfmlClass *sfmInf)
{
    sf::Vector2f sizeRec(10, 10);

    sfmInf->_vectorVector2f.push_back(sf::Vector2f(
        sizeRec.x * lastPos.x + ((window.getSize().x - mapSize.x * 10) / 2),
        sizeRec.y * lastPos.y + ((window.getSize().y - mapSize.y * 10) / 2)));
    sfmInf->_colorVector.push_back(color);
    rectangle.setSize(sizeRec);

    if (sfmInf->_vectorVector2f.size() > 30) {
        for (size_t i = sfmInf->_vectorVector2f.size() - 50;
             i < sfmInf->_vectorVector2f.size() - 30; i++) {
            onScreen(sfmInf->_vectorVector2f[i], sfmInf->_colorVector[i]);
        }
    }
    for (size_t i = sfmInf->_vectorVector2f.size() - 30;
         i < sfmInf->_vectorVector2f.size(); i++) {
        rectangle.setFillColor(sf::Color(0, 0, 150 + i * 3.0, 255));
        rectangle.setPosition(sfmInf->_vectorVector2f[i]);
        window.draw(rectangle);
    }
    window.display();
}

void print_sfml(sf::Color color, int x, int y, sf::Vector2i mapSize)
{
    sf::Vector2f sizeRec(10, 10);
    rectangle.setFillColor(color);
    if (color == sf::Color::Magenta)
        rectangle.setFillColor(sf::Color(
            50 + 200 / mapSize.y * y, 27, 250, 150 + 100 / mapSize.x * x));
    rectangle.setSize(sizeRec);
    rectangle.setPosition(
        sf::Vector2f(sizeRec.x * x + (window.getSize().x - mapSize.x * 10) / 2,
            sizeRec.y * y + (window.getSize().y - mapSize.y * 10) / 2));
    window.draw(rectangle);
    window.display();
}

int main(int ac, char **argv)
{
    srand(time(NULL));

    window.setFramerateLimit(200);
    while (window.isOpen()) {
        Maze Maze({randy(4, window.getSize().x / 10, -1),
            randy(4, window.getSize().y / 10, -1)});
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed &&
                event.KeyPressed == sf::Keyboard::Escape)
                window.close();
        }

        if (Maze.body() || Maze.solver())
            return (84);
        window.clear();
    }
    return (0);
}
