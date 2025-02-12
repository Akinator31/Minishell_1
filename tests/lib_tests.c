/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** lib_tests
*/

#include <criterion/criterion.h>
#include "my_lib.h"

Test(my_strcmp, basic_my_strcmpt_test)
{
    cr_assert_eq(my_strcmp("super_string", "super_string"), 0);
}
