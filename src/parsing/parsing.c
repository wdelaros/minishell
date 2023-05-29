#include "../../include/parsing.h"

char	**string_handler(char *input)
{
	t_token	token_handler;

	if (if_all_quote_closed(input, DOUBLE_QUOTE) == 0
		|| if_all_quote_closed(input, SINGLE_QUOTE) == 0)
		printf ("MARDE\n");
	token_separator(input, &token_handler);
	return (token_handler.token);
}

int	if_all_quote_closed(char *str, int quote)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == quote && flag == 0) // QUOTE OPEN
		{
			flag = 1;
			i++;
		}
		if (str[i] == quote && flag == 1) // QUOTE CLOSED
		{
			flag = 0;
			i++;
		}
		i++;
	}
	if (flag == 0)
		return (1);
	return (0);
}
