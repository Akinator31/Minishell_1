/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** my_exec
*/

#define _GNU_SOURCE
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include "mysh.h"
#include "my_lib.h"
#include "utils.h"

void exit_manager(int status, pid_t pid, int *error_code)
{
    if (!WIFEXITED(status)) {
        *error_code = WTERMSIG(status);
        my_putstr(strsignal(WTERMSIG(status)), 2);
        write(2, "\n", 1);
        return;
    }
    *error_code = WEXITSTATUS(status);
    kill(pid, 0);
}

void launch_binary(char ***envp, char *binary_path,
    char **command_element, int *error_code)
{
    pid_t pid = fork();
    int exec_return = 0;
    int status = 0;

    if (pid == 0) {
        exec_return = execve(binary_path, command_element, *envp);
        if (exec_return != 0) {
            perror(binary_path);
            free_2d_array_of_char(command_element);
            exit(exec_return);
        }
        free_2d_array_of_char(command_element);
    } else {
        free_2d_array_of_char(command_element);
        waitpid(pid, &status, 0);
        exit_manager(status, pid, error_code);
    }
    return;
}

void launch_file(char ***envp, char **command_element, int *error_code)
{
    pid_t pid = fork();
    int exec_return = 0;
    int status = 0;

    if (pid == 0) {
        exec_return = execve(command_element[0], command_element, *envp);
        if (exec_return != 0) {
            perror(command_element[0]);
            free_2d_array_of_char(command_element);
            exit(exec_return);
        }
        free_2d_array_of_char(command_element);
    } else {
        free_2d_array_of_char(command_element);
        waitpid(pid, &status, 0);
        exit_manager(status, pid, error_code);
    }
    return;
}

void my_exec(char ***envp, char *command,
    exit_status_t *status, int *error_code)
{
    char **command_element = my_str_to_word_array(command, " ");
    char *binary_path = get_binary(envp, command);

    if (command_element[0][0] == '.' || command_element[0][0] == '/') {
        launch_file(envp, command_element, error_code);
    } else if (!binary_path) {
        write(2, command_element[0], my_strlen(command_element[0]));
        write(2, ": Command not found.\n", 21);
        free_2d_array_of_char(command_element);
        *error_code = 1;
        return;
    } else {
        launch_binary(envp, binary_path, command_element, error_code);
    }
    free(binary_path);
}
