/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** errno_manager
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "my_lib.h"

void errno_manager(int exec_return, char **command_element)
{
    struct stat file_stat;

    stat(command_element[0], &file_stat);
    if (exec_return != 0 && errno == EACCES && S_ISDIR(file_stat.st_mode)) {
        perror(command_element[0]);
        free_2d_array_of_char(command_element);
        exit(1);
    }
    if (exec_return != 0) {
        write(2, command_element[0], my_strlen(command_element[0]));
        write(2, ": Command not found.\n", 21);
        free_2d_array_of_char(command_element);
        exit(1);
    }
}
