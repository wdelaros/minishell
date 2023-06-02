#include "../../include/minishell.h"

void	count(char ***cmd, int i)
{
	int	fd;

	struc()->pipenum = 0;
	struc()->number_of_cmd = 0;
	while (cmd[i])
	{
		if (cmd[i][0] && !ft_strcmp(cmd[i][0], "|"))
			struc()->pipenum++;
		else if (cmd[i][0] && !ft_strcmp(cmd[i][0], "<"))
			;
		else if (cmd[i][0] && !ft_strcmp(cmd[i][0], ">"))
		{
			fd = open(cmd[i][1], O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
			close(fd);
		}
		else if (cmd[i][0] && !ft_strcmp(cmd[i][0], ">>"))
		{
			fd = open(cmd[i][1], O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
			close(fd);
		}
		else if (cmd[i][0])
			struc()->number_of_cmd++;
		i++;
	}
}

void	wait_end_cmd(void)
{
	int	status;
	int	i;

	i = 0;
	while (i <= struc()->number_of_cmd - 1)
	{
		waitpid(struc()->pid[i], &status, 0);
		i++;
	}
}

void	reset_fd(int	*fd)
{
	rl_clear_history();
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
}

void	ft_free_all(t_cmd *current, char ***cmd)
{
	int	i;

	if (current)
	{
		while (current->previous != NULL)
		{
			current = current->previous;
			free(current->next);
		}
		free(current);
	}
	i = 0;
	while (cmd[i])
	{
		cmd[i] = ft_free_null(cmd[i]);
		i++;
	}
	free(cmd);
	free(struc()->pid);
}

static void	run_cmds(t_cmd	**lcmd, int	*pfd, int fd_out, int i)
{
	if (struc()->pid[i] == -1)
		return ;
	if (!struc()->pid[i])
	{
		redir_input(lcmd);
		redir_output(*lcmd, &pfd, i);
		if (struc()->pipenum > 0)
		{
			close(pfd[0]);
			close(pfd[1]);
		}
		close(fd_out);
		rl_clear_history();
		exec((*lcmd)->cmd);
	}
}

void	run_pipe(char	***cmd)
{
	t_cmd	*current;
	t_cmd	*lcmd;
	int		pfd[2];
	int		fd_out;
	int		i;

	count(cmd, 0);
	current = NULL;
	struc()->pid = malloc((struc()->pipenum + 1) * sizeof(pid_t *));
	lcmd = ft_setnode(cmd, &current);
	i = 0;
	while (lcmd->next && !ft_strcmp(lcmd->cmd[0], "<"))
		lcmd = lcmd->next;
	lcmd->fd_in = 0;
	fd_out = dup(STDOUT_FILENO);
	while (lcmd)
	{
		if (lcmd->next && !ft_strcmp(lcmd->cmd[0], "|"))
			lcmd = lcmd->next;
		while (lcmd->next && (!ft_strcmp(lcmd->cmd[0], ">") || \
		!ft_strcmp(lcmd->cmd[0], ">>") || !ft_strcmp(lcmd->cmd[0], "<")))
			lcmd = lcmd->next;
		if (!lcmd->next && (!ft_strcmp(lcmd->cmd[0], "|") \
		|| !ft_strcmp(lcmd->cmd[0], ">") || !ft_strcmp(lcmd->cmd[0], ">>")))
			break ;
		if (i < struc()->pipenum)
			pipe(pfd);
		struc()->pid[i] = fork();
		struc()->is_child = 1;
		run_cmds(&lcmd, pfd, fd_out, i);
		if (struc()->pipenum > 0)
			close(pfd[1]);
		if (lcmd->previous && lcmd->previous->previous && struc()->pipenum > 0)
			close(lcmd->previous->previous->fd_in);
		lcmd->fd_in = pfd[0];
		i++;
		if (!lcmd->next)
			break ;
		lcmd = lcmd->next;
	}
	close(fd_out);
	if (struc()->number_of_cmd > 1)
		reset_fd(pfd);
	wait_end_cmd();
	ft_free_all(current, cmd);
}
