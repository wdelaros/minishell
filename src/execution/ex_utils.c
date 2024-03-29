/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:34:50 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/12 07:43:52 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

t_ex_data	*ex_struc(void)
{
	static t_ex_data	ex_data;

	return (&ex_data);
}

void	ft_exit_message(char **fcmd, t_cmd *lcmd, char ***cmd, int code)
{
	if (code == 127 || !fcmd[0][0])
		ft_dprintf(2, "minishell: %s: command not found\n", fcmd[0]);
	else if (code == 126)
		ft_dprintf(2, "minishell: %s: Permission denied\n", fcmd[0]);
	else if (code == 1261)
	{
		ft_dprintf(2, "minishell: %s: is a directory\n", fcmd[0]);
		code = 126;
	}
	else
		ft_dprintf(2, "minishell: %s: operations not permitted\n", fcmd[0]);
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
	struct stat	path;

	struc()->path = findpath(struc());
	find_executable(fcmd, 0, struc());
	if (execve(struc()->cmdpath, fcmd, struc()->envp) == -1)
	{
		lstat(struc()->cmdpath, &path);
		if (access(struc()->cmdpath, F_OK))
			ft_exit_message(fcmd, lcmd, cmd_to_free, 127);
		else if (access(struc()->cmdpath, X_OK))
			ft_exit_message(fcmd, lcmd, cmd_to_free, 126);
		else if (S_ISDIR(path.st_mode))
			ft_exit_message(fcmd, lcmd, cmd_to_free, 1261);
		else
			ft_exit_message(fcmd, lcmd, cmd_to_free, 1);
	}
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
