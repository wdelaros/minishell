#include "../../include/error.h"

static void	pipe_error(t_err *error_data)
{
	size_t	i;

	i = 0;
	while (error_data->input[i] && ft_isspace(error_data->input[i]) == YES)
		i++;
	if (error_data->input[i] == PIPE)
		error_data->error_code = 1;
	else
	{
		i = ft_strlen(error_data->input) - 1;
		if (error_data->input[i])
		{
			while (i > 0 && ft_isspace(error_data->input[i]) == YES)
				i--;
			if (error_data->input[i] == PIPE)
				error_data->error_code = 1;
		}
	}
}

static void	red_error(t_err *error_data)
{
	size_t	i;

	i = 0;
	i = ft_strlen(error_data->input) - 1;
	if (error_data->input[i])
	{
		while (i > 0 && ft_isspace(error_data->input[i]) == YES)
			i--;
		if (error_data->input[i] == RED_IN || error_data->input[i] == RED_OUT)
			error_data->error_code = 2;
	}
}

static void	quote_error(t_err *error_data, int quote)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (error_data->input[i])
	{
		if (error_data->input[i] == quote && flag == 0)
			flag = 1;
		else if (error_data->input[i] == quote && flag == 1)
			flag = 0;
		i++;
	}
	if (flag == 0)
		error_data->error_code = 3;
}

int	error_handler(char *input)
{
	t_err	error_data;

	if (input[0] == '\0')
		return (0);
	error_data.error_code = 0;
	error_data.input = ft_strdup(input);
	pipe_error(&error_data);
	if (error_data.error_code == 0)
		red_error(&error_data);
	if (error_data.error_code == 0)
		quote_error(&error_data, DOUBLE_QUOTE);
	if (error_data.error_code == 0)
		quote_error(&error_data, SINGLE_QUOTE);
	ft_xfree(error_data.input);
	return (error_data.error_code);
}
