#include "../../include/parsing.h"

static void	quote_eraser(t_quote *qd, char *input, char quote)
{
	qd->i++;
	while (input[qd->i])
	{
		if (input[qd->i] == quote)
			break ;
		qd->res[qd->i_res] = input[qd->i];
		qd->i_res++;
		qd->i++;
	}
}

char	*quote_handler(char *input)
{
	t_quote	quote_data;

	quote_data.i = 0;
	quote_data.res = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	quote_data.i_res = 0;
	while (input[quote_data.i])
	{
		if (input[quote_data.i] == SINGLE_QUOTE)
			quote_eraser(&quote_data, input, SINGLE_QUOTE);
		else if (input[quote_data.i] == DOUBLE_QUOTE)
			quote_eraser(&quote_data, input, DOUBLE_QUOTE);
		else
		{
			quote_data.res[quote_data.i_res] = input[quote_data.i];
			quote_data.i_res++;
		}
		quote_data.i++;
	}
	ft_xfree(input);
	input = ft_strdup(quote_data.res);
	ft_xfree(quote_data.res);
	return (input);
}
