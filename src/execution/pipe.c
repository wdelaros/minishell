#include "../../include/minishell.h"

static void	count(char ***cmd, int i)
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
		{
			waitpid(struc()->pid[i], &status, 0);
			j++;
		}
		i++;
	}
	free(struc()->pid);
	free(struc()->skip);
}

static void	reset_fd(int	*fd)
{
	rl_clear_history();
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
}

static void	ft_free_all_pipe(t_cmd *current, char ***cmd)
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

static void	run_cmds(t_cmd	**lcmd, int	*pfd, int fd_out, char ***cmd)
{
	if (struc()->pid[struc()->tmp_i] == -1)
		return ;
	if (!struc()->pid[struc()->tmp_i])
	{
		redir_input(lcmd);
		redir_output(*lcmd, &pfd, struc()->tmp_i);
		if (struc()->pipenum > 0)
		{
			close(pfd[0]);
			close(pfd[1]);
		}
		close(fd_out);
		rl_clear_history();
		if ((*lcmd)->cmd)
			exec((*lcmd)->cmd);
		while ((*lcmd)->next)
			(*lcmd) = (*lcmd)->next;
		ft_free_all_pipe((*lcmd), cmd);
		free(struc()->pid);
		free(struc()->skip);
		exit(1);
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
	//printf ("JE SUIS ICI\n");
	current = NULL;
	if (struc()->number_of_cmd > 0)
	{
		lcmd = ft_setnode(cmd, &current);
		struc()->pid = malloc((struc()->pipenum + 1) * sizeof(pid_t *));
		struc()->skip = malloc((struc()->pipenum + 1) * sizeof(int *));
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
			struc()->pid[i] = fork();
			struc()->is_child = 1;
			struc()->tmp_i = i;
			run_cmds(&lcmd, pfd, fd_out, cmd);
			if (struc()->pipenum > 0)
				close(pfd[1]);
			if (lcmd->previous && struc()->pipenum > 0)
				close(lcmd->previous->previous->fd_in);
			lcmd->fd_in = pfd[0];
			if (lcmd->cmd)
				struc()->skip[i] = 0;
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
