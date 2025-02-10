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

int analyse_command(char ***evnp, char *command, bool is_tty)
{
    if (is_exit_command(command))
        return EXIT;
    if (is_nothing(command, is_tty))
        return NOTHING;
    if (is_setenv_command(evnp, command) ||
        is_unsetenv_command(evnp, command) ||
        is_env_command(evnp, command)) {
        if (!is_tty)
            write(1, prompt, 3);
        return NORMAL;
    }
    if (!is_tty)
        write(1, prompt, 3);
    return NORMAL;
}
