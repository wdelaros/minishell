#include "../../include/execution.h"

t_e_data	*e_struc(void)
{
	static t_e_data	e_data;

	return (&e_data);
}

void	ft_exit_message(char **fcmd, t_cmd *lcmd, char ***cmd, int code)
{
	if (code == 127)
		ft_dprintf(2, "minishell: %s: command not found\n", fcmd[0]);
	else if (code == 126)
		ft_dprintf(2, "minishell: %s: Permission denied\n", fcmd[0]);
	else
		ft_dprintf(2, "minishell: %s: is a directory\n", fcmd[0]);
	ft_free_all_pipe(lcmd, cmd);
	free(struc()->current_pwd);
	ft_free_null(struc()->path);
	ft_free_null(struc()->envp);
	ft_free_null(struc()->export);
	free(struc()->cmdpath);
	exit (code);
}

/**
 * execute a command
 * execve(the path of the command, the command, environment)
*/
void	exec(char **fcmd, t_cmd	*lcmd, char ***cmd_to_free)
{
	struc()->path = findpath(struc());
	find_executable(fcmd, 0, struc());
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

int	ft_perror(char ***arg, int i, t_pilist	*list)
{
	perror(arg[i][1]);
	while (ft_strcmp(arg[i][0], "|") && (arg[i + 1] && \
	ft_strcmp(arg[i + 1][0], "|")))
		i++;
	if (ft_strcmp(arg[i][0], "|") && !arg[i + 1])
		struc()->exit_code = 1;
	list->input = NULL;
	list->command = NULL;
	list->output = NULL;
	return (i);
}

int	exit_status(int status)
{
	int	result;

	result = 0;
	if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		result = (128 + WTERMSIG(status));
	return (result);
}
