 #include "../libft/libft.h"
#include "args_state_machine.h"

t_state	in_space_h(char new_char, char prev_char, char *quote_char)
{
	(void)prev_char;
	if (ft_isspace(new_char))
		return (in_space);
	else
	{
		if (new_char == '"' || new_char == '\'')
		{
			*quote_char = new_char;
			return (in_quote);
		}
		else
			return (in_word);
	}
}

t_state	in_word_h(char new_char, char prev_char, char *quote_char)
{
	if (ft_isspace(new_char))
		return (in_space);
	else if ((new_char == '"' || new_char == '\'') && prev_char != '\\')
	{
		*quote_char = new_char;
		return (in_quote_in_word);
	}
	return (in_word);
}

t_state	in_quote_h(char new_char, char prev_char, char *quote_char)
{
	if (ft_isspace(new_char) && prev_char == *quote_char)
		return (in_space);
	if (new_char == *quote_char && prev_char == '\\')
		return (in_escaped_quote);
	return (in_quote);
}

t_state	in_quote_w_h(char new_char, char prev_char, char *quote_char)
{
	if (new_char == *quote_char && prev_char != '\\')
		return (in_word);
	return (in_quote_in_word);
}

t_state	in_esc_quote_h(char new_char, char prev_char, char *quote_char)
{
	(void)new_char;
	(void)prev_char;
	(void)quote_char;
	return (in_quote);
}