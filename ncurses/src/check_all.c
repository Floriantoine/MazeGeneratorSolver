/*
** EPITECH PROJECT, 2018
** CPE_dante_2018
** File description:
** check_all.c
*/

#include "struct.h"
#include "check.h"
#include "param.h"
#include <stdio.h>

int check_that_all(int x, int y, param_t *param) {
    if (x < 0 || y < 0 || x > param->size_x - 1 || y > param->size_y - 1)
        return (0);
    if (param->map[x][y] != 'X')
        return (1);
    return (0);
}

int check_posibility(int x, int y, param_t *param) {
    int out = 0;

    if (x < 0 || y < 0 || x > param->size_x - 1 || y > param->size_y - 1)
        return (1);
    if (param->map[x][y] != 'X')
        return (1);
    out += check_that_all(x + 1, y, param);
    out += check_that_all(x - 1, y, param);
    out += check_that_all(x, y - 1, param);
    out += check_that_all(x, y + 1, param);
    if ((4 - out) < 3)
        return (1);
    return (0);
}

int check_all(param_t *param, info_pos_t *info) {
    int out = 0;
    (void)info;

    out += check_posibility(param->last_pos->x - 1, param->last_pos->y, param);
    out += check_posibility(param->last_pos->x + 1, param->last_pos->y, param);
    out += check_posibility(param->last_pos->x, param->last_pos->y + 1, param);
    out += check_posibility(param->last_pos->x, param->last_pos->y - 1, param);
    if ((4 - out) < 1)
        return (1);
    return (0);
}
