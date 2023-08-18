#include "../../include/parsing.h"

static int	skip_quote(char *input, int i, int quote)
{
	i++;
	if (quote == 1)
		while (input[i] && input[i] != SINGLE_QUOTE)
			i++;
	else if (quote == 2)
		while (input[i] && input[i] != DOUBLE_QUOTE)
			i++;
	return (i);
}

static int	double_quote_condition(char **input, char **env, int i)
{
	int		max_len;
	int		start;

	max_len = skip_quote(*input, i, 2);
	start = i;
	while (i < max_len)
	{
		if ((*input)[i] && (*input)[i] == '$' && i++)
		{
			*input = wagadoo_machine_2(*input, env, i, max_len);
			i = start;
		}
		i++;
	}
	return (skip_quote(*input, start, 2));
}

// static int	normal_condition(char *input, char **env, int i)
// {
// }

void	var_handler(t_input **list, char **env)
{
	t_input	*temp;
	int		i;

	temp = *list;
	while (temp->next)
	{
		i = 0;
		while (temp->input[i])
		{
			if (temp->input[i] == '$')
			{
				;
				// i = normal_condition(temp->input, env, i);
			}
			else if (temp->input[i] == DOUBLE_QUOTE)
				i = double_quote_condition(&temp->input, env, i);
			else if (temp->input[i] == SINGLE_QUOTE)
				i = skip_quote(temp->input, i, 1);
			i++;
		}
		temp = temp->next;
	}
}
