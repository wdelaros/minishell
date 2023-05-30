#include "../../include/minishell.h"

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
