/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:21:33 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/18 08:47:30 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (NULL);
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

void	find_executable(char	**fcmd, int i)
{
	char	*tmp;

	if (!access(fcmd[0], F_OK))
	{
		struc()->cmdpath = fcmd[0];
		return ;
	}
	if (struc()->path)
	{
		while (struc()->path[i])
		{
			tmp = ft_rstrjoin(fcmd[0], struc()->path[i]);
			struc()->cmdpath = ft_strdup(tmp);
			free(tmp);
			if (!access(struc()->cmdpath, F_OK))
				return ;
			free(struc()->cmdpath);
			i++;
		}
	}
	struc()->cmdpath = NULL;
}