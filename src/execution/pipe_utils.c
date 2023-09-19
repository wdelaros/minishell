/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:13 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 13:35:14 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

/// @brief wait the end of each command
void	wait_end_cmd(void)
{
	int	status;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < ex_struc()->number_of_cmd)
	{
		if (ex_struc()->skip[i] == 0)
			waitpid(ex_struc()->pid[i], &status, 0);
		if (ex_struc()->skip[i] != 1)
			j++;
		i++;
	}
	if (!ex_struc()->skip[i - 1])
		struc()->exit_code = exit_status(status);
}

/// @brief reset the fd at the end of a command line
/// @param fd the file descriptor
void	reset_fd(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
}

void	free_env(void)
{
	ft_free_null(struc()->envp);
	ft_free_null(struc()->export);
	rl_clear_history();
}

void	ft_free_triple_pointer(char	***cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			cmd[i] = ft_free_null(cmd[i]);
			i++;
		}
		ft_xfree(cmd);
	}
}

/// @brief free
/// @param current struct to free 
/// @param cmd triple pointer to free
void	ft_free_all_pipe(t_cmd *current, char ***cmd)
{
	if (current)
	{
		while (current->next)
			current = current->next;
		while (current->previous != NULL)
		{
			current = current->previous;
			if (current->next->redir_in
				&& !ft_strcmp(current->next->redir_in[0], "<<") 
				&& !access(current->next->redir_in[1], F_OK))
				unlink(current->next->redir_in[1]);
			free(current->next);
		}
		if (current->redir_in && !ft_strcmp(current->redir_in[0], "<<") 
			&& !access(current->redir_in[1], F_OK))
			unlink(current->redir_in[1]);
		free(current);
	}
	ft_free_triple_pointer(cmd);
	ft_xfree(ex_struc()->pid);
	ft_xfree(ex_struc()->skip);
}
