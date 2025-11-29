/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main for Dante solver
*/

#include "main.h"
#include "enum.h"
#include "maze.h"
#include "param.h"
#include "toolbox.h"
#include "tools.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

int init(void)
{
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, true);
    if (has_colors() == FALSE) {
        printf("Your terminal does not support color\n");
        return (1);
    }
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_WHITE);
    init_pair(5, COLOR_BLUE, COLOR_BLUE);
    init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);
    return (0);
}

void free_tab(char **tab)
{
    int n = 0;

    while (tab[n] != NULL) {
        free(tab[n]);
        ++n;
    }
}

static int is_number(char const *str)
{
    int i = 0;

    if (!str || !str[0])
        return (0);
    while (str[i]) {
        if (isdigit((unsigned char)str[i]) == 0)
            return (0);
        ++i;
    }
    return (1);
}

int check_param(int ac, char **argv, param_t *param)
{
    int numeric = 0;

    param->loop = 999;
    param->speed = 1000;
    param->show_stats = 0;
    param->panel_top = 0;
    param->step_mode = 0;
    param->step_run = 0;
    param->step_finish = 0;
    param->solve_snapshot = NULL;
    for (int i = 1; i < ac; ++i) {
        if (is_number(argv[i])) {
            if (numeric == 0)
                param->loop = atoi(argv[i]);
            else if (numeric == 1)
                param->speed = atoi(argv[i]);
            ++numeric;
            continue;
        }
        if (strcmp(argv[i], "--no-stats") == 0) {
            param->show_stats = 0;
            continue;
        }
        if (strcmp(argv[i], "--stats") == 0 || strcmp(argv[i], "--show-stats") == 0) {
            param->show_stats = 1;
            continue;
        }
        if (strcmp(argv[i], "--step") == 0) {
            param->step_mode = 1;
            continue;
        }
    }

    return (0);
}

int main(int ac, char **argv)
{
    param_t param;
    srand(time(NULL));
    maze_t maze;
    int n = 0;
    const int panel_width = 24;
    struct timespec gen_start;
    struct timespec gen_end;
    struct timespec solve_start;
    struct timespec solve_end;
    int max_stack_cells = 0;

    init();
    if (check_param(ac, argv, &param))
        return (84);
    while (n < param.loop) {
        reset_stats(&param);
        param.stats.seed = (unsigned int)time(NULL) ^ (unsigned int)n;
        srand(param.stats.seed);
        getmaxyx(stdscr, param.window_x, param.window_y);
        param.panel_top = 0;
        int reserve_right = (param.show_stats) ? panel_width : 0;
        int max_rows = param.window_x - 2;
        int max_cols = param.window_y - reserve_right - 2;
        if (max_rows < 5)
            max_rows = 5;
        if (max_cols < 5)
            max_cols = 5;
        param.size_x = (max_rows > 5) ? randy(5, max_rows, -1) : 5;
        param.size_y = (max_cols > 5) ? randy(5, max_cols, -1) : 5;
        max_stack_cells = param.size_x * param.size_y;
        param.history_cap = max_stack_cells * 2;
        param.solve_stack = malloc(sizeof(coord_t) * max_stack_cells);
        param.history = malloc(sizeof(solve_event_t) * param.history_cap);
        param.history_size = 0;
        param.history_view = 0;
        if (!param.solve_stack)
            return (84);
        if (!param.history)
            return (84);
        param.solve_stack_size = 0;
        clock_gettime(CLOCK_MONOTONIC, &gen_start);
        if (generator(&param)) {
            free(param.solve_stack);
            free(param.history);
            return (84);
        }
        clock_gettime(CLOCK_MONOTONIC, &gen_end);
        param.stats.gen_ms = (gen_end.tv_sec - gen_start.tv_sec) * 1000
        + (gen_end.tv_nsec - gen_start.tv_nsec) / 1000000;
        if (copy_map_snapshot(&param))
            return (84);
        maze.maze = param.map;
        maze.height = param.size_x;
        maze.width = param.size_y;
        clock_gettime(CLOCK_MONOTONIC, &solve_start);
        solve(&maze, &param);
        clock_gettime(CLOCK_MONOTONIC, &solve_end);
        param.stats.solve_ms = (solve_end.tv_sec - solve_start.tv_sec) * 1000
        + (solve_end.tv_nsec - solve_start.tv_nsec) / 1000000;
        print_state(&param);
        if (param.step_finish) {
            mvprintw(param.window_x - 1, 1,
                "Solve finished (fast-forward). Press any key to continue.");
            refresh();
            getch();
            param.step_mode = 1;
            param.step_run = 0;
            param.step_finish = 0;
        }
        free_tab(param.map);
        free(param.solve_stack);
        free(param.history);
        if (param.solve_snapshot) {
            for (int i = 0; i < param.size_x; ++i)
                free(param.solve_snapshot[i]);
            free(param.solve_snapshot);
            param.solve_snapshot = NULL;
        }
        param.solve_stack = NULL;
        param.solve_stack_size = 0;
        clear();
        ++n;
    }
    endwin();
    return (0);
}
