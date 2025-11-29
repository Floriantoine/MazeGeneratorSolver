/*
** EPITECH PROJECT, 2018
** CPE_dante_2018
** File description:
** print_map.c
*/

#include "toolbox.h"
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

void print_ncurses(char carac, int color, int x, int y, param_t *param)
{
    char str[2];
    str[0] = carac;
    str[1] = '\0';
    attron(COLOR_PAIR(color));
    mvprintw(x + (param->window_x - param->size_x)/ 2,
    y + (param->window_y - param->size_y)/ 2, str);
    attroff(COLOR_PAIR(color));
    refresh();
    usleep(param->speed);
}

void print_caract(int color, param_t *param)
{
    attron(COLOR_PAIR(color));
    mvprintw(param->last_pos->x + (param->window_x - param->size_x)/ 2,
    param->last_pos->y + (param->window_y - param->size_y)/ 2, "*");
    attroff(COLOR_PAIR(color));
    refresh();
    usleep(param->speed);
}

void print_map(char **map, int x, param_t *param) {
    int n = 0;
    (void)x;

    attron(COLOR_PAIR(4));
    while (n < param->size_x) {
        mvaddstr(n + (param->window_x - param->size_x)/ 2,
        (param->window_y - param->size_y)/ 2, map[n]);
        ++n;
    }
    attroff(COLOR_PAIR(4));
}
