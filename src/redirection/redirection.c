#include "../../include/minishell.h"

/*
 * <
*/
void	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	dup2(fd, 0);
	close(fd);
}

/*
 * >
*/
void	redirect_output(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
	dup2(fd, 1);
	close(fd);
}

/*
 * >>
*/
void	append_output(char	*file)
{
	int	fd;

	fd = open(file, O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
	dup2(fd, 1);
	close(fd);
}

void	count(char	**cmd)
{
	int	i;

	i = 0;
	struc()->pipenum = 0;
	struc()->number_of_cmd = 0;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "|", 2))
			struc()->pipenum++;
		else
			struc()->number_of_cmd++;
		i++;
	}
}

void	run_pipe(char	**cmd)
{
	int		status;
	int		*pfd;
	int		i;
	int		j;
	int		k;

	if (!ft_strncmp(cmd[0], "cd", 2))
	{
		chdir(cmd[1]);
		return ;
	}
	count(cmd);
	pfd = ft_calloc(2 * struc()->pipenum, sizeof(int *));
	struc()->pid = ft_calloc(struc()->pipenum, sizeof(pid_t *));
	i = 0;
	while (i < struc()->number_of_cmd - 1)
	{
		if (pipe(pfd + i * 2) == -1)
			return ;
		i++;
	}
	i = 0;
	k = 0;
	while (i < struc()->number_of_cmd + struc()->pipenum)
	{
		if (struc()->number_of_cmd > 1)
		{
			if (!ft_strncmp(cmd[i], "|", 2))
				i++;
			else if (!ft_strncmp(cmd[i], "<", 2))
			{
				i++;
				redirect_input(cmd[i]);
			}
			else if (!ft_strncmp(cmd[i], ">", 2))
			{
				i++;
				redirect_output(cmd[i]);
			}
			else if (!ft_strncmp(cmd[i], ">>", 3))
			{
				i++;
				append_output(cmd[i]);
			}
		}
		struc()->pid[k] = fork();
		struc()->is_child = 1;
		if (struc()->pid[k] == -1)
			return ;
		if (!struc()->pid[k])
		{
			if (struc()->pipenum > 0)
			{
				if (i > 0)
					dup2(pfd[(k - 1) * 2], STDIN_FILENO);
				if (i < (struc()->number_of_cmd - 1))
					dup2(pfd[k * 2 + 1], STDOUT_FILENO);
				j = 0;
				while (j < (2 * (struc()->number_of_cmd - 1)))
				{
					close(pfd[j]);
					j++;
				}
			}
			exec(ft_split(cmd[i], 32));
		}
		k++;
		i++;
	}
	i = 0;
	while (i < struc()->number_of_cmd)
	{
		waitpid(struc()->pid[i - 1], &status, 0);
		i++;
	}
}



/* void	count(char	**cmd)
{
	int	i;

	i = 0;
	struc()->pipenum = 0;
	struc()->number_of_cmd = 0;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "|", 2))
			struc()->pipenum++;
		else
			struc()->number_of_cmd++;
		i++;
	}
}

void	run_pipe(char	***cmd)
{
	int		status;
	int		*pfd;
	int		i;
	int		j;
	pid_t	*pid;

	pfd = ft_calloc(2 * struc()->pipenum, sizeof(int *));
	pid = ft_calloc(struc()->pipenum, sizeof(pid_t *));
	i = 0;
	while (i < struc()->number_of_cmd - 1)
	{
		if (pipe(pfd + i * 2) == -1)
			//error
		i++;
	}
	i = 0;
	while (i < struc()->number_of_cmd + struc()->pipenum)
	{
		pid[i] = fork();
		if (!pid[i])
		{
			if (!ft_strncmp(cmd[i][0], "<", 2))
			{
				i++;
				redirect_input(cmd[i][0]);
			}
			else if (!ft_strncmp(cmd[i][0], ">", 2))
			{
				i++;
				redirect_output(cmd[i][0]);
			}
			else if (!ft_strncmp(cmd[i][0], ">>", 3))
			{
				i++;
				append_output(cmd[i][0]);
			}
			else
			{
				if (i > 0)
					dup2(pfd[(i - 1) * 2], STDIN_FILENO);
				if (i < (struc()->number_of_cmd - 1))
					dup2(pfd[i * 2 + 1], STDOUT_FILENO);
				j = 0;
				while (j < (2 * (struc()->number_of_cmd - 1)))
				{
					close(pfd[j]);
					j++;
				}
				//exec(cmd[i]);
			}
		}
		else if (pid[i] == -1)
		{
			perror("pid");
			exit(0);
		}
		i++;
	}
	i = 0;
	while (i < struc()->number_of_cmd)
	{
		waitpid(pid[i - 1], &status, 0);
		i++;
	}
} */
