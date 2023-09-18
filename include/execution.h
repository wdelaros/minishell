#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_ex_data
{
	pid_t		*pid;
	pid_t		*skip;
	int			number_of_cmd;
	int			tmp_i;
}				t_ex_data;

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

//ex_utils.c
t_ex_data	*ex_struc(void);
void		exec(char **fcmd, t_cmd	*lcmd, char ***cmd_to_free);
void		ft_exit_message(char **fcmd, t_cmd *lcmd, char ***cmd, int code);
int			exit_status(int status);

//io_redirection.c
void		redir_input(t_cmd	**lcmd, int	**pfd, char	***cmd, int fd_out);
void		redir_output(t_cmd	*lcmd, int	**pfd, int i);

//list.c
t_cmd		*ft_setnode(char	***arg, t_cmd	**current);

//list_utils.c
t_cmd		*picreate_node(void);
t_pilist	list_null(void);
int			ft_perror(char ***arg, int i, t_pilist	*list);
t_cmd		*finish_node(t_cmd *node, char	**redir_in, char **cmd, \
char **redir_out);

//pipe_utils.c
void		reset_fd(int *fd);
void		free_env(void);
void		wait_end_cmd(void);

char		**findpath(t_data *data);
void		find_executable(char	**fcmd, int i, t_data	*data);

//exec_builtin.c
int			is_builtin(char	**cmd);
void		redir_builtin(t_cmd	*lcmd, char	***cmd, int fd_out, int *pfd);
void		run_builtin(t_cmd	*lcmd, char	***cmd, int fd_out, int	*pfd);

#endif