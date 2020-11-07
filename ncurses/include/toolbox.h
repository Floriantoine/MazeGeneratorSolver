/*
** EPITECH PROJECT, 2018
** CPE_dante_2018
** File description:
** toolbox.h
*/

#ifndef TOOLBOX_H
#define TOOLBOX_H
#include "param.h"
int randy(int min, int max, int nop);
void print_map(char **map, int x, param_t *param);
void my_putchar(char c, int nb);
int my_putstr( char const *str, int output);
void print_caract(int color, param_t *param);
void print_ncurses(char carac, int color, int x, int y, param_t *param);
#endif
