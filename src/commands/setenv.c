/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** setenv
*/

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "my_lib.h"
#include "utils.h"

extern char **environ;

int env_var_already_exist(const char *variable)
{
    char **environ_elements = NULL;

    for (int i = 0; environ[i]; i++) {
        environ_elements = my_str_to_word_array(environ[i]);
        if (my_strcmp(environ_elements[0], variable) == 0) {
            free_2d_array_of_char(environ_elements);
            return i;
        }
        free_2d_array_of_char(environ_elements);
    }
    return -1;
}

int my_setenv(const char *name, const char *value,
    int overwrite, bool *environ_modified)
{
    int environ_size = get_2d_arr_len(environ);
    int variable_index_if_existing = env_var_already_exist(name);
    char **new_environ = NULL;

    if (variable_index_if_existing != -1) {
        if (!overwrite)
            return 0;
        free(environ[variable_index_if_existing]);
        environ[variable_index_if_existing] = get_environ_var(name, value);
        return 0;
    } else {
        new_environ = duplicate_2d_char_array(environ, environ_size + 2);
        if (*environ_modified)
            free_2d_array_of_char(environ);
        new_environ[environ_size] = get_environ_var(name, value);
        environ = new_environ;
        return 0;
    }
}

bool too_many_or_not_enough_args(bool is_correct_cmd, int nb_args,
    char **cmd_args)
{
    if (is_correct_cmd && (nb_args > 3 || nb_args == 1)) {
        if (nb_args > 3)
            write(2, "Too much arguments\n", 20);
        if (nb_args == 1)
            env();
        free_2d_array_of_char(cmd_args);
        return false;
    }
    return true;
}

bool is_setenv_command(char *command, bool *environ_modified)
{
    char **cmd_args = my_str_to_word_array(command);
    bool is_correct_cmd = is_good_cmd("setenv", command);
    int nb_ags = get_2d_arr_len(cmd_args);

    if (!too_many_or_not_enough_args(is_correct_cmd, nb_ags, cmd_args))
        return false;
    if (is_correct_cmd && (nb_ags == 2 || nb_ags == 3)) {
        if (my_setenv(cmd_args[1], cmd_args[2], 1, environ_modified) == -1) {
            write(2, "Not enough space in the environment\n", 37);
            return false;
        }
        *environ_modified = true;
        free_2d_array_of_char(cmd_args);
        return true;
    } else {
        free_2d_array_of_char(cmd_args);
        return false;
    }
}
