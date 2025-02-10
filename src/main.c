/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** main
*/

#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "my_lib.h"
#include "mysh.h"
#include "utils.h"

int mysh_tty(char ***envp)
{
    int result_command = 0;
    char *buffer = NULL;
    size_t len = 0;

    while (getline(&buffer, &len, stdin) != -1) {
        result_command = analyse_command(envp, buffer, 1);
        if (result_command == EXIT)
            return EXIT;
        if (result_command == NOTHING)
            continue;
    }
    return EXIT_EOF;
}

int mysh(char ***envp)
{
    int result_command = 0;
    char *buffer = NULL;
    size_t len = 0;

    write(1, prompt, 4);
    while (getline(&buffer, &len, stdin) != -1) {
        result_command = analyse_command(envp, buffer, 0);
        if (result_command == EXIT)
            return EXIT;
        if (result_command == NOTHING)
            continue;
    }
    return EXIT_EOF;
}

int main(int ac, char **av, char **envp)
{
    int mysh_exit_status = 0;
    int mysh_tty_exit_status = 0;
    char **env = NULL;

    env = duplicate_2d_char_array(envp, get_2d_arr_len(envp) + 1);
    if (!isatty(stdin->_fileno))
        mysh_tty_exit_status = mysh_tty(&env);
    else
        mysh_exit_status = mysh(&env);
    if (mysh_exit_status == EXIT_EOF)
        write(1, "exit\n", 6);
    free_2d_array_of_char(env);
    return 0;
}
