#include "../../include/minishell.h"

t_data	*struc(void)
{
	static t_data	data;

	return (&data);
}

static void	ft_error_message(char **fcmd, t_cmd	*lcmd, char ***cmd, int	code)
{
	if (code == 127)
		printf("minishell: %s: command not found\n", fcmd[0]);
	else if (code == 126)
		printf("minishell: %s: Permission denied\n", fcmd[0]);
	else
		printf("minishell: %s: exit 1", fcmd[0]);
	ft_free_all_pipe(lcmd, cmd);
	ft_free_null(struc()->path);
	free(struc()->cmdpath);
	free(struc()->pid);
	free(struc()->skip);
	exit (code);
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
			ft_error_message(fcmd, lcmd, cmd_to_free, 127);
		else if (access(struc()->cmdpath, X_OK))
			ft_error_message(fcmd, lcmd, cmd_to_free, 126);
		else
			ft_error_message(fcmd, lcmd, cmd_to_free, 1);
	}
}

void	initialize(char **envp)
{
	struc()->envp = envp;
	struc()->exit_code = 0;
	struc()->is_child = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char	***cmd;
	int		err;

	(void)argc;
	(void)argv;
	if (signal_handler())
		exit(1);
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
		err = error_handler(struc()->input);
		if (err != RUN)
			printf ("OUOUOUOOU J'AI UNE ERREUR!\n");
		else if (err == RUN)
		{
			cmd = string_handler(struc()->input, envp);
			run_pipe(cmd);
		}
		printf("exit code: %d\n", struc()->exit_code);
	}
	rl_clear_history();
	return (0);
}
