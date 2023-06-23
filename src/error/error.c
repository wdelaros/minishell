#include "../../include/error.h"

// static void	pipe_error(t_err *error_data)
// {

// 	return ;
// }

// static void	red_error(t_err *error_data)
// {

// 	return ;
// }

static void	quote_error(t_err *error_data, int quote)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (error_data->input[i])
	{
		if (error_data->input[i] == quote && flag == 0)
		{
			flag = 1;
			i++;
		}
		if (error_data->input[i] == quote && flag == 1)
		{
			flag = 0;
			i++;
		}
		i++;
	}
	if (flag == 0)
		error_data->error_code = 1;
}

int	error_handler(char *input)
{
	t_err	error_data;

	error_data.error_code = 0;
	error_data.input = ft_strdup(input);
	// pipe_error(&error_data);
	// if (error_data.error_code != 0)
	// 	red_error(&error_data);
	if (error_data.error_code != 0)
		quote_error(&error_data, DOUBLE_QUOTE);
	else if (error_data.error_code != 0)
		quote_error(&error_data, SINGLE_QUOTE);
	ft_xfree(error_data.input);
	return (error_data.error_code);
}
