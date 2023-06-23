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
void	exec(char **fcmd, t_cmd	*lcmd, char ***cmd_to_free)
{
	struc()->path = findpath(struc());
	find_executable(fcmd, 0);
	// int	i = 0;		//a enlever
	// char l = 'A';	//a enlever
	// while (fcmd[i])	//a enlever
	// {
	// 	Ct_mprintf(fcmd[i], ft_strlen(fcmd[i]) + 1, 1, l);	//a enlever
	// 	i++;	//a enlever
	// 	l++;	//a enlever
	// }	//a enlever
	if (execve(struc()->cmdpath, fcmd, struc()->envp) == -1)
	{
		if (access(struc()->cmdpath, F_OK))
		{
			printf("minishell: %s: command not found\n", fcmd[0]);
			exit (127);
		}
		else if (access(struc()->cmdpath, X_OK))
		{
			printf("minishell: %s: Permission denied\n", fcmd[0]);
			exit (126);
		}
		else
		{
			printf("minishell: %s: exit 1", fcmd[0]);
			exit (1);
		}
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
	struc()->exit_code = 0;
	struc()->envp = envp;
	struc()->is_child = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char	***cmd;

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
		if (ft_strcmp("", struc()->input))
			add_history(struc()->input);
		cmd = string_handler(struc()->input);
		free(struc()->input);
		run_pipe(cmd);
	}
	rl_clear_history();
}
