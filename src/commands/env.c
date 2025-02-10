/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** env
*/

#include <stdbool.h>
#include <unistd.h>
#include "mysh.h"
#include "my_lib.h"
#include "utils.h"

extern char **environ;

void env(void)
{
    int i = 0;

    while (environ[i + 1]) {
        write(1, environ[i], my_strlen(environ[i]));
        write(1, "\n", 1);
        i++;
    }
    write(1, environ[i], my_strlen(environ[i]));
    write(1, "\n", 1);
}

bool is_env_command(char *command)
{
    if (is_good_cmd("env", command)) {
        env();
        return true;
    }
    return false;
}
