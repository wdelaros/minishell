#include "../../include/parsing.h"

static char	*find_var(char *var, char **env, size_t len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(&var[1], env[i], len - 1) == 0)
			break ;
		i++;
	}
	return (env[i]);
}

static size_t	var_len(char *env)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] == '=')
		i++;
	while (env[i])
	{
		i++;
		len++;
	}
	printf ("VAR:%s	", env);
	printf ("LEN DE LA VAR:%zu\n", len);
	return (len);
}

static char	*copy_var(char *input, char *env)
{
	char	*copy;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	copy = ft_strdup(input);
	printf ("LEN DU NOUVEAU INPUT:%lu\n", ft_strlen(copy) + var_len(env));
	ft_xfree(input);
	input = ft_calloc(ft_strlen(copy) + var_len(env) + 1, sizeof(char));
	while (copy[i])
	{
		if (copy[i] == '$')
		{
			while (env[k] != '=')
				k++;
			while (env[++k])
			{
				input[j] = env[k];
				j++;
			}
			while (copy[i] && copy[i] != SPACE)
				i++;
		}
		input[j] = copy[i];
		j++;
		i++;
	}
	printf("NEW INPUT:%s\n", input);
	ft_xfree(copy);
	return (input);
}

char	*var_handler(char *input, char **env)
{
	int		pos;
	size_t	len;
	char	*check_env;

	pos = 0;
	len = 0;
	while (input[pos] && input[pos] != '$')
		pos++;
	if (input[pos - 1] == SINGLE_QUOTE)
		return (input);
	printf ("VERIF FAIT!\n");
	len = ft_strlen_until_space(&input[pos]);
	check_env = ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(check_env, &input[pos], len + 1);
	check_env = find_var(check_env, env, len);
	printf ("TROUVER LA VAR:%s\n", check_env);
	input = copy_var(input, check_env);
	printf("INPUT:%s\n", input);
	//free(check_env);
	return (input);
}
