/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** free_if_necessary
*/

#include <stdlib.h>

extern char **environ;

void free_environ(void)
{
    int i = 0;

    while (environ[i]) {
        free(environ[i]);
        i++;
    }
    free(environ);
}
