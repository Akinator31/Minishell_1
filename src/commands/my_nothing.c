/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** nothing
*/

#include <stdbool.h>
#include <unistd.h>
#include "mysh.h"
#include "commands.h"
#include "my_lib.h"
#include "utils.h"

bool is_nothing(char *command, bool is_tty, char **envp)
{
    if (my_strlen(command) == 1) {
        if (!is_tty)
            print_prompt(envp);
        return true;
    }
    return false;
}
