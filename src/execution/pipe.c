#include "../../include/minishell.h"

t_cmd	*create_node(char	**cmd)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->cmd = cmd;
	node->previous = NULL;
	node->next = NULL;
	return (node);
}

t_cmd	*ft_setnode(char	***arg, t_cmd	**current)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = create_node(arg[i]);
	(*current) = cmd;
	i++;
	while (arg[i])
	{
		(*current)->next = create_node(arg[i]);
		(*current)->next->previous = (*current);
		(*current) = (*current)->next;
		i++;
	}
	return (cmd);
}

int	ft_pilesize(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	return (ft_pilesize(cmd->next) + 1);
}

void	count(char	***cmd, int	i)
{
	int	fd;

	struc()->pipenum = 0;
	struc()->number_of_cmd = 0;
	struc()->redirnum = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i][0], "|"))
			struc()->pipenum++;
		else if (cmd[i][0] && !ft_strcmp(cmd[i][0], "<"))
		{
			struc()->redirnum += 2;
			i++;
		}
		else if (!ft_strcmp(cmd[i][0], ">") || !ft_strcmp(cmd[i][0], ">>"))
		{
			i++;
			struc()->redirnum++;
			fd = open(cmd[i][0], O_RDWR | O_CREAT, S_IRWXU);
			close(fd);
		}
		else
			struc()->number_of_cmd++;
		i++;
	}
}

void	wait_end_cmd(t_cmd *cmd)
{
	int	status;
	int	i;

	i = 0;
	while (i <= struc()->number_of_cmd - 1)
	{
		waitpid(cmd->pid, &status, 0);
		i++;
	}
}

void	reset_fd(int	*fd)
{
	rl_clear_history();
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
}

void	run_pipe(char	***cmd)
{
	t_cmd	*current;
	t_cmd	*lcmd;
	int	pfd[2];
	int	fd_out;
	int	j;

	count(cmd, 0);
	current = NULL;
	lcmd = ft_setnode(cmd, &current);
	j = 0;
	lcmd->fd_in = 0;
	fd_out = dup(STDOUT_FILENO);
	while (lcmd)
	{
		if (!ft_strcmp(lcmd->cmd[0], "|"))
			lcmd = lcmd->next;
		if (j < struc()->pipenum)
			pipe(pfd);
		lcmd->pid = fork();
		struc()->is_child = 1;
		if (lcmd->pid == -1)
			return ;
		if (!lcmd->pid)
		{
			if (struc()->pipenum > 0)
			{
				input_to_pipe(lcmd);
				if (j < (struc()->number_of_cmd - 1))
					dup2(pfd[1], STDOUT_FILENO);
				close(pfd[0]);
				close(pfd[1]);
			}
			close(fd_out);
			exec(lcmd->cmd);
		}
		if (struc()->pipenum > 0)
			close(pfd[1]);
		if (lcmd->previous)
			close(lcmd->previous->previous->fd_in);
		lcmd->fd_in = pfd[0];
		j++;
		if (!lcmd->next)
			break ;
		lcmd = lcmd->next;
	}
	close(fd_out);
	if (struc()->number_of_cmd > 1)
		reset_fd(pfd);
	wait_end_cmd(lcmd);
	if (current)
	{
		while (current->previous != NULL)
		{
			current = current->previous;
			free(current->next);

		}
		free(current);
	}
	j = 0;
	while (cmd[j])
	{
		cmd[j] = ft_free_null(cmd[j]);
		j++;
	}
	free(cmd);
}






























/* void	run_pipe(char	**cmd)
{
	int	pfd[2];
	int	fd_in;
	int	fd_out;
	int	i;
	int	k; 

	fd_in = 0;
	fd_out = dup(STDOUT_FILENO);
	if (!ft_strcmp(cmd[0], "cd"))
	{
		chdir(cmd[1]);
		return ;
	}
	count(cmd, 0);
	struc()->pid = ft_fcalloc(struc()->pid, struc()->pipenum, sizeof(pid_t *));
	i = 0;
	k = 0;
	if (!ft_strcmp(cmd[i], "exit") && !struc()->pipenum)
	{
		ft_printf("exit\n");
		exit(0);
	}
	while (i < struc()->number_of_cmd + struc()->pipenum + struc()->redirnum)
	{
		if (!ft_strcmp(cmd[i], "|"))
			i++;
		pipe(pfd);
		struc()->pid[k] = fork();
		struc()->is_child = 1;
		if (struc()->pid[k] == -1)
			return ;
		if (!struc()->pid[k])
		{
			if (struc()->redirnum > 0)
			{
				if (!ft_strcmp(cmd[i], "<") && k == 0)
				{
					i += 2;
					redirect_input(cmd[i - 1]);
					if (struc()->redirnum > 2)
					{
						if (!ft_strcmp(cmd[i + 1], ">"))
							redirect_output(cmd[i + 2]);
						else if (!ft_strcmp(cmd[i + 1], ">>"))
							append_output(cmd[i + 2]);
					}
				}
				else if (k == struc()->number_of_cmd - 1)
				{
					if (!ft_strcmp(cmd[i + 1], ">"))
						redirect_output(cmd[i + 2]);
					else if (!ft_strcmp(cmd[i + 1], ">>"))
						append_output(cmd[i + 2]);
				}
			}
			dup2(fd_in, STDIN_FILENO);
			if (k < (struc()->number_of_cmd - 1))
				dup2(pfd[1], STDOUT_FILENO);
			close(pfd[0]);
			if (!ft_strcmp(cmd[i], "exit"))
				exit(0);
			exec(ft_split(cmd, 32));
			// exec(cmd);
		}
		close(pfd[1]);
		fd_in = pfd[0];
		if (struc()->redirnum > 1 && !ft_strcmp(cmd[i], "<"))
			i++;
		if (i + 2 < struc()->number_of_cmd + struc()->pipenum + struc()->redirnum && \
		struc()->redirnum > 2 && (!ft_strcmp(cmd[i + 2], ">") || !ft_strcmp(cmd[i + 2], ">>")))
			i+=2;
		else if ((i + 1 < struc()->number_of_cmd + struc()->pipenum + struc()->redirnum && \
		struc()->redirnum > 0 && (!ft_strcmp(cmd[i + 1], ">") || !ft_strcmp(cmd[i + 1], ">>"))))
			i++;
		k++;
		i++;
	}
	wait_end_cmd();
	dup2(fd_out, STDOUT_FILENO);
	close(pfd[0]);
	close(pfd[1]);
	close(fd_out);
} */
