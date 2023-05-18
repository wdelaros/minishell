/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:55:14 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/18 11:06:51 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_data
{
	char		**envp;
	char		**path;
	char		*input;
	char		*cmdpath;
	pid_t		*pid;
	int			is_child;
}				t_data;

int		signal_handler(void);
t_data	*struc(void);
char	**findpath(t_data *data);
void	find_executable(char	**fcmd, int i);
void	print_cell(char	**cell);

#endif