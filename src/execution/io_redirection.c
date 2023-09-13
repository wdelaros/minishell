#include "../../include/execution.h"

/// @brief redirect the output to a file
/// @param file the name of the file
void	output_to_file(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

/// @brief redirect the input to a file
/// @param file the name of the file
void	append_output(char	*file)
{
	int	fd;

	fd = open(file, O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	input_to_pipe(t_cmd	*cmd)
{
	if (cmd->previous)
	{
		if (dup2(cmd->previous->previous->fd_in, STDIN_FILENO) == -1)
			ft_dprintf(2, "dup2 stdin failed\n", 2);
		if (close(cmd->previous->previous->fd_in) == -1)
			ft_dprintf(2, "close stdin failed\n", 2);
	}
	else
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			ft_dprintf(2, "dup2 stdin failed\n", 2);
}

/// @brief redirect input of file or a pipe
/// @param lcmd list of command
void	redir_input(t_cmd	**lcmd, int	**pfd, char	***cmd, int fd_out)
{
	int	fd;

	if ((*lcmd)->redir_in && (!ft_strcmp((*lcmd)->redir_in[0], "<") || !ft_strcmp((*lcmd)->redir_in[0], "<<")))
	{
		fd = open((*lcmd)->redir_in[1], O_RDONLY);
		if (fd == -1)
		{
			close(fd_out);
			if (struc()->pipenum > 0)
			{
				if ((*lcmd)->previous && (*lcmd)->previous->previous)
					close((*lcmd)->previous->previous->fd_in);
				close((*pfd)[0]);
				close((*pfd)[1]);
			}
			ft_free_all_pipe((*lcmd), cmd);
			free_env();
			rl_clear_history();
			exit (struc()->exit_code);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (struc()->pipenum > 0)
		input_to_pipe(*lcmd);
}

/// @brief redirect the output of a command to a file or a pipe
/// @param lcmd list of command
/// @param pfd file descriptor
void	redir_output(t_cmd	*lcmd, int	**pfd, int i)
{
	if (lcmd->redir_out && (!ft_strcmp(lcmd->redir_out[0], ">") \
	|| !ft_strcmp(lcmd->redir_out[0], ">>")))
	{
		if (lcmd && !ft_strcmp(lcmd->redir_out[0], ">"))
			output_to_file(lcmd->redir_out[1]);
		else if (lcmd && !ft_strcmp(lcmd->redir_out[0], ">>"))
			append_output(lcmd->redir_out[1]);
		if (struc()->pipenum > 0)
		{
			close((*pfd)[0]);
			close((*pfd)[1]);
		}
	}
	if (i < (e_struc()->number_of_cmd - 1))
		dup2((*pfd)[1], STDOUT_FILENO);
}
