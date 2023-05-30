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
	Ct_mprintf(fcmd[0], ft_strlen(fcmd[0]) + 1, 1, 'A');
	Ct_mprintf(fcmd[1], ft_strlen(fcmd[1]) + 1, 1, 'B');
	Ct_mprintf(fcmd[2], ft_strlen(fcmd[2]) + 1, 1, 'C');
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
	// pid_t	*temp;

	struc()->envp = envp;
	// temp = ft_calloc(2, sizeof(pid_t *));
	// struc()->pid = temp;
	// free(temp);
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
		cmd = string_handler(struc()->input);
		run_pipe(cmd);
		add_history(struc()->input);
	}
	rl_clear_history();
}
