/*
** EPITECH PROJECT, 2018
** CPE_dante_2018
** File description:
** generator.h
*/

#ifndef CHECK_H
#define CHECK_H
    #include "struct.h"
    #include "param.h"
    int check_all(param_t *param, info_pos_t *info);
    int check_ancestor(int x, int y, info_pos_t *info);
    int check_pos(info_pos_t *info, param_t *param);
    int check_that(int x, int y, param_t *param, info_pos_t *info);
#endif
