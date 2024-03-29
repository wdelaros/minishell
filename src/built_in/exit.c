/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:34:32 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/20 14:08:10 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_in.h"

static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == 43 || str[i] == 45)
		i++;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

static int	free_and_exit(char **cmd, t_cmd *lcmd, char ***to_free, int fd_out)
{
	int	exitnum;

	exitnum = ft_atoi(cmd[1]);
	close(fd_out);
	free(struc()->current_pwd);
	ft_free_null(struc()->envp);
	ft_free_null(struc()->export);
	ft_free_all_pipe(lcmd, to_free);
	return (exitnum);
}

void	ft_exit(char **cmd, t_cmd *lcmd, char ***to_free, int fd_out)
{
	if (struc()->pipenum == 0)
		ft_printf("exit\n");
	if (!cmd[1])
	{
		free_and_exit(cmd, lcmd, to_free, fd_out);
		exit (struc()->exit_code);
	}
	else if (!ft_isnumber(cmd[1]))
	{
		ft_dprintf(2, "%s exit: %s: numeric argument required\n", \
		MINI, cmd[1]);
		free_and_exit(cmd, lcmd, to_free, fd_out);
		exit (255);
	}
	else if (cmd[2])
	{
		ft_dprintf(2, "%s exit: too many arguments\n", MINI);
		struc()->exit_code = 1;
		return ;
	}
	else
		exit (free_and_exit(cmd, lcmd, to_free, fd_out));
}
