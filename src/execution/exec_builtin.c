#include "../../include/execution.h"

int	is_builtin(char	**cmd)
{
	if (!ft_strcmp(cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (1);
	else if (!ft_strcmp(cmd[0], "export"))
		return (1);
	// else if (!ft_strcmp(cmd[0], "echo"))
	// 	return (2);
	else if (!ft_strcmp(cmd[0], "env"))
		return (2);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (2);
	return (0);
}

void	redir_builtin(t_cmd	*lcmd, char	***cmd, int fd_out, int *pfd)
{
	if (pfd)
	{
		redir_input(&lcmd, &pfd, cmd, fd_out);
		redir_output(lcmd, &pfd, e_struc()->tmp_i);
		if (struc()->pipenum > 0)
		{
			close(pfd[0]);
			close(pfd[1]);
		}
	}
}

void	run_builtin(t_cmd	*lcmd, char	***cmd, int fd_out, int	*pfd)
{
	t_data	*data;

	data = struc();
	redir_builtin(lcmd, cmd, fd_out, pfd);
	if (!ft_strcmp(lcmd->cmd[0], "unset"))
		data->exit_code = ft_unset(lcmd->cmd, data);
	else if (!ft_strcmp(lcmd->cmd[0], "env"))
		data->exit_code = ft_env(data->envp);
	else if (!ft_strcmp(lcmd->cmd[0], "export"))
		data->exit_code = export(lcmd->cmd, data);
	else if (!ft_strcmp(lcmd->cmd[0], "pwd"))
		data->exit_code = pwd();
	// else if (!ft_strcmp(lcmd->cmd[0], "echo"))
	// 	data->exit_code = echo();
	else if (!ft_strcmp(lcmd->cmd[0], "cd"))
		data->exit_code = cd(lcmd->cmd[1]);
	else if (!ft_strcmp(lcmd->cmd[0], "exit"))
		ft_exit(lcmd->cmd, lcmd, cmd, fd_out);
}