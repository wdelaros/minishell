#include "../../include/minishell.h"

t_data	*struc(void)
{
	static t_data	data;

	return (&data);
}

/**
 * execute a command
 * execve(the path of the command, the command, environment)
*/
void	exec(char **fcmd)
{
	struc()->path = findpath(struc());
	find_executable(fcmd, 0);
	int	i = 0;		//a enlever
	char l = 'A';	//a enlever
	while (fcmd[i])	//a enlever
	{
		Ct_mprintf(fcmd[i], ft_strlen(fcmd[i]) + 1, 1, l);	//a enlever
		i++;	//a enlever
		l++;	//a enlever
	}	//a enlever
	if (execve(struc()->cmdpath, fcmd, struc()->envp) == -1)
	{
		perror(fcmd[0]);
		exit (1);
	}
}

/**
 * create a fork(new process) for execute a command
*/
void	run_cmd(char **cmd)
{
	int		status;

	if (!ft_strncmp(cmd[0], "cd", 2))
	{
		chdir(cmd[1]);
		return ;
	}
	struc()->pid[0] = fork();
	struc()->is_child = 1;
	if (struc()->pid[0] == -1)
		return ;
	if (!struc()->pid[0])
		exec(cmd);
	waitpid(struc()->pid[0], &status, 0);
}

void	initialize(char **envp)
{
	struc()->envp = envp;
	struc()->is_child = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char	***cmd;
	// int		i;

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
		cmd = string_handler(struc()->input);
		// i = 3;
		// cmd = ft_calloc(20, sizeof(char **));
		// while (i > 0)
		// {
		// 	i--;
		// 	cmd[i] = ft_calloc(20, sizeof(char *));
		// }

		// cmd[0][0] = ft_strdup("<"); // a enlever
		// cmd[0][1] = ft_strdup("out"); // a enlever

		// cmd[1][0] = ft_strdup("|"); // a enlever

		// cmd[2][0] = ft_strdup("wc"); // a enlever
		// cmd[2][1] = ft_strdup("-l"); // a enlever
		run_pipe(cmd);
		if (ft_strcmp("", struc()->input))
			add_history(struc()->input);
		free(struc()->input);
	}
	rl_clear_history();
}
