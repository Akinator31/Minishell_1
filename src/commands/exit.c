/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** exit
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <mysh.h>
#include "my_lib.h"
#include "utils.h"

bool is_exit_command(char *command)
{
    if (my_strlen(command) <= 1)
        return false;
    if (is_good_cmd("exit", command)) {
        write(1, "exit\n", 5);
        free(command);
        return true;
    }
    return false;
}
