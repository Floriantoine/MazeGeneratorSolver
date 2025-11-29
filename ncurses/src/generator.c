/*
** EPITECH PROJECT, 2018
** CPE_dante_2018
** File description:
** generator.c
*/

#include "param.h"
#include "check.h"
#include "toolbox.h"
#include "struct.h"
#include "take_pos.h"
#include "enum.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

int init_all(info_pos_t *info, param_t *param)
{
    info->new_x = 1;
    info->new_y = 0;
    pos_list_t *list = malloc(sizeof(pos_list_t));
    list->prev = NULL;
    list->x = 0;
    list->y = 0;
    param->last_pos = list;
    param->stack_depth = 1;
    param->stats.depth_max = 1;
    return (0);
}

int alloc_map(param_t *param)
{
    int n = 0;

    param->map = malloc(sizeof(char *) * (param->size_x + 1));
    if (!param->map)
        return (1);
    while (n < param->size_x) {
        param->map[n] = malloc(sizeof(char) * (param->size_y + 1));
        if (!param->map[n])
            return (1);
        memset(param->map[n], 'X', (sizeof(char) * param->size_y));
        param->map[n][param->size_y] = '\0';
        ++n;
    }
    param->map[param->size_x] = NULL;
    param->map[0][0] = '*';
    return (0);
}

void unperfect(param_t *param)
{
    for (int i = 0; i < 100 ; i++) {
        param->map[randy(0, param->size_x, -1)][randy(0, param->size_y, -1)] = '*';
        param->map[randy(param->size_x /2 , param->size_x, -1)][randy(param->size_y /2, param->size_y, -1)] = '*';
    }
}

int body(param_t *param, info_pos_t *info, int go)
{
    while (param->last_pos->prev != NULL || go != 0) {
        go = 0;
        if (check_pos(info, param) == 0) {
            pos_list_t *list = malloc(sizeof(pos_list_t));
            list->x = info->new_x;
            list->y = info->new_y;
            list->prev = param->last_pos;
            param->last_pos = list;
            ++param->stack_depth;
            if (param->stack_depth > param->stats.depth_max)
                param->stats.depth_max = param->stack_depth;
            ++param->stats.gen_steps;
            print_caract(RED_C, param);
            param->map[info->new_x][info->new_y] = '*';
        } else if (check_all(param, info)) {
            pos_list_t *tempo = param->last_pos;
            param->last_pos = param->last_pos->prev;
            free(tempo);
            ++param->stats.gen_backtracks;
            if (param->stack_depth > 1)
                --param->stack_depth;
            print_caract(GREEN_C, param);
            info->new_x = param->last_pos->x;
            info->new_y = param->last_pos->y;
        } else {
            info->new_x = param->last_pos->x;
            info->new_y = param->last_pos->y;
        }
        take_new_pos(info, param);
        print_state(param);
    }
    unperfect(param);
    print_state(param);
    return (0);
}

int generator(param_t *param) {
    info_pos_t info;
    int go = 1;
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW);

    if (alloc_map(param) || init_all(&info, param))
        return (1);
    print_map(param->map, param->size_x, param);
    refresh();
    return (body(param, &info, go));
}
