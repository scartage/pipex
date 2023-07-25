#ifndef ARGS_STATE_MACHINE_H
# define ARGS_STATE_MACHINE_H

typedef enum e_state
{
	in_space,
	in_word,
	in_quote,
	in_quote_in_word,
	in_escaped_quote
}	t_state;

typedef t_state	(*t_handler)(char new_char, char old_char, char *quote_char);

t_state	in_space_h(char new_char, char prev_char, char *quote_char);
t_state	in_word_h(char new_char, char prev_char, char *quote_char);
t_state	in_quote_h(char new_char, char prev_char, char *quote_char);
t_state	in_quote_w_h(char new_char, char prev_char, char *quote_char);
t_state	in_esc_quote_h(char new_char, char prev_char, char *quote_char);
#endif