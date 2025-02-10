/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** utils
*/

#ifndef INCLUDED_UTILS_H
    #define INCLUDED_UTILS_H
    #include <stdbool.h>

bool is_good_cmd(char *cmd, char *prompt);
char *get_environ_var(const char *name, const char *value);
void free_environ(void);
void env(void);

#endif
