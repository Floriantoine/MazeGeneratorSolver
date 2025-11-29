/*
** EPITECH PROJECT, 2018
** CPE_dante_2018
** File description:
** param.h
*/

#ifndef PARAM_H
#define PARAM_H
    typedef struct run_stats
    {
        unsigned int seed;
        long gen_ms;
        long solve_ms;
        unsigned long gen_steps;
        unsigned long gen_backtracks;
        unsigned long solve_steps;
        unsigned long solve_backtracks;
        int depth_max;
    } run_stats_t;

    typedef struct coord_s {
        int x;
        int y;
    } coord_t;

    typedef struct solve_event_s {
        int x;
        int y;
        char ch;
        int color;
    } solve_event_t;

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
        int stack_depth;
        int show_stats;
        int panel_top;
        int step_mode;
        int step_run;
        int step_finish;
        coord_t *solve_stack;
        int solve_stack_size;
        solve_event_t *history;
        int history_size;
        int history_view;
        int history_cap;
        char **solve_snapshot;
        run_stats_t stats;
        pos_list_t *last_pos;
    }param_t;
#endif
