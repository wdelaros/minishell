/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:34:44 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 14:25:46 by wdelaros         ###   ########.fr       */
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
}

int	mul_red_error(t_err *error_data, int i)
{
	while (error_data->input[i] && error_data->error_code == 0)
	{
		if (error_data->input[i] == RD_I || error_data->input[i] == RD_O)
		{
			if ((error_data->input[i] == RD_I || error_data->input[i] == RD_O)
				&& error_data->input[i + 2] && (error_data->input[i + 2] == RD_I
					|| error_data->input[i + 2] == RD_O))
			{
				if_red(error_data, i + 2);
				return (error_data->error_code);
			}
			else
			{
				while (error_data->input[i] == '>'
					|| error_data->input[i] == '<')
					i++;
				while (ft_isspace(error_data->input[i]) == YES)
					i++;
			}
			if_red(error_data, i);
		}
		if (error_data->input[i])
			i++;
	}
	return (error_data->error_code);
}
