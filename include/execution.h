#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_exec
{
	// pid_t		*pid;
	// pid_t		*skip;
	// int			pipenum;
	// int			redirnum;
	// int			tmp_i;
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

#endif