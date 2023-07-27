#include "arguments.h"
#include "args_state_machine.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>


static t_state state_handler(t_state next_state, char new_char)
{
    static char prev_char;
    static char quote_char;
    t_handler   *handlers;

    handlers = (t_handler[5])
    {
        in_space_h,
        in_word_h,
        in_quote_h,
        in_quote_w_h,
        in_esc_quote_h,
    };
    next_state = handlers[next_state](new_char, prev_char, &quote_char);
    prev_char = new_char;
    return (next_state);
}

static int get_number_args(char *com)
{
    t_state next_state;
    t_state prev_state;
    char new_char;
    int n_args;

    next_state = in_space;
    n_args = 0;
    while(*com)
    {
        new_char = *(com++);
        prev_state = next_state;
        next_state = state_handler(next_state, new_char);
        if (prev_state == in_space && next_state != in_space)
            n_args++;
    }
    return (n_args);
}

char ** get_argument_array(char *com)
{
    t_state next_state;
    t_state prev_state;

    char **result;
    int i;
    int w_start;

    printf("%s\n", com);
    int n_args = get_number_args(com);
    printf("%d\n", n_args);
    result = protected_calloc(n_args + 1, sizeof(char *));
    next_state = in_space;
    i = 0;
    while(com[i])
    {
        prev_state = next_state;
        next_state = state_handler(next_state, com[i]);
        if (prev_state == in_space && next_state != in_space)
            w_start = i;
        if (prev_state != in_space && next_state == in_space)
            add_to_result(result, ft_substr(com, w_start, i - w_start));
        i++;
    }
    if (next_state != in_space)
        add_to_result(result, ft_substr(com, w_start, i - w_start));
    add_to_result(result, NULL);
    return (result);
}