/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** mysh
*/

#ifndef INCLUDED_MYSH_H
    #define INCLUDED_MYSH_H
    #include <stdbool.h>
    #define IS_A_TTY_OFFSET -10
    #define IS_NOT_A_TTY_OFFSET 0

static const char *prompt = "$> ";

enum EXIT_STATUS {
    NORMAL,
    EXIT,
    EXIT_EOF,
    NOTHING,
};

int analyse_command(char *command, bool *environ_modified);

#endif
