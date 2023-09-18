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

# ifndef GRN
#  define GRN "\x1b[32;49m"
# endif

# ifndef WHT
#  define WHT "\x1b[0m"
# endif

typedef struct s_data
{
	char		**envp;
	char		**export;
	char		**path;
	char		*input;
	char		*cmdpath;
	int			exit_code;
	char		*current_pwd;
	int			is_child;
	int			pipenum;
}				t_data;

typedef struct s_cmd
{
	char			**cmd;
	char			**redir_in;
	char			**redir_out;
	char			*tmp_file[16];
	int				fd_in;
	int				good;
	struct s_cmd	*previous;
	struct s_cmd	*next;
}				t_cmd;

t_data	*struc(void);
int		signal_handler(int sleep, int interactive);

//minishell_utils.c
void	print_cell(char	***cell);
char	*ft_prompt_line(void);
void	logo(void);
void	ft_error(int code);

int		error_handler(char *input);

char	**cpy_environement(char **env, char **cpy_env);

/*--------------------execution--------------------*/

void	run_pipe(char	***cmd);
void	ft_free_triple_pointer(char	***cmd);
void	ft_free_all_pipe(t_cmd *current, char ***cmd);

/*--------------------built_in--------------------*/

int		ft_unset(char **unset, t_data *data);
int		cd(char	*dir);
int		ft_env(char **envp);
int		pwd(void);
int		export(char **content, t_data *data);
void	ft_exit(char **cmd, t_cmd *lcmd, char ***to_free, int fd_out);
int		echo(char **input);

#endif