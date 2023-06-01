#include "../../include/minishell.h"

void	input_to_pipe(t_cmd	*cmd)
{
	if (cmd->previous)
	{
		if(dup2(cmd->previous->previous->fd_in, STDIN_FILENO) == -1)
			ft_printf("Error1\n", 2);
		if (close(cmd->previous->previous->fd_in) == -1)
			ft_printf("Error2\n", 2);
	}
	else
	{
		if(dup2(cmd->fd_in, STDIN_FILENO) == -1)
			ft_printf("Error3\n", 2);
		if (close(cmd->fd_in) == -1)
			ft_printf("Error4\n", 2);
	}
}

/*
 * <
*/
void	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);

}

/*
 * >
*/
void	redirect_output(char *file)
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
