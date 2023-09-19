#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_ex_data
{
	pid_t		*pid;
	pid_t		*skip;
	char		**heredoc;
	int			number_of_cmd;
	int			tmp_i;
}				t_ex_data;

typedef struct s_heredoc
{
	pid_t		pid;
	int			fd;
	int			flag;
	int			status;
	char		*line;
	char		*delimiter;
	struct stat	sfd;
	struct stat	sfile;
}				t_heredoc;

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
int			exit_status(int status);
void		exec(char **fcmd, t_cmd	*lcmd, char ***cmd_to_free);
void		ft_exit_message(char **fcmd, t_cmd *lcmd, char ***cmd, int code);
t_ex_data	*ex_struc(void);

//exec_builtin.c
int			is_builtin(char	**cmd);
void		redir_builtin(t_cmd	*lcmd, char	***cmd, int fd_out, int *pfd);
void		run_builtin(t_cmd	*lcmd, char	***cmd, int fd_out, int	*pfd);

//here_doc.c
int			ft_here_doc(t_pilist *list, char **str, t_cmd **current, 
				char ***cmd);

//io_redirection.c
void		redir_input(t_cmd	**lcmd, int	**pfd, char	***cmd, int fd_out);
void		redir_output(t_cmd	*lcmd, int	**pfd, int i);

//list_utils.c
int			ft_perror(char ***arg, int i, t_pilist	*list);
t_pilist	list_null(void);
t_cmd		*picreate_node(void);
t_cmd		*finish_node(t_cmd *node, char	**redir_in, char **cmd, 
				char **redir_out);

//list.c
t_cmd		*ft_setnode(char	***arg, t_cmd	**current);
char		*mini_parsing(char *str, char **env, int err);

//path.c
char		**findpath(t_data *data);
void		find_executable(char	**fcmd, int i, t_data	*data);

//pipe_utils.c
void		reset_fd(int *fd);
void		free_env(void);
void		wait_end_cmd(void);

//random_heredoc_gen.c
char		*heredoc_file(void);

#endif