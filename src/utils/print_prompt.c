/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** get_prompt
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include "my_lib.h"
#include <stdio.h>
#include <fcntl.h>

void print_hostname(void)
{
    int hostname_file = open("/etc/hostname", O_RDONLY);
    char hostname[254];
    ssize_t hostname_len = 0;

    if (!hostname_file)
        return;
    hostname_len = read(hostname_file, hostname, 253);
    write(1, hostname, hostname_len - 1);
    close(hostname_file);
}

void print_prompt(char **envp)
{
    char *home = get_environ_variable_value(&envp, "HOME");
    char *current_dir = get_environ_variable_value(&envp, "PWD");

    if (my_strstr(current_dir, home) != NULL) {
        print_hostname();
        write(1, ":~", 3);
        write(1, current_dir + my_strlen(home),
            my_strlen(current_dir + my_strlen(home)));
        write(1, "> ", 2);
    } else {
        print_hostname();
        write(1, ":", 2);
        write(1, current_dir, my_strlen(current_dir));
        write(1, "> ", 2);
    }
    free(home);
    free(current_dir);
}
