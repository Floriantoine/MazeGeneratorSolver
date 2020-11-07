/*
** EPITECH PROJECT, 2018
** CPE_dante_2018
** File description:
** toolbox.h
*/

#ifndef TOOLBOX_H
#define TOOLBOX_H
#include "sfmlClass.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
int randy(int min, int max, int nop);
void my_putchar(char c, int nb);
int my_putstr( char const *str, int output);
void print_caract(sf::Color color, sf::Vector2i lastPos, sf::Vector2i mapSize, sfmlClass *sfmInf);
void print_sfml(sf::Color, int x, int y, sf::Vector2i mapSize);
#endif
