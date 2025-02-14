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
#include <signal.h>
#include "my_lib.h"
#include "mysh.h"
#include "utils.h"

int mysh(char ***envp, int is_tty)
{
    int result_command = 0;
    char *buffer = NULL;
    size_t len = 0;

    if (!is_tty)
        print_prompt(*envp);
    while (getline(&buffer, &len, stdin) != -1) {
        result_command = analyse_command(envp, buffer, is_tty);
        if (result_command == EXIT) {
            free(buffer);
            return EXIT;
        }
        if (result_command == NORMAL && !is_tty)
            print_prompt(*envp);
        if (result_command == NOTHING)
            continue;
    }
    free(buffer);
    return EXIT_EOF;
}

int main(int ac, char **av, char **envp)
{
    int mysh_exit_status = 0;
    int mysh_tty_exit_status = 0;
    char **env = NULL;

    env = duplicate_2d_char_array(envp, get_2d_arr_len(envp) + 1);
    if (!isatty(stdin->_fileno))
        mysh_tty_exit_status = mysh(&env, 1);
    else
        mysh_exit_status = mysh(&env, 0);
    if (mysh_exit_status == EXIT_EOF)
        write(1, "exit\n", 6);
    free_2d_array_of_char(env);
    return 0;
}
