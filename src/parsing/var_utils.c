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
	res = ft_calloc(ft_strlen(temp) + (ft_strlen(replace) - size),
			sizeof(char));
	ft_strlcpy(res, temp, i + 1);
	if (!replace)
	{
		res = ft_fstrjoin(res, &temp[start]);
		ft_xfree(*str);
		*str = ft_strdup(res);
		ft_xfree(res);
		return ;
	}
	res = ft_fstrjoin(res, replace);
	res = ft_fstrjoin(res, &temp[start]);
	ft_xfree(*str);
	*str = ft_strdup(res);
	ft_xfree(res);
}

char	*change_input_with_var(char *str, char **env, int i, t_var t_var)
{
	int		j;
	char	*var;
	char	*new;
	char	*temp;

	j = 0;
	temp = NULL;
	var = ft_calloc (t_var.maxlen + 1, sizeof(char));
	while (str[i] && (ft_isalnum(str[i]) == YES || str[i] == '?'))
		var[j++] = str[i++];
	if (ft_strncmp(var, "?", 1) == 0)
		var = ft_fstrjoin(ft_itoa(t_var.err_code), var + 1);
	else
	{
		temp = ft_fstrjoin(var, "=");
		var = ft_strdup(get_var_parsing(temp, env));
	}
	ft_str_search_replace(&str, i, var);
	new = ft_strdup(str);
	ft_xfree(temp);
	ft_xfree(str);
	ft_xfree(var);
	return (new);
}
