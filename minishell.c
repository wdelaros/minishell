/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:54:34 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/09 07:34:32 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	pid_t	pid;
	char	*input;
	char	**cmd;

	cmd = ft_calloc(2, sizeof(char *));
	cmd[0] = ft_calloc(3, sizeof(char));
	cmd[0] = "ls";
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	while (1)
	{
		input = readline("minishell> ");
		if (!strncmp(input, "cd", 2))
			chdir(input + 3);
		if (!strcmp(input, "ls"))
		{
			pid = fork();
			if (!pid)
				execv("/bin/ls", cmd);
		}
		if (!input)
			break ;
		add_history(input);
	}
	rl_clear_history();
	return (0);
}
