/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main for Dante solver
*/

#include "main.h"
#include "enum.h"
#include "maze.h"
#include "param.h"
#include "time.h"
#include "toolbox.h"
#include "tools.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int init(void)
{
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, true);
    if (has_colors() == FALSE) {
        printf("Your terminal does not support color\n");
        return (1);
    }
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_WHITE);
    init_pair(5, COLOR_BLUE, COLOR_BLUE);
    init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
    return (0);
}

void free_tab(char **tab)
{
    int n = 0;

    while (tab[n] != NULL) {
        free(tab[n]);
        ++n;
    }
}

int check_param(int ac, char **argv, param_t *param)
{
    if (ac < 3)
        param->speed = 1000;
    else
        param->speed = atoi(argv[2]);
    if (ac < 2)
        param->loop = 999;
    else
        param->loop = atoi(argv[1]);

    return (0);
}

int main(int ac, char **argv)
{
    param_t param;
    srand(time(NULL));
    maze_t maze;
    int n = 0;

    init();
    if (check_param(ac, argv, &param))
        return (84);
    while (n < param.loop) {
        getmaxyx(stdscr, param.window_x, param.window_y);
        param.size_x = randy(5, param.window_x, -1);
        param.size_y = randy(5, param.window_y, -1);
        if (generator(&param))
            return (84);
        maze.maze = param.map;
        maze.height = param.size_x;
        maze.width = param.size_y;
        solve(&maze, &param);
        free_tab(param.map);
        clear();
        ++n;
    }
    endwin();
    return (0);
}