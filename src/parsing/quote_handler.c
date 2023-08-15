#include "../../include/parsing.h"

// static int	double_quote_handler(char **res, char **input, size_t *i, size_t *j)
// {
// 	char	*double_input;
// 	char	*double_res;
// 	size_t	double_i;
// 	size_t	double_j;
// 	int		var;

// 	double_input = *input;
// 	double_res = *res;
// 	double_i = *i;
// 	double_j = *j;
// 	var = NO;
// 	while (double_input[double_i] && double_input[double_i] != DOUBLE_QUOTE)
// 	{
// 		if (double_input[double_i] == '$')
// 			var = YES;
// 		double_res[double_j] = double_input[double_i];
// 		double_i++;
// 		double_j++;
// 	}
// 	*i = double_i;
// 	*j = double_j;
// 	return (var);
// }

static int	quote_size(char *input)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == DOUBLE_QUOTE || input[i] == SINGLE_QUOTE)
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
			{
				i++;
				count++;
			}
		}
		else
			count++;
		i++;
	}
	return (count);
}

static char	*quote_interpreter(char *input)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_calloc(quote_size(input), sizeof(char));
	while (input[i])
	{
		if (input[i] == SINGLE_QUOTE)
		{
			i++;
			while (input[i] && input[i] != SINGLE_QUOTE)
				res[j++] = input[i++];
		}
		else if (input[i] == DOUBLE_QUOTE)
		{
			i++;
			while (input[i] && input[i] != DOUBLE_QUOTE)
				res[j++] = input[i++];
		}
		else
			res[j++] = input[i];
		i++;
	}
	return (res);
}

static int	is_quote(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == DOUBLE_QUOTE || input[i] == SINGLE_QUOTE)
			return (YES);
		i++;
	}
	return (NO);
}

void	quote_handler(t_input **input)
{
	t_input	*temp;

	temp = *input;
	while (temp->next)
	{
		if (is_quote(temp->input) == YES)
			temp->input = quote_interpreter(temp->input);
		temp = temp->next;
	}
}
