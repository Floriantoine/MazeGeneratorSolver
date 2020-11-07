/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** toolbox
*/

#include <unistd.h>
#include "maze.h"

int my_strlen(char const *str)
{
    int i = 0;

    if (str) {
        while (str[i])
            ++i;
    }
    return (i);
}

void err_putchar(char c)
{
    write(2, &c, 1);
}

int put_err(char const *str)
{
    int i = 0;

    if (str) {
        while (str[i]) {
            err_putchar(str[i]);
            ++i;
        }
    }
    return (0);
}



