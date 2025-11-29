/*
** EPITECH PROJECT, 2018
** CPE_dante_2018
** File description:
** take_pos.c
*/

#include "toolbox.h"
#include "param.h"
#include "struct.h"
#include "check.h"
#include <stdio.h>
#include <unistd.h>

int check_that_all(int x, int y, param_t *param);

int check_new_pos(int x, int y, param_t *param)
{
    int out = 0;

    if (x < 0 || y < 0 || x > param->size_x - 1 || y > param->size_y - 1)
        return (1);
    if (param->map[x][y] != 'X')
        return (1);
    out += check_that_all(x - 1, y, param);
    out += check_that_all(x + 1, y, param);
    out += check_that_all(x, y + 1, param);
    out += check_that_all(x, y - 1, param);
    if (4 - out < 3)
        return (1);
    return (0);
}

int force_pos(param_t *param, info_pos_t *info)
{
    if (((param->last_pos->x == param->size_x - 2
    && param->last_pos->y == param->size_y - 1 ) ||
    (param->last_pos->x == param->size_x - 1
    && param->last_pos->y == param->size_y - 2))
    && param->map[param->size_x - 1][param->size_y - 1] == 'X') {
        info->new_x = param->size_x - 1;
        info->new_y = param->size_y - 1;
        return (1);
    }
    return (0);
}

void take_new_pos(info_pos_t *info, param_t *param)
{
    int tab[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int side = randy(0, 4, -1);
    int x = param->last_pos->x;
    int y = param->last_pos->y;

    if (force_pos(param, info) == 0) {
        x += tab[side][0];
        y += tab[side][1];
        side = 0;
        while (side <  4 && check_new_pos(x, y, param) == 1) {
            x = param->last_pos->x + tab[side][0];
            y = param->last_pos->y + tab[side][1];
            side++;
        }
        info->new_x = x;
        info->new_y = y;
    }
}
