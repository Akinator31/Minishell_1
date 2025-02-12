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

void env(char **envp)
{
    int i = 0;

    while (envp[i + 1]) {
        write(1, envp[i], my_strlen(envp[i]));
        write(1, "\n", 1);
        i++;
    }
    write(1, envp[i], my_strlen(envp[i]));
    write(1, "\n", 1);
}

bool is_env_command(char ***envp, char *command)
{
    if (is_good_cmd("env", command)) {
        env(*envp);
        return true;
    }
    return false;
}
