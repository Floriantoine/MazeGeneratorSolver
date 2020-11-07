/*
** EPITECH PROJECT, 2018
** CPE_dante_2018
** File description:
** randy.c
*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int randy(int min, int max, int nop) {
    int out_rand = nop;

    while (out_rand < min || out_rand > max || out_rand == nop) {
        out_rand = rand() % (max - min) + min;
    }
    return (out_rand);
}
