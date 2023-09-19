/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:11 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 13:35:12 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

/**
 * find the path for the excutable
*/
char	**findpath(t_data *data)
{
	int		i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (data->envp[i])
		data->path = ft_split(data->envp[i] + 5, ':');
	else
	{
		data->path = ft_split("", ' ');
		return (data->path);
	}
	i = 0;
	while (data->path[i])
	{
		data->path[i] = ft_fstrjoin(data->path[i], "/");
		i++;
	}
	if (!data->path)
		perror("Error");
	return (data->path);
}

/**
 * check if the excutable exist
*/
void	find_executable(char	**fcmd, int i, t_data *data)
{
	if (data->path)
	{
		while (data->path[i])
		{
			data->cmdpath = ft_rstrjoin(fcmd[0], data->path[i]);
			if (!access(data->cmdpath, F_OK))
				break ;
			free(data->cmdpath);
			data->cmdpath = NULL;
			i++;
		}
	}
	if (!access(fcmd[0], F_OK) || (data->cmdpath && \
	!access(data->cmdpath, F_OK)))
	{
		if (!strncmp("./", fcmd[0], 2))
			data->cmdpath = ft_strdup(fcmd[0]);
		else if (!strncmp("/", fcmd[0], 1))
			data->cmdpath = ft_strdup(fcmd[0]);
		if (data->cmdpath && !access(data->cmdpath, F_OK))
			return ;
	}
	data->cmdpath = ft_strdup("");
}
