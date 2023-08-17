#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_e_data
{
	pid_t		*pid;
	pid_t		*skip;
	int			number_of_cmd;
	int			tmp_i;
}				t_e_data;

typedef struct s_exec
{
	int			pfd[2];
	int			fd_out;
}				t_exec;

typedef struct s_pilist
{
	char	**input;
	char	**output;
	char	**command;
	int		fd;
}				t_pilist;

t_e_data	*e_struc(void);
void		exec(char **fcmd, t_cmd	*lcmd, char ***cmd_to_free);
void		ft_exit_message(char **fcmd, t_cmd *lcmd, char ***cmd, int code);
int			exit_status(int status);


void		redir_input(t_cmd	**lcmd, int	**pfd, char	***cmd, int fd_out);
void		redir_output(t_cmd	*lcmd, int	**pfd, int i);

t_cmd		*ft_setnode(char	***arg, t_cmd	**current);

void		count(char ***cmd, int i);
void		reset_fd(int *fd);
void		wait_end_cmd(void);

char		**findpath(t_data *data);
void		find_executable(char	**fcmd, int i);

int			is_builtin(char	**cmd);
void		redir_builtin(t_cmd	*lcmd, char	***cmd, int fd_out, int *pfd);
void		run_builtin(t_cmd	*lcmd, char	***cmd, int fd_out, int	*pfd);

#endif