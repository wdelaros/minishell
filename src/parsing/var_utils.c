#include "../../include/parsing.h"

char	*get_var_parsing(char *var, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, ft_strlen(var)))
			return (envp[i] + ft_strlen(var));
		i++;
	}
	return (NULL);
}

static int	size_of_guedille(char *temp, int *i)
{
	int	size;
	int	j;

	size = 0;
	j = (*i);
	printf ("DE KOSSÉ: %s	%d\n", temp, *i);
	if (temp[j] == '$')
	{
		size++;
		j--;
	}
	while (temp[j] && temp[j - 1] && temp[j] != '$')
	{
		size++;
		j--;
	}
	*i = j;
	return (size);
}

void	ft_str_search_replace(char **str, int start, char *replace)
{
	int		i;
	int		size;
	char	*res;
	char	*temp;

	i = start;
	res = NULL;
	temp = *str;
	size = size_of_guedille(temp, &i);
	printf ("SIZE?: %d\n", size);
	res = ft_calloc(ft_strlen(temp) + (ft_strlen(replace) - size),
			sizeof(char));
	ft_strlcpy(res, temp, i + 1);
	printf ("PREMIER CPY: %s\n", res);
	if (!replace)
	{
		res = ft_fstrjoin(res, &temp[start]);
		ft_xfree(*str);
		*str = ft_strdup(res);
		ft_xfree(res);
		return ;
	}
	res = ft_fstrjoin(res, replace);
	printf ("DEUXIEME CPY: %s\n", res);
	res = ft_fstrjoin(res, &temp[start]);
	printf ("TROISIEME CPY: %s\n", res);
	ft_xfree(*str);
	*str = ft_strdup(res);
	ft_xfree(res);
}

char	*wagadoo_machine_2(char *str, char **env, int i, int max_len)
{
	int		j;
	char	*var;
	char	*new;
	char	*temp;

	j = 0;
	var = ft_calloc (max_len + 1, sizeof(char));
	while (str[i] && ft_isalpha(str[i]) == YES)
		var[j++] = str[i++];
	temp = ft_fstrjoin(var, "=");
	var = ft_strdup(get_var_parsing(temp, env));
	ft_str_search_replace(&str, i, var);
	new = ft_strdup(str);
	ft_xfree(temp);
	ft_xfree(str);
	ft_xfree(var);
	return (new);
}
