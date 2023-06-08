#include "../../include/minishell.h"

void	redir_input(t_cmd	**lcmd)
{
	int	fd;

	if ((*lcmd)->redir_in && !ft_strcmp((*lcmd)->redir_in[0], "<"))
	{
		fd = open((*lcmd)->redir_in[1], O_RDONLY);
		if (fd == -1)
		{
			perror((*lcmd)->redir_in[1]);
			return ;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (struc()->pipenum > 0)
		input_to_pipe(*lcmd);
}

void	redir_output(t_cmd	*lcmd, int	**pfd, int i)
{
	if (lcmd->redir_out && (!ft_strcmp(lcmd->redir_out[0], ">") \
	|| !ft_strcmp(lcmd->redir_out[0], ">>")))
	{
		if (lcmd && !ft_strcmp(lcmd->redir_out[0], ">"))
			output_to_file(lcmd->redir_out[1]);
		else if (lcmd && !ft_strcmp(lcmd->redir_out[0], ">>"))
			append_output(lcmd->redir_out[1]);
	}
	if (i < (struc()->number_of_cmd - 1))
		dup2((*pfd)[1], STDOUT_FILENO);
}

void	input_to_pipe(t_cmd	*cmd)
{
	if (cmd->previous)
	{
		if (dup2(cmd->previous->previous->fd_in, STDIN_FILENO) == -1)
			ft_printf("Error1\n", 2);
		if (close(cmd->previous->previous->fd_in) == -1)
			ft_printf("Error2\n", 2);
	}
	else
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			ft_printf("Error3\n", 2);
		if (close(cmd->fd_in) == -1)
			ft_printf("Error4\n", 2);
	}
}

/*
 * >
*/
void	output_to_file(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

/*
 * >>
*/
void	append_output(char	*file)
{
	int	fd;

	fd = open(file, O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
