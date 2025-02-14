/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** cd
*/

#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "mysh.h"
#include "my_lib.h"
#include "utils.h"
#include "commands.h"

static int cd_to_old_directory(char ***envp)
{
    char *current_directory = get_environ_variable_value(envp, "PWD");
    char *old_directory = get_environ_variable_value(envp, "OLDPWD");

    if (!old_directory || !current_directory) {
        write(2, ": No such file or folder.\n", 27);
        free(old_directory);
        free(current_directory);
        return 0;
    } else {
        if (chdir(old_directory) == -1) {
            perror(old_directory);
            return 0;
        }
        my_setenv(envp, "OLDPWD", current_directory, 1);
        my_setenv(envp, "PWD", old_directory, 1);
    }
    free(old_directory);
    free(current_directory);
    return 1;
}

static int cd_to_home_directory(char ***envp)
{
    char *home_directory = get_environ_variable_value(envp, "HOME");
    char *current_directory = get_environ_variable_value(envp, "PWD");
    char *old_directory = get_environ_variable_value(envp, "OLDPWD");

    if (!current_directory || !home_directory) {
        write(2, ": No such file or folder.\n", 27);
        my_free(current_directory, old_directory, NULL);
        return 0;
    } else {
        if (chdir(home_directory) == -1) {
            perror(home_directory);
            my_free(home_directory, current_directory, old_directory, NULL);
            return 0;
        }
        my_setenv(envp, "OLDPWD", current_directory, 1);
        my_setenv(envp, "PWD", home_directory, 1);
        my_free(home_directory, current_directory, old_directory, NULL);
    }
    return 1;
}

static int cd_to_directory(char ***envp, char *path_to_directory)
{
    char *current_directory = get_environ_variable_value(envp, "PWD");
    char *old_directory = get_environ_variable_value(envp, "OLDPWD");
    char *directory = NULL;

    if (!current_directory) {
        my_free(current_directory, old_directory, directory, NULL);
        return write(2, "PWD variable not found\n", 24);
    } else {
        if (chdir(path_to_directory) == -1) {
            perror(path_to_directory);
            my_free(current_directory, old_directory, NULL);
            return 0;
        }
        directory = getcwd(NULL, 0);
        my_setenv(envp, "OLDPWD", current_directory, 1);
        my_setenv(envp, "PWD", directory, 1);
        free(directory);
        my_free(current_directory, old_directory, NULL);
    }
    return 1;
}

static int cd_to_env_directory(char ***envp, char **command_element)
{
    char *current_directory = get_environ_variable_value(envp, "PWD");
    char *variable = get_environ_variable_value(envp, command_element[1] + 1);
    char *old_directory = get_environ_variable_value(envp, "OLDPWD");
    char *directory = NULL;

    if (!variable) {
        write(2, command_element[1] + 1, my_strlen(command_element[1] + 1));
        return write(2, ": Variable undefined.\n", 23);
    } else {
        if (chdir(variable) == -1) {
            perror(variable);
            my_free(variable, NULL);
            return 0;
        }
        directory = getcwd(NULL, 0);
        my_setenv(envp, "OLDPWD", current_directory, 1);
        my_setenv(envp, "PWD", directory, 1);
        free(directory);
        my_free(current_directory, old_directory, NULL);
    }
}

static int my_cd(char ***envp, char *command)
{
    char **command_element = my_str_to_word_array(command, " ");

    if (get_2d_arr_len(command_element) == 1) {
        free_2d_array_of_char(command_element);
        return cd_to_home_directory(envp);
    }
    if (my_strcmp(command_element[1], "-") == 0) {
        free_2d_array_of_char(command_element);
        return cd_to_old_directory(envp);
    }
    if (my_strcmp(command_element[1], "~") == 0) {
        free_2d_array_of_char(command_element);
        return cd_to_home_directory(envp);
    }
    if (command_element[1][0] == '$')
        return cd_to_env_directory(envp, command_element);
    cd_to_directory(envp, command_element[1]);
    free_2d_array_of_char(command_element);
}

bool is_cd_command(char ***envp, char *command,
    bool is_tty, exit_status_t *status)
{
    if (is_good_cmd("cd", command)) {
        my_cd(envp, command);
        *status = NORMAL;
        return true;
    }
    return false;
}
