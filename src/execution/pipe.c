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
	while (struc()->pid[i])
	{
		waitpid(struc()->pid[i], &status, 0);
		i++;
	}
	free(struc()->pid);
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
		if ((*lcmd)->cmd)
			exec((*lcmd)->cmd);
		exit(0);
	}
}

// int	check_cmd(t_cmd	**lcmd, int i)
// {
// 	t_cmd	*current;

// 	(void)i;
// 	current = *lcmd;
// 	while (current)
// 	{
// 		current = current->next;
// 	}
// 	while ((*lcmd) != current)
// 		(*lcmd) = (*lcmd)->next;
// }

void	run_pipe(char	***cmd)
{
	t_cmd	*current;
	t_cmd	*lcmd;
	int		pfd[2];
	int		fd_out;
	int		i;

	count(cmd, 0);
	current = NULL;
	if (struc()->number_of_cmd > 0)
	{
		lcmd = ft_setnode(cmd, &current);
		struc()->pid = malloc((struc()->pipenum + 1) * sizeof(pid_t *));
		i = 0;
		lcmd->fd_in = 0;
		fd_out = dup(STDOUT_FILENO);
		while (lcmd)
		{
			if (lcmd->next && lcmd->cmd && !ft_strcmp(lcmd->cmd[0], "|"))
				lcmd = lcmd->next;
			if (!lcmd->next && lcmd->cmd && (!ft_strcmp(lcmd->cmd[0], "|")))
				break ;
			if (i < struc()->pipenum)
				pipe(pfd);
			struc()->pid[i] = fork();
			struc()->is_child = 1;
			run_cmds(&lcmd, pfd, fd_out, i);
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
	ft_free_all(current, cmd);
}

	// j = 0;
	// while (lcmd)
	// {
	// 	ft_printf("cmd %d:\n", j);
	// 	i = 0;
	// 	while (lcmd->redir_in && lcmd->redir_in[i])
	// 	{
	// 		ft_printf("%s ", lcmd->redir_in[i]);
	// 		i++;
	// 	}
	// 	ft_printf("\n");
	// 	i = 0;
	// 	while (lcmd->cmd && lcmd->cmd[i])
	// 	{
	// 		ft_printf("%s ", lcmd->cmd[i]);
	// 		i++;
	// 	}
	// 	ft_printf("\n");
	// 	i = 0;
	// 	while (lcmd->redir_out && lcmd->redir_out[i])
	// 	{
	// 		ft_printf("%s ", lcmd->redir_out[i]);
	// 		i++;
	// 	}
	// 	ft_printf("\n");
	// 	j++;
	// 	if (!lcmd->next)
	// 		break ;
	// 	lcmd = lcmd->next;
	// }
	// while (lcmd->previous)
	// 	lcmd = lcmd->previous;
