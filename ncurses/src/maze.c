/*
** EPITECH PROJECT, 2019
** maze.c
** File description:
** All about maze_open it and stock it
*/

#include "maze.h"
#include "tools.h"
#include <unistd.h>
#include <malloc.h>
#include <string.h>

void print_maze(maze_t *maze)
{
    int i = 0;

    while (i < maze->height) {
        printf("%s\n", maze->maze[i]);
        ++i;
    }
}