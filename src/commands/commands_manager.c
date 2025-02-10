/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** commands_manager
*/

#include <unistd.h>
#include "my_lib.h"
#include "commands.h"
#include "mysh.h"

extern char **environ;

int analyse_command(char *command, bool *environ_modified)
{
    if (is_exit_command(command))
        return EXIT;
    if (is_nothing(command))
        return NOTHING;
    if (is_setenv_command(command, environ_modified) ||
        is_unsetenv_command(command, environ_modified) ||
        is_env_command(command)) {
        write(1, prompt, 3);
        return NORMAL;
    }
    write(1, prompt, 3);
    return NORMAL;
}
