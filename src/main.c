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

int mysh_tty(bool *environ_modified)
{
    printf("%s\n", getcwd(NULL, 0));
}

int mysh(bool *environ_modified)
{
    int result_command = 0;
    char *buffer = NULL;
    size_t len = 0;

    write(1, prompt, 4);
    while (getline(&buffer, &len, stdin) != -1) {
        result_command = analyse_command(buffer, environ_modified);
        if (result_command == EXIT)
            return EXIT;
        if (result_command == NOTHING)
            continue;
    }
    return EXIT_EOF;
}

int main(void)
{
    int mysh_exit_status = 0;
    int mysh_tty_exit_status = 0;
    bool environ_modified = 0;

    if (!isatty(stdin->_fileno))
        mysh_tty_exit_status = mysh_tty(&environ_modified);
    else
        mysh_exit_status = mysh(&environ_modified);
    if (mysh_exit_status == EXIT_EOF)
        write(1, "exit\n", 6);
    if (environ_modified)
        free_environ();
    return 0;
}
