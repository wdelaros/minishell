#include "minishell.h"

/**
 * find the path for the excutable
*/
char	**findpath(t_data *data)
{
	int		i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (data->envp[i])
		data->path = ft_split(data->envp[i] + 5, ':');
	else
		return (NULL);
	i = 0;
	while (data->path[i])
	{
		data->path[i] = ft_fstrjoin(data->path[i], "/");
		i++;
	}
	if (!data->path)
		perror("Error");
	return (data->path);
}

/**
 * check if the excutable exist
*/
void	find_executable(char	**fcmd, int i)
{
	char	*tmp;

	if (!access(fcmd[0], F_OK))
	{
		struc()->cmdpath = fcmd[0];
		return ;
	}
	if (struc()->path)
	{
		while (struc()->path[i])
		{
			tmp = ft_rstrjoin(fcmd[0], struc()->path[i]);
			struc()->cmdpath = ft_strdup(tmp);
			free(tmp);
			if (!access(struc()->cmdpath, F_OK))
				return ;
			free(struc()->cmdpath);
			i++;
		}
	}
	struc()->cmdpath = NULL;
}
