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

int	ft_unset(char **unset)
{
	int		i;
	int		j;
	char	**env_cpy;
	char	**env;

	env = struc()->envp;
	struc()->exit_code = 0;
	if (!unset)
		return (struc()->exit_code);
	j = 1;
	while (unset[j])
	{
		i = 0;
		if (ft_strsearch(unset[j], 32))
		{
			ft_dprintf(2, "minishell: unset: `%s': not a valid identifier\n", unset[j]);
			struc()->exit_code = 1;
			j++;
			continue ;
		}
		unset[j] = ft_fstrjoin(unset[j], "=");
		while (env[i])
		{
			if (!ft_strncmp(unset[j], env[i], ft_strlen(unset[j])))
			{
				env_cpy = cpy_environement(NULL, env);
				ft_free_null(env);
				env = ft_calloc(ft_strlen_double(env_cpy), sizeof(char *));
				if (!env)
					return (struc()->exit_code);
				env = reset(env, unset[j], env_cpy);
				ft_free_null(env_cpy);
				i--;
			}
			i++;
		}
		j++;
	}
	struc()->envp = env;
	return (struc()->exit_code);
}
