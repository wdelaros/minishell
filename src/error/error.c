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
	printf("EST CE QUE J'AI UNE ERREUR DE PIPE?\n");
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
	printf("EST CE QUE J'AI UNE ERREUR DE REDIRECTION?\n");
}

static void	quote_error(t_err *error_data)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (error_data->input[i])
	{
		if (error_data->input[i] == DOUBLE_QUOTE)
		{
			flag = 1;
			i++;
			while (error_data->input[i] && error_data->input[i] != DOUBLE_QUOTE)
				i++;
			if (error_data->input[i] == DOUBLE_QUOTE)
				flag = 0;
		}
		if (error_data->input[i] == SINGLE_QUOTE)
		{
			flag = 1;
			i++;
			while (error_data->input[i] && error_data->input[i] != SINGLE_QUOTE)
				i++;
			if (error_data->input[i] == SINGLE_QUOTE)
				flag = 0;
		}
		i++;
	}
	if (flag == 1)
		error_data->error_code = 3;
	printf("EST CE QUE J'AI UNE ERREUR DE QUOTE?\n");
}

static int	mul_pipe_error(t_err *error_data)
{
	int	i;

	i = 0;
	while (error_data->input[i])
	{
		if (error_data->input[i] == PIPE)
		{
			i++;
			if (error_data->input[i] == PIPE)
				error_data->error_code = 258;
			while (error_data->input[i]
				&& ft_isspace(error_data->input[i]) == YES)
			{
				i++;
				if (error_data->input[i] == PIPE)
					error_data->error_code = 258;
			}
		}
		i++;
	}
	printf ("EST CE QUE J'AI UNE ERREUR DE MULTIPLE PIPE?\n");
	return (error_data->error_code);
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
		mul_pipe_error(&error_data);
	if (error_data.error_code == 0)
		red_error(&error_data);
	if (error_data.error_code == 0)
		quote_error(&error_data);
	ft_xfree(error_data.input);
	if (error_data.error_code != 0)
		printf ("OUI!\n");
	else
		printf ("PAS D'ERREUR!\n");
	return (error_data.error_code);
}
