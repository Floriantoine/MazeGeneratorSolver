/*
** EPITECH PROJECT, 2024
** history.c
** File description:
** Solve history management for step mode
*/

#include "toolbox.h"
#include "param.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int copy_map_snapshot(param_t *param)
{
    param->solve_snapshot = malloc(sizeof(char *) * (param->size_x));
    if (!param->solve_snapshot)
        return (1);
    for (int i = 0; i < param->size_x; ++i) {
        param->solve_snapshot[i] = malloc(sizeof(char) * (param->size_y + 1));
        if (!param->solve_snapshot[i])
            return (1);
        memcpy(param->solve_snapshot[i], param->map[i], param->size_y + 1);
    }
    return (0);
}

void record_draw(param_t *param, int y, int x, char ch, int color)
{
    if (param->history_size < param->history_cap) {
        param->history[param->history_size].x = x;
        param->history[param->history_size].y = y;
        param->history[param->history_size].ch = ch;
        param->history[param->history_size].color = color;
        param->history_size += 1;
        param->history_view = param->history_size;
    }
    print_ncurses(ch, color, y, x, param);
}

void render_history_view(param_t *param, int view)
{
    int map_row = (param->window_x - param->size_x) / 2;
    int map_col = (param->window_y - param->size_y) / 2;

    if (!param->solve_snapshot)
        return;
    clear();
    print_map(param->solve_snapshot, param->size_x, param);
    for (int i = 0; i < view && i < param->history_size; ++i) {
        attron(COLOR_PAIR(param->history[i].color));
        mvprintw(map_row + param->history[i].y,
            map_col + param->history[i].x, "%c", param->history[i].ch);
        attroff(COLOR_PAIR(param->history[i].color));
    }
    print_state(param);
    refresh();
}
