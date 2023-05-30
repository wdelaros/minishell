#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "parsing.h"
# include <dirent.h>
# include <fcntl.h>
# include "../readline/history.h"
# include "../readline/readline.h"
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include "../uwu/C_tool.h"

# define DEFAULT_ECHO_TERM 207

typedef struct s_data
{
	char		**envp;
	char		**path;
	char		*input;
	char		*cmdpath;
	pid_t		*pid;
	int			is_child;
	int			pipenum;
	int			number_of_cmd;
	int			redirnum;
}				t_data;

t_data	*struc(void);
int		signal_handler(void);
char	**findpath(t_data *data);
void	find_executable(char	**fcmd, int i);
void	print_cell(char	***cell);
void	exec(char **fcmd);

void	count(char	**cmd, int	i);
void	run_pipe(char	**cmd);

void	redirect_input(char *file);
void	redirect_output(char *file);
void	append_output(char	*file);

#endif