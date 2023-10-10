/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:27:36 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/10 12:29:55 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "parsing.h"
# include "../readline/history.h"
# include "../readline/readline.h"
# include <fcntl.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>

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
	int			pipenum;
}				t_data;

typedef struct s_cmd
{
	char			**cmd;
	char			**redir_in;
	char			**redir_out;
	int				fd_in;
	int				good;
	struct s_cmd	*previous;
	struct s_cmd	*next;
}				t_cmd;

t_data	*struc(void);
void	signal_handler_child(int heredoc);
int		signal_handler(int sleep, int interactive);

//minishell_utils.c
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