/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:34:47 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/12 16:39:33 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/error.h"
#include "../../include/parsing.h"

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

static void	red_error(t_err *err, size_t i, size_t red)
{
	(void)red;

	while (i < ft_strlen(err->input))
	{
		if (err->input[i] == DQ || err->input[i] == SQ)
			i = skip_quote(err->input, i, err->input[i]);
		if (i < ft_strlen(err->input) && (err->input[i] == RD_I
				|| err->input[i] == RD_O))
		{
			if (i == ft_strlen(err->input) - 1)
				err->error_code = 2;
		}
		if (i < ft_strlen(err->input))
			i++;
	}
}

static void	quote_error(t_err *error_data, int i, int flag)
{
	while (error_data->input[i])
	{
		if (error_data->input[i] == DQ)
		{
			flag = 1;
			i++;
			while (error_data->input[i] && error_data->input[i] != DQ)
				i++;
			if (error_data->input[i] == DQ)
				flag = 0;
		}
		if (error_data->input[i] == SQ)
		{
			flag = 1;
			i++;
			while (error_data->input[i] && error_data->input[i] != SQ)
				i++;
			if (error_data->input[i] == SQ)
				flag = 0;
		}
		if (error_data->input[i])
			i++;
	}
	if (flag == 1)
		error_data->error_code = 3;
}

static int	mul_pipe_error(t_err *error_data)
{
	int		i;

	i = 0;
	while (error_data->input[i])
	{
		if (error_data->input[i] == PIPE)
		{
			i++;
			if (error_data->input[i] == PIPE)
				error_data->error_code = 1;
			while (error_data->input[i]
				&& ft_isspace(error_data->input[i]) == YES)
			{
				i++;
				if (error_data->input[i] == PIPE)
					error_data->error_code = 1;
			}
		}
		else if (error_data->input[i] == DQ || error_data->input[i] == SQ)
			i = skip_quote(error_data->input, i, error_data->input[i]) - 1;
		if (error_data->input[i])
			i++;
	}
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
		red_error(&error_data, 0, 0);
	if (error_data.error_code == 0)
		mul_red_error(&error_data, 0);
	if (error_data.error_code == 0)
		mul_pipe_error(&error_data);
	if (error_data.error_code == 0)
		quote_error(&error_data, 0, 0);
	ft_xfree(error_data.input);
	return (error_data.error_code);
}
