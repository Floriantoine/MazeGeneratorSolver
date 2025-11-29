/*
** EPITECH PROJECT, 2018
** CPE_dante_2018
** File description:
** check_pos.c
*/

#include "param.h"
#include "struct.h"
#include <stdio.h>

int check_that(int x, int y, param_t *param) {
    if (x < 0 || y < 0 || x > param->size_x - 1 || y > param->size_y - 1)
        return (0);
    if (param->map[x][y] != 'X')
        return (1);
    return (0);
}

int check_pos(info_pos_t *info, param_t *param) {
    int out = 0;

    if (info->new_x < 0 || info->new_y < 0 ||
    info->new_x > param->size_x - 1 || info->new_y > param->size_y - 1)
        return (1);
    if (param->map[info->new_x][info->new_y] != 'X')
        return (1);
    out += check_that(info->new_x + 1, info->new_y, param);
    out += check_that(info->new_x - 1, info->new_y, param);
    out += check_that(info->new_x, info->new_y - 1, param);
    out += check_that(info->new_x, info->new_y + 1, param);
    if ((4 - out) < 3)
        return (1);
    return (0);
}
