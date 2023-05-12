/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:54:34 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/12 08:52:38 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	pid_t	pid;
	int		status;
	char	*input;
	char	**cmd;

	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		cmd = ft_split(input, 32);
		if (!ft_strncmp(cmd[0], "cd", 2))
			chdir(cmd[1]);
		if (!ft_strncmp(cmd[0], "ls", 2))
		{
			pid = fork();
			if (!pid)
				execve("/bin/ls", cmd, envp);
			waitpid(pid, &status, 0);
		}
		add_history(input);
	}
	rl_clear_history();
	return (0);
}
