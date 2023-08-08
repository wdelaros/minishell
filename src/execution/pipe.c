#include "../../include/minishell.h"

/// @brief wait the end of each command
static void	wait_end_cmd(void)
{
	int	status;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < struc()->number_of_cmd)
	{
		if (struc()->skip[i] == 0)
			waitpid(struc()->pid[i], &status, 0);
		if (struc()->skip[i] != 1)
			j++;
		i++;
	}
	if (!struc()->skip[i - 1])
		struc()->exit_code = exit_status(status);
}

/// @brief reset the fd at the end of a command line
/// @param fd the file descriptor
static void	reset_fd(int	*fd)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
}

static int	is_builtin(char	**cmd)
{
	if (!ft_strcmp(cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (1);
	else if (!ft_strcmp(cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd[0], "echo"))
		return (2);
	else if (!ft_strcmp(cmd[0], "env"))
		return (2);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (2);
	return (0);
}

static void	redir_builtin(t_cmd	*lcmd, char	***cmd, int fd_out, int **pfd)
{
	if (pfd)
	{
		redir_input(&lcmd, pfd, cmd, fd_out);
		redir_output(lcmd, pfd, struc()->tmp_i);
		if (struc()->pipenum > 0)
		{
			close(*pfd[0]);
			close(*pfd[1]);
		}
	}
}

static void	run_builtin(t_cmd	*lcmd, char	***cmd, int fd_out, int	*pfd)
{
	t_data	*data;

	data = struc();
	redir_builtin(lcmd, cmd, fd_out, &pfd);
	if (!ft_strcmp(lcmd->cmd[0], "unset"))
		data->exit_code = ft_unset(lcmd->cmd, data);
	else if (!ft_strcmp(lcmd->cmd[0], "env"))
		data->exit_code = ft_env(data->envp);
	else if (!ft_strcmp(lcmd->cmd[0], "export"))
		data->exit_code = export(lcmd->cmd, data);
	else if (!ft_strcmp(lcmd->cmd[0], "pwd"))
		data->exit_code = pwd();
	else if (!ft_strcmp(lcmd->cmd[0], "echo"))
		;
	else if (!ft_strcmp(lcmd->cmd[0], "cd"))
		data->exit_code = cd(lcmd->cmd[1]);
	else if (!ft_strcmp(lcmd->cmd[0], "exit"))
		ft_exit(lcmd->cmd, lcmd, cmd, fd_out);
}

/// @brief make all redirection and execute a command
/// @param lcmd the list of command
/// @param pfd the file descriptor
/// @param fd_out a copy of the stdout file descriptor
/// @param cmd the command line
static void	run_cmds(t_cmd	**lcmd, int	*pfd, int fd_out, char ***cmd)
{
	if (struc()->pid[struc()->tmp_i] == -1)
		return ;
	if (!struc()->pid[struc()->tmp_i])
	{
		redir_input(lcmd, &pfd, cmd, fd_out);
		redir_output(*lcmd, &pfd, struc()->tmp_i);
		if (struc()->pipenum > 0)
		{
			close(pfd[0]);
			close(pfd[1]);
		}
		close(fd_out);
		rl_clear_history();
		struc()->exit_code = 0;
		if (is_builtin((*lcmd)->cmd))
			run_builtin((*lcmd), cmd, fd_out, NULL);
		else if ((*lcmd)->cmd)
			exec((*lcmd)->cmd, *lcmd, cmd);
		ft_free_all_pipe((*lcmd), cmd);
		ft_free_null(struc()->envp);
		ft_free_null(struc()->export);
		exit(struc()->exit_code);
	}
}

/// @brief 
/// @param cmd the command line
void	run_pipe(char	***cmd)
{
	t_cmd	*current;
	t_cmd	*lcmd;
	int		pfd[2];
	int		fd_out;
	int		i;

	count(cmd, 0);
	current = NULL;
	lcmd = ft_setnode(cmd, &current);
	struc()->pid = malloc((struc()->pipenum + 1) * sizeof(pid_t *));
	struc()->skip = malloc((struc()->pipenum + 1) * sizeof(int *));
	if (struc()->number_of_cmd > 0)
	{
		i = 0;
		lcmd->fd_in = 0;
		fd_out = dup(STDOUT_FILENO);
		while (lcmd)
		{
			struc()->skip[i] = 1;
			if (lcmd->next && lcmd->cmd && !ft_strcmp(lcmd->cmd[0], "|"))
				lcmd = lcmd->next;
			if (!lcmd->next && lcmd->cmd && (!ft_strcmp(lcmd->cmd[0], "|")))
				break ;
			if (i < struc()->pipenum)
				pipe(pfd);
			if (is_builtin(lcmd->cmd) != 1 || struc()->pipenum > 0)
			{
				struc()->pid[i] = fork();
				struc()->is_child = 1;
				struc()->tmp_i = i;
				run_cmds(&lcmd, pfd, fd_out, cmd);
				struc()->skip[i] = 0;
			}
			else
			{
				run_builtin(lcmd, cmd, fd_out, pfd);
				struc()->skip[i] = 2;
			}
			if (struc()->pipenum > 0)
				close(pfd[1]);
			if (lcmd->previous && struc()->pipenum > 0)
				close(lcmd->previous->previous->fd_in);
			lcmd->fd_in = pfd[0];
			i++;
			if (!lcmd->next)
				break ;
			lcmd = lcmd->next;
		}
		close(fd_out);
		if (struc()->pipenum > 0)
			reset_fd(pfd);
		wait_end_cmd();
	}
	ft_free_all_pipe(current, cmd);
}

	// int j = 0;
	// while (lcmd)
	// {
	// 	ft_printf("\n-----------------------\n");
	// 	ft_printf("cmd number %d:\ninput: ", j);
	// 	i = 0;
	// 	while (lcmd->redir_in && lcmd->redir_in[i])
	// 	{
	// 		ft_printf("%s ", lcmd->redir_in[i]);
	// 		i++;
	// 	}
	// 	ft_printf("\ncmd: ");
	// 	i = 0;
	// 	while (lcmd->cmd && lcmd->cmd[i])
	// 	{
	// 		ft_printf("%s ", lcmd->cmd[i]);
	// 		i++;
	// 	}
	// 	ft_printf("\noutput: ");
	// 	i = 0;
	// 	while (lcmd->redir_out && lcmd->redir_out[i])
	// 	{
	// 		ft_printf("%s ", lcmd->redir_out[i]);
	// 		i++;
	// 	}
	// 	j++;
	// 	if (!lcmd->next)
	// 		break ;
	// 	lcmd = lcmd->next;
	// }
	// 	ft_printf("\n-----------------------\n");
	// while (lcmd->previous)
	// 	lcmd = lcmd->previous;
