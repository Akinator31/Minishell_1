/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** change_directory
*/

#include <unistd.h>
#include <stdio.h>
#include "utils.h"

int change_dir(char *path_to_directory, char *current_directory,
    char *old_directory, int *error_code)
{
    if (chdir(path_to_directory) == -1) {
        perror(path_to_directory);
        my_free(current_directory, old_directory, NULL);
        *error_code = 84;
        return 1;
    }
    return 0;
}

int change_directory_to_env(char *variable)
{
    if (chdir(variable) == -1) {
        perror(variable);
        my_free(variable, NULL);
        return 1;
    }
    return 0;
}
