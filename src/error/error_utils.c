/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:34:44 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/12 07:46:28 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/error.h"

static void	if_red(t_err *error_data, int i)
{
	if (error_data->input[i] == RD_I && (error_data->input[i + 1]
			&& error_data->input[i + 1] == RD_I))
		error_data->error_code = 6;
	else if (error_data->input[i] == RD_O && (error_data->input[i + 1]
			&& error_data->input[i + 1] == RD_O))
		error_data->error_code = 7;
	else if (error_data->input[i] == RD_I)
		error_data->error_code = 4;
	else if (error_data->input[i] == RD_O)
		error_data->error_code = 5;
	else if (!error_data->input[i])
		error_data->error_code = 2;
	else if (error_data->input[i] == PIPE)
		error_data->error_code = 1;
}

void	mul_red_error(t_err *err, int i)
{
	while (err->input[i] && err->error_code == 0)
	{
		if (err->input[i] == RD_I || err->input[i] == RD_O)
		{
			if ((err->input[i] == RD_I || err->input[i] == RD_O)
				&& err->input[i + 1] && err->input[i + 2] 
				&& (err->input[i + 2] == RD_I
					|| err->input[i + 2] == RD_O))
			{
				if_red(err, i + 2);
				return ;
			}
			else
			{
				while (err->input[i] == '>'
					|| err->input[i] == '<')
					i++;
				while (ft_isspace(err->input[i]) == YES)
					i++;
			}
			if_red(err, i);
		}
		if (err->input[i])
			i++;
	}
}
