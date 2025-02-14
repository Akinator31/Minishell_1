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

typedef enum {
    NORMAL,
    EXIT,
    EXIT_EOF,
    NOTHING,
} exit_status_t;

typedef struct {
    char *builtins_name;
    bool (*f)(char ***, char *, bool, exit_status_t *);
} my_builtins_t;

exit_status_t analyse_command(char ***evnp, char *command,
    bool is_tty, int *error_code);

#endif
