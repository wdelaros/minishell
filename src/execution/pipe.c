#include "../../include/execution.h"

/// @brief make all redirection and execute a command
/// @param lcmd the list of command
/// @param pfd the file descriptor
/// @param fd_out a copy of the stdout file descriptor
/// @param cmd the command line
static void	run_cmds(t_cmd	**lcmd, int	*pfd, int fd_out, char ***cmd)
{
	if (ex_struc()->pid[ex_struc()->tmp_i] == -1)
		return ;
	if (!ex_struc()->pid[ex_struc()->tmp_i])
	{
		signal_handler_child(NO);
		redir_input(lcmd, &pfd, cmd, fd_out);
		redir_output(*lcmd, &pfd, ex_struc()->tmp_i);
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
		free(struc()->current_pwd);
		ft_free_null(struc()->envp);
		ft_free_null(struc()->export);
		exit(struc()->exit_code);
	}
}

static void	run_pipe2(char	***cmd, int *i, t_cmd **lcmd, t_exec *ex)
{
	ex_struc()->skip[*i] = 1;
	if ((*lcmd)->next && (*lcmd)->cmd && !ft_strcmp((*lcmd)->cmd[0], "|"))
		(*lcmd) = (*lcmd)->next;
	if (*i < struc()->pipenum)
		pipe((*ex).pfd);
	if (is_builtin((*lcmd)->cmd) != 1 || struc()->pipenum > 0)
	{
		ex_struc()->pid[*i] = fork();
		ex_struc()->tmp_i = *i;
		run_cmds(lcmd, (*ex).pfd, (*ex).fd_out, cmd);
		ex_struc()->skip[*i] = 0;
	}
	else
	{
		run_builtin((*lcmd), cmd, (*ex).fd_out, (*ex).pfd);
		ex_struc()->skip[*i] = 2;
	}
	if (struc()->pipenum > 0)
		close((*ex).pfd[1]);
	if ((*lcmd)->previous && struc()->pipenum > 0)
		close((*lcmd)->previous->previous->fd_in);
	(*lcmd)->fd_in = (*ex).pfd[0];
	*i += 1;
	(*lcmd) = (*lcmd)->next;
}

/// @brief 
/// @param cmd the command line
void	run_pipe(char	***cmd)
{
	t_cmd	*current;
	t_cmd	*lcmd;
	t_exec	ex;
	int		i;

	if (!cmd || !cmd[0] || !cmd[0][0])
		return ;
	current = NULL;
	struc()->exit_code = 0;
	lcmd = ft_setnode(cmd, &current);
	ex_struc()->pid = malloc((struc()->pipenum + 1) * sizeof(pid_t *));
	ex_struc()->skip = malloc((struc()->pipenum + 1) * sizeof(int *));
	if (ex_struc()->number_of_cmd > 0)
	{
		i = 0;
		lcmd->fd_in = 0;
		ex.fd_out = dup(STDOUT_FILENO);
		while (lcmd)
			run_pipe2(cmd, &i, &lcmd, &ex);
		close(ex.fd_out);
		if (struc()->pipenum > 0)
			reset_fd(ex.pfd);
		wait_end_cmd();
	}
	ft_free_all_pipe(current, cmd);
}
