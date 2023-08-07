#include "../../include/built_in.h"

char	**cpy_environement(char **env, char **cpy_env)
{
	int	i;

	i = 0;
	while (cpy_env[i])
		i++;
	env = ft_calloc(i + 1, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (cpy_env[i])
	{
		env[i] = ft_strdup(cpy_env[i]);
		i++;
	}
	return (env);
}

static char	**reset(char **env, char *variable, char **env_cpy)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_cpy[j])
	{
		if (ft_strncmp(variable, env_cpy[j], ft_strlen(variable)))
		{
			env[i] = ft_strdup(env_cpy[j]);
			i++;
		}
		j++;
	}
	return (env);
}

static void	checkexport(char *var, int j, t_data *data)
{
	char	**export;
	int		i;

	while (++j < 2)
	{
		i = 0;
		while (data->export[i])
		{
			if (!ft_strncmp(var, data->export[i], ft_strlen(var) + (1 - j)))
			{
				export = cpy_environement(NULL, data->export);
				ft_free_null(data->export);
				data->export = ft_calloc(ft_strlen_double(export), \
				sizeof(char *));
				if (!data->export)
					return ;
				data->export = reset(data->export, var, export);
				ft_free_null(export);
				i--;
			}
			i++;
		}
		var = ft_fstrjoin(var, "=");
	}
	free(var);
}

int	ft_unset(char **unset, t_data *data)
{
	int		i;
	int		j;
	char	**env_cpy;

	data->exit_code = 0;
	if (!unset)
		return (data->exit_code);
	j = 1;
	while (unset[j])
	{
		i = 0;
		if ((!ft_isalpha(unset[j][0]) && unset[j][0] != '_') || \
		ft_strsearch(unset[j], 32))
		{
			ft_dprintf(2, "%s unset: `%s': %s\n", MINI, unset[j], ERR);
			data->exit_code = 1;
			j++;
			continue ;
		}
		checkexport(ft_strdup(unset[j]), -1, data);
		unset[j] = ft_fstrjoin(unset[j], "=");
		while (data->envp[i])
		{
			if (!ft_strncmp(unset[j], data->envp[i], ft_strlen(unset[j])))
			{
				env_cpy = cpy_environement(NULL, data->envp);
				ft_free_null(data->envp);
				data->envp = ft_calloc(ft_strlen_double(env_cpy), \
				sizeof(char *));
				if (!data->envp)
					return (1);
				data->envp = reset(data->envp, unset[j], env_cpy);
				ft_free_null(env_cpy);
				i--;
			}
			i++;
		}
		j++;
	}
	return (data->exit_code);
}
