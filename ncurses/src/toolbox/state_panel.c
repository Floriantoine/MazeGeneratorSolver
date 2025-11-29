/*
** EPITECH PROJECT, 2024
** state_panel.c
** File description:
** Runtime stats display
*/

#include "toolbox.h"
#include "param.h"
#include <ncurses.h>
#include <string.h>

static void clamp_coords(int *y, int *x)
{
    if (*y < 0)
        *y = 0;
    if (*x < 0)
        *x = 0;
}

void reset_stats(param_t *param)
{
    memset(&param->stats, 0, sizeof(run_stats_t));
    param->stack_depth = 1;
    param->solve_stack_size = 0;
    param->step_finish = 0;
    param->history_size = 0;
    param->history_view = 0;
}

void print_state(param_t *param)
{
    int map_row = (param->window_x - param->size_x) / 2;
    int map_col = (param->window_y - param->size_y) / 2;
    int start_row = map_row;
    int start_col = map_col + param->size_y + 2;
    int need_width = 22;
    int space_right = param->window_y - (start_col + need_width);
    int line = 0;

    if (!param->show_stats)
        return;
    if (space_right < 0)
        start_col = param->window_y - need_width;
    if (start_col + need_width > param->window_y)
        start_col = param->window_y - need_width;
    clamp_coords(&start_row, &start_col);
    attron(COLOR_PAIR(7));
    mvprintw(start_row + line++, start_col, "=== STATE ===");
    mvprintw(start_row + line++, start_col, "Seed: %u", param->stats.seed);
    mvprintw(start_row + line++, start_col, "Size: %dx%d",
        param->size_x, param->size_y);
    mvprintw(start_row + line++, start_col, "Gen steps: %lu",
        param->stats.gen_steps);
    mvprintw(start_row + line++, start_col, "Gen backtracks: %lu",
        param->stats.gen_backtracks);
    mvprintw(start_row + line++, start_col, "Depth max: %d",
        param->stats.depth_max);
    mvprintw(start_row + line++, start_col, "Solve steps: %lu",
        param->stats.solve_steps);
    mvprintw(start_row + line++, start_col, "Solve backtracks: %lu",
        param->stats.solve_backtracks);
    mvprintw(start_row + line++, start_col, "Gen time: %ld ms",
        param->stats.gen_ms);
    mvprintw(start_row + line++, start_col, "Solve time: %ld ms",
        param->stats.solve_ms);
    mvprintw(start_row + line++, start_col, "Stack depth: %d",
        param->solve_stack_size);
    mvprintw(start_row + line++, start_col, "History: %d/%d",
        param->history_view, param->history_size);
    if (param->solve_stack && param->solve_stack_size > 0) {
        int from = param->solve_stack_size - 5;
        if (from < 0)
            from = 0;
        for (int i = from; i < param->solve_stack_size; ++i) {
            mvprintw(start_row + line++, start_col, "#%d (%d,%d)",
                i + 1, param->solve_stack[i].y, param->solve_stack[i].x);
        }
    }
    attroff(COLOR_PAIR(7));
}

void wait_step(param_t *param)
{
    int ch = 0;

    if (!param->step_mode)
        return;
    if (param->step_run) {
        nodelay(stdscr, TRUE);
        ch = getch();
        if (ch == 'c' || ch == 'C')
            param->step_run = 0;
        if (ch == 'h' || ch == 'H')
            param->show_stats = !param->show_stats;
        nodelay(stdscr, FALSE);
        return;
    }
    mvprintw(param->window_x - 1, 1,
        "Step mode: space/n=next, b=back, c=run/stop, f=finish, h=hide");
    refresh();
    while (1) {
        ch = getch();
        if (ch == ' ' || ch == 'n' || ch == 'N' || ch == '\n')
            break;
        if (ch == 'c' || ch == 'C') {
            param->step_run = 1;
            break;
        }
        if (ch == 'h' || ch == 'H') {
            param->show_stats = !param->show_stats;
            render_history_view(param, param->history_view);
            continue;
        }
        if (ch == 'f' || ch == 'F') {
            param->step_run = 1;
            param->step_mode = 0;
            param->step_finish = 1;
            break;
        }
        if (ch == 'b' || ch == 'B') {
            if (param->history_view > 1) {
                param->history_view -= 1;
                render_history_view(param, param->history_view);
            }
            continue;
        }
    }
    if (param->history_view != param->history_size)
        render_history_view(param, param->history_size);
    param->history_view = param->history_size;
}
