/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** is_good_command
*/

#include <stdbool.h>
#include "mysh.h"
#include "my_lib.h"

bool is_good_cmd(char *cmd, char *prompt)
{
    char **prompt_elt = my_str_to_word_array(prompt, " ");
    int is_correct_cmd = my_strcmp(cmd, prompt_elt[0]);

    if (is_correct_cmd == IS_A_TTY_OFFSET ||
        is_correct_cmd == IS_NOT_A_TTY_OFFSET) {
        free_2d_array_of_char(prompt_elt);
        return true;
    }
    free_2d_array_of_char(prompt_elt);
    return false;
}
