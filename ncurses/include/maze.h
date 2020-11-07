/*
** EPITECH PROJECT, 2018
** CPE_dante_2018
** File description:
** maze.h
*/

#ifndef MAZE_H_
    #define MAZE_H_
    #include "param.h"
    typedef struct maze_s {
        int height;
        int width;
        int x;
        int y;
        char **maze;
    }   maze_t;

    enum maze_elements {
        TO_VISIT = '*',
        VISITED = 'v',
        WALL = 'X',
        PATH = 'o',
    };

    int maze_parser(maze_t *maze, char *av);
    void print_maze(maze_t *maze);
    int solve(maze_t *maze, param_t *param);
#endif