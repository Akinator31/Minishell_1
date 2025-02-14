/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** my_exec
*/

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "mysh.h"
#include "my_lib.h"
#include "utils.h"

void launch_binary(char ***envp, char *binary_path, char **command_element)
{
    pid_t pid = fork();
    int exec_return = 0;
    int status = 0;

    if (pid == 0) {
        exec_return = execve(binary_path, command_element, *envp);
        if (exec_return != -1)
            exit(exec_return);
    } else {
        free_2d_array_of_char(command_element);
        waitpid(pid, &status, 0);
    }
    return;
}

void launch_file(char ***envp, char **command_element)
{
    pid_t pid = fork();
    int exec_return = 0;
    int status = 0;

    if (pid == 0) {
        exec_return = execve(command_element[0], command_element, *envp);
        free_2d_array_of_char(command_element);
        if (exec_return != -1)
            exit(exec_return);
    } else {
        free_2d_array_of_char(command_element);
        waitpid(pid, &status, 0);
    }
    return;
}

void my_exec(char ***envp, char *command, bool is_tty, exit_status_t *status)
{
    char **command_element = my_str_to_word_array(command, " ");
    char *binary_path = NULL;

    if (command_element[0][0] == '.') {
        launch_file(envp, command_element);
    } else {
        binary_path = get_binary(envp, command);
        launch_binary(envp, binary_path, command_element);
        free(binary_path);
    }
}
