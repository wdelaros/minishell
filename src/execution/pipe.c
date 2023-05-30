#include "../../include/minishell.h"

void	count(char	**cmd, int	i)
{
	int	fd;

	struc()->pipenum = 0;
	struc()->number_of_cmd = 0;
	struc()->redirnum = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "|"))
			struc()->pipenum++;
		else if (cmd[i] && !ft_strcmp(cmd[i], "<"))
		{
			struc()->redirnum += 2;
			i++;
		}
		else if (!ft_strcmp(cmd[i], ">") || !ft_strcmp(cmd[i], ">>"))
		{
			i++;
			struc()->redirnum++;
			fd = open(cmd[i], O_RDWR | O_CREAT, S_IRWXU);
			close(fd);
		}
		else
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

void	run_pipe(char	**cmd)
{
	int	pfd[2];
	int	fd_in;
	int	fd_out;
	int	i;
	int	j;

	fd_in = 0;
	count(cmd, 0);
	fd_out = dup(STDOUT_FILENO);
	struc()->pid = ft_calloc(struc()->pipenum + 1, sizeof(pid_t *));
	i = 0;
	j = 0;
	while (i < struc()->number_of_cmd + struc()->pipenum)
	{
		if (!ft_strcmp(cmd[i], "|"))
			i++;
		if (j < struc()->pipenum)
			pipe(pfd);
		struc()->pid[j] = fork();
		struc()->is_child = 1;
		if (struc()->pid[j] == -1)
			return ;
		if (!struc()->pid[j])
		{
			if (struc()->pipenum > 0)
			{
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
				if (j < (struc()->number_of_cmd - 1))
					dup2(pfd[1], STDOUT_FILENO);
				close(pfd[0]);
				close(pfd[1]);
			}
			close(fd_out);
			exec(ft_split(cmd[i], 32));
		}
		if (struc()->pipenum > 0)
			close(pfd[1]);
		fd_in = pfd[0];
		j++;
		i++;
	}
	if (struc()->pipenum > 0)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(pfd[0]);
		close(pfd[1]);
	}
	close(fd_out);
	wait_end_cmd();
	free(struc()->pid);
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
