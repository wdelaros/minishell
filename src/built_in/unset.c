#include "../../include/minishell.h"

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

int	ft_unset(char *variable)
{
	int		i;
	int		j;
	char	**unset;
	char	**env_cpy;
	char	**env;

	env = struc()->envp;
	unset = ft_split(variable, 32);
	if (!unset)
		return (0);
	j = 0;
	while (unset[j])
	{
		i = 0;
		unset[j] = ft_fstrjoin(unset[j], "=");
		while (env[i])
		{
			if (!ft_strncmp(unset[j], env[i], ft_strlen(unset[j])))
			{
				env_cpy = cpy_environement(NULL, env);
				ft_free_null(env);
				env = ft_calloc(ft_strlen_double(env_cpy), sizeof(char *));
				if (!env)
					return (0);
				env = reset(env, unset[j], env_cpy);
				ft_free_null(env_cpy);
			}
			i++;
		}
		j++;
	}
	struc()->envp = cpy_environement(NULL, env);
	ft_free_null(env);
	ft_free_null(unset);
	return (0);
}
