#include "../../include/minishell.h"

t_data	*struc(void)
{
	static t_data	data;

	return (&data);
}

static void	ft_error(int code)
{
	struc()->exit_code = 258;
	if (code == 1)
		ft_dprintf(2, "minishell: syntax error near unexpected token `|'\n");
	else if (code == 2)
		ft_dprintf(2, \
		"minishell: syntax error near unexpected token `newline'\n");
	else if (code == 3)
		ft_dprintf(2, \
		"minishell: syntax error near unexpected token `quote'\n");
}

/**
 * execute a command
 * execve(the path of the command, the command, environment)
*/
void	exec(char **fcmd, t_cmd	*lcmd, char ***cmd_to_free)
{
	struc()->path = findpath(struc());
	find_executable(fcmd, 0);
	if (execve(struc()->cmdpath, fcmd, struc()->envp) == -1)
	{
		if (access(struc()->cmdpath, F_OK))
			ft_exit_message(fcmd, lcmd, cmd_to_free, 127);
		else if (access(struc()->cmdpath, X_OK))
			ft_exit_message(fcmd, lcmd, cmd_to_free, 126);
		else
			ft_exit_message(fcmd, lcmd, cmd_to_free, 1);
	}
}

static void	initialize(int argc, char **argv, char **envp)
{
	char	**envcpy;

	(void)argc;
	(void)argv;
	envcpy = cpy_environement(NULL, envp);
	struc()->export = cpy_environement(NULL, envp);
	//export OLDPWD
	struc()->envp = envcpy;
	struc()->exit_code = 0;
	struc()->is_child = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char	***cmd;
	int		err;
	int j = 0;

	if (signal_handler())
		exit(1);
	initialize(argc, argv, envp);
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
			ft_error(err);
		else if (err == RUN)
		{
			if (j == 1)
			{
				int i = 1;
				cmd = ft_calloc(100, sizeof(char **));
				while (i > 0)
				{
					i--;
					cmd[i] = ft_calloc(100, sizeof(char *));
				}

				cmd[0][0] = ft_strdup("export");
				cmd[0][1] = ft_strdup("1");
				cmd[0][2] = ft_strdup("1");
			}
			else
				cmd = string_handler(struc()->input);
			j++;
			run_pipe(cmd);
		}
		printf("exit code: %d\n", struc()->exit_code);
	}
	ft_free_null(struc()->envp);
	ft_free_null(struc()->export);
	rl_clear_history();
	return (0);
}
