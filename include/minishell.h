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
	char		**export;
	char		**path;
	char		*input;
	char		*cmdpath;
	int			exit_code;
	int			is_child;
	pid_t		*pid;
	pid_t		*skip;
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

typedef struct s_pilist
{
	char	**input;
	char	**output;
	char	**command;
	int		fd;
}				t_pilist;

typedef struct s_exec
{
	pid_t		*pid;
	pid_t		*skip;
	int			pipenum;
	int			redirnum;
	int			tmp_i;
}				t_exec;

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

char	**cpy_environement(char **env, char **cpy_env);

/*--------------------built_in--------------------*/

int		ft_unset(char **unset, t_data *data);
int		cd(char	*dir);
int		ft_env(char **envp);
int		pwd(void);
int		export(char **content, t_data *data);
void	ft_exit(char **cmd, t_cmd *lcmd, char ***to_free, int fd_out);

#endif