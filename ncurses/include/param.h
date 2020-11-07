/*
** EPITECH PROJECT, 2018
** CPE_dante_2018
** File description:
** param.h
*/

#ifndef PARAM_H
#define PARAM_H
    typedef struct pos_list
    {
        int x;
        int y;
        struct pos_list *prev;
    }pos_list_t;

    typedef struct
    {
        int window_x;
        int window_y;
        int speed;
        int loop;
        int size_x;
        int size_y;
        char **map;
        pos_list_t *last_pos;
    }param_t;
#endif
