#include "../../include/parsing.h"

static char	*get_var(char *var, char **envp)
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

// static int	do_search(char *str, char *search)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (ft_strncmp(&str[i], search, ft_strlen(search)) == 0)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// static void	do_replace(char *str, char *res, int start, int size)
// {
// 	int	i;

// 	i = 0;
// 	(void)size;
// 	ft_strlcpy(res, str, (ft_strlen(str) - start) + 1);
// }

void	ft_str_search_replace(char **str, int end, char *replace)
{
	int		i;
	int		size;
	char	*res;
	char	*temp;

	i = end;
	size = 0;
	res = NULL;
	temp = *str;
	if (temp[i] == '$')
	{
		size++;
		i--;
	}
	while (temp[i] && temp[i - 1] && temp[i] != '$')
	{
		size++;
		i--;
	}
	res = ft_calloc(ft_strlen(temp) + (ft_strlen(replace) - size), sizeof(char));
	ft_strlcpy(res, temp, i + 1);
	if (!replace)
	{
		ft_xfree(*str);
		*str = ft_strdup(res);
		ft_xfree(res);
		return ;
	}
	res = ft_fstrjoin(res, replace);
	res = ft_fstrjoin(res, &temp[end]);
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
	var = ft_strdup(get_var(temp, env));
	ft_str_search_replace(&str, i, var);
	new = ft_strdup(str);
	ft_xfree(temp);
	ft_xfree(str);
	ft_xfree(var);
	return (new);
}
