/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** commands
*/

#ifndef INCLUDED_COMMANDS_H
    #define INCLUDED_COMMANDS_H
    #include <stdbool.h>

bool is_exit_command(char *command);
bool is_nothing(char *command, bool is_tty);
bool is_env_command(char ***envp, char *command);
bool is_setenv_command(char ***envp, char *command);
bool is_unsetenv_command(char ***envp, char *command);

#endif
