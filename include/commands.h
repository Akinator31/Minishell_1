/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** commands
*/

#ifndef INCLUDED_COMMANDS_H
    #define INCLUDED_COMMANDS_H
    #include <stdbool.h>
    #include "mysh.h"

bool is_exit_command(char ***envp, char *command,
    bool is_tty, exit_status_t *status);
bool is_nothing(char ***envp, char *command,
    bool is_tty, exit_status_t *status);
bool is_env_command(char ***envp, char *command,
    bool is_tty, exit_status_t *status);
bool is_setenv_command(char ***envp, char *command,
    bool is_tty, exit_status_t *status);
bool is_unsetenv_command(char ***envp, char *command,
    bool is_tty, exit_status_t *status);
bool is_cd_command(char ***envp, char *command,
    bool is_tty, exit_status_t *status);
bool my_exec(char ***envp, char *command,
    bool is_tty, exit_status_t *status);

#endif
