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

# define DEFAULT_ECHO_TERM 207
# define RUN 0
# define GROSSE_ERROR 1

typedef struct s_data
{
	char		**envp;
	char		**path;
	char		*input;
	char		*cmdpath;
	pid_t		*pid;
	pid_t		*skip;
	int			is_child;
	int			exit_code;
	int			pipenum;
	int			number_of_cmd;
	int			redirnum;
	int			tmp_i;
}				t_data;

typedef struct s_cmd
{
	char			**cmd;
	char			**redir_in;
	char			**redir_out;
	int				fd_in;
	struct s_cmd	*previous;
	struct s_cmd	*next;
}				t_cmd;

t_data	*struc(void);
int		signal_handler(void);
char	**findpath(t_data *data);
void	find_executable(char	**fcmd, int i);
void	exec(char **fcmd, t_cmd	*lcmd, char ***cmd_to_free);

void	print_cell(char	***cell);
void	ft_exit_message(char **fcmd, t_cmd *lcmd, char ***cmd, int code);
int		exit_status(int status);

void	run_pipe(char	***cmd);

void	ft_free_all_pipe(t_cmd *current, char ***cmd);
void	count(char ***cmd, int i);

t_cmd	*ft_setnode(char	***arg, t_cmd	**current);

void	redir_input(t_cmd	**lcmd, int	**pfd, char	***cmd, int fd_out);
void	redir_output(t_cmd	*lcmd, int	**pfd, int i);

int		error_handler(char *input);

#endif