#include "../../include/execution.h"

/// @brief wait the end of each command
void	wait_end_cmd(void)
{
	int	status;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < e_struc()->number_of_cmd)
	{
		if (e_struc()->skip[i] == 0)
			waitpid(e_struc()->pid[i], &status, 0);
		if (e_struc()->skip[i] != 1)
			j++;
		i++;
	}
	if (!e_struc()->skip[i - 1])
		struc()->exit_code = exit_status(status);
}

/// @brief reset the fd at the end of a command line
/// @param fd the file descriptor
void	reset_fd(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
}

/// @brief free
/// @param current struct to free 
/// @param cmd triple pointer to free
void	ft_free_all_pipe(t_cmd *current, char ***cmd)
{
	int	i;

	if (current)
	{
		while (current->next)
			current = current->next;
		while (current->previous != NULL)
		{
			current = current->previous;
			free(current->next);
		}
		free(current);
	}
	i = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			cmd[i] = ft_free_null(cmd[i]);
			i++;
		}
		free(cmd);
	}
	ft_xfree(e_struc()->pid);
	ft_xfree(e_struc()->skip);
}

/// @brief create all output file, count the number of command
/// and the number of pipe
/// @param cmd 
/// @param i 
void	count(char ***cmd, int i)
{
	struc()->pipenum = 0;
	e_struc()->number_of_cmd = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i][0] && !ft_strcmp(cmd[i][0], "|"))
			struc()->pipenum++;
		else if (cmd[i][0] && !ft_strcmp(cmd[i][0], "<"))
			;
		else if (cmd[i][0] && !ft_strcmp(cmd[i][0], ">"))
			;
		else if (cmd[i][0] && !ft_strcmp(cmd[i][0], ">>"))
			;
		else if (cmd[i][0])
			e_struc()->number_of_cmd++;
		i++;
	}
}
