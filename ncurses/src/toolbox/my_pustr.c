/*
** EPITECH PROJECT, 2018
** PSU_minishell1_2018
** File description:
** my_putstr.c
*/

#include <unistd.h>

void my_putchar(char c, int nb)
{
    write(nb, &c, 1);
}

int my_putstr( char const *str, int output)
{
    int n = 0;

    while (str[n] != '\0'){
        my_putchar(str[n], output);
        n++;
    }
    return (0);
}
