#include "../../include/minishell.h"

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
	ft_xfree(struc()->pid);
	ft_xfree(struc()->skip);
}

/// @brief create all output file, count the number of command
/// and the number of pipe
/// @param cmd 
/// @param i 
void	count(char ***cmd, int i)
{
	struc()->pipenum = 0;
	struc()->number_of_cmd = 0;
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
			struc()->number_of_cmd++;
		i++;
	}
}
