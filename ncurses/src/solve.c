/*
** EPITECH PROJECT, 2019
** solver.c
** File description:
** solve maze
*/

#include "param.h"
#include "maze.h"
#include "tools.h"
#include "toolbox.h"
#include "enum.h"
#include <ncurses.h>
#include <malloc.h>
#include <stdio.h>

static int backtracking_solve(maze_t *maze, int x, int y, int i, param_t *param)
{
    if (param->solve_stack
        && param->solve_stack_size < param->size_x * param->size_y) {
        param->solve_stack[param->solve_stack_size].x = x;
        param->solve_stack[param->solve_stack_size].y = y;
        ++param->solve_stack_size;
    }
    maze->maze[y][x] = PATH;
    ++param->stats.solve_steps;
    record_draw(param, y, x, PATH, WHITE_C);
    print_state(param);
    wait_step(param);
    if (x == maze->width - 1 && y == maze->height - 1)
        goto success;
    if (x + 1 < maze->width && maze->maze[y][x + 1] == TO_VISIT) {
        if (backtracking_solve(maze, x + 1, y, i + 1, param) == 0)
            goto success;
    }
    if (y + 1 < maze->height && maze->maze[y + 1][x] == TO_VISIT) {
        if (backtracking_solve(maze, x, y + 1, i + 1, param) == 0)
            goto success;
    }
    if (x - 1 >= 0 && maze->maze[y][x - 1] == TO_VISIT) {
        if (backtracking_solve(maze, x - 1, y, i + 1, param) == 0)
            goto success;
    }
    if (y - 1 >= 0 && maze->maze[y - 1][x] == TO_VISIT) {
        if (backtracking_solve(maze, x, y - 1, i + 1, param) == 0)
            goto success;
    }
    maze->maze[y][x] = VISITED;
    ++param->stats.solve_backtracks;
    record_draw(param, y, x, VISITED, 6);
    print_state(param);
    wait_step(param);
    if (param->solve_stack_size > 0)
        --param->solve_stack_size;
    return (1);
success:
    if (param->solve_stack_size > 0)
        --param->solve_stack_size;
    return (0);
}

static void clean_visited(maze_t *maze, param_t *param)
{
    int i = 0;
    int j = 0;

    while (j != maze->height) {
        i = 0;
        while (i != maze->width) {
            if (maze->maze[j][i] == VISITED) {
                maze->maze[j][i] = TO_VISIT;
                print_ncurses(TO_VISIT, RED_C, j, i, param);
            }
            ++i;
        }
        ++j;
    }
}

int solve(maze_t *maze, param_t *param)
{
    int i = 0;

    if (backtracking_solve(maze, 0, 0, i, param) == 1) {
        put_err("No Path\n");
        return (1);
    }
    return (0);
    clean_visited(maze, param);
}
