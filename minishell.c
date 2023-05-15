/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:54:34 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/15 14:36:14 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char *cmd, t_data *data)
{
	char	**fcmd;
	char	*str;
	int		i;

	i = 0;
	fcmd = ft_split(cmd, 32);
	while (data->path[i])
	{
		data->cmdpath = ft_strjoin(data->path[i], fcmd[0]);
		if (!access(data->cmdpath, F_OK))
			break ;
		if (data->path[i + 1])
			free(data->cmdpath);
		i++;
	}
	if (execve(data->cmdpath, fcmd, data->envp) == -1)
	{
		if (execve(fcmd[0], fcmd, data->envp) == -1)
		{
			free(data->cmdpath);
			str = ft_strdup(fcmd[0]);
			exit (0);
		}
	}
}

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
	if (!data->path)
		perror("Error");
	return (data->path);
}

t_data	init_value(char *envp[])
{
	t_data	data;
	int		i;

	ft_printf("papelipoupi\n");
	data.envp = envp;
	data.path = findpath(&data);
	i = 0;
	while (data.path[i])
	{
		data.path[i] = ft_fstrjoin(data.path[i], "/");
		i++;
	}
	return (data);
}

void	run_cmd(char *cmd, t_data *data)
{
	int		pfd[2];
	int		status;
	pid_t	pid1;

	if (pipe(pfd) == -1)
		return ;
	pid1 = fork();
	if (pid1 == -1)
		return ;
	if (!pid1)
		exec(cmd, data);
	waitpid(pid1, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data				data;
	char				**cmd;
	struct sigaction	init;

	(void)argc;
	(void)argv;
	init.sa_flags = SA_SIGINFO;
	init.sa_sigaction = signal_handler;
	data = init_value(envp);
	sigaction(SIGINT, &init, NULL);
	sigaction(SIGQUIT, &init, NULL);
	while (1)
	{
		data.input = readline("minishell> ");
		if (!data.input)
		{
			ft_putendl_fd("EXIT", 1);
			break ;
		}
		cmd = ft_split(data.input, 32);
		if (!ft_strncmp(cmd[0], "cd", 2))
			chdir(cmd[1]);
		else
			run_cmd(data.input, &data);
		add_history(data.input);
	}
	rl_clear_history();
	return (0);
}
