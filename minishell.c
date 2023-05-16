/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:54:34 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/16 16:47:21 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*struc(void)
{
	static t_data	data;

	return (&data);
}

void	exec(char *cmd)
{
	char	**fcmd;

	fcmd = ft_split(cmd, 32);
	struc()->path = findpath(struc());
	find_executable(fcmd, 0);
	if (execve(struc()->cmdpath, fcmd, struc()->envp) == -1)
	{
		if (execve(fcmd[0], fcmd, struc()->envp) == -1)
		{
			perror(fcmd[0]);
			exit (0);
		}
	}
}

void	run_cmd(char *cmd)
{
	int		status;

	struc()->pid[0] = fork();
	struc()->is_child = 1;
	if (struc()->pid[0] == -1)
		return ;
	if (!struc()->pid[0])
	{
		exec(cmd);
	}
	waitpid(struc()->pid[0], &status, 0);
}

void	initialize(char **envp)
{
	pid_t	*temp;

	struc()->envp = envp;
	temp = ft_calloc(2, sizeof(pid_t *));
	struc()->pid = temp;
	struc()->is_child = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd;

	(void)argc;
	(void)argv;
	if (signal_handler())
		exit(1);
	ft_printf("NEW_PROCESS\n");
	initialize(envp);
	while (1)
	{
		struc()->is_child = 0;
		struc()->input = readline("minishell> ");
		if (!struc()->input)
		{
			ft_putendl_fd("EXIT", 1);
			break ;
		}
		cmd = ft_split(struc()->input, 32);
		if (!ft_strncmp(cmd[0], "cd", 2))
			chdir(cmd[1]);
		else
			run_cmd(struc()->input);
		add_history(struc()->input);
	}
	rl_clear_history();
	return (0);
}
