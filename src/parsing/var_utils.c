/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:40 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/05 17:41:14 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	free_guedille(char *temp, char *str, char *var)
{
	ft_xfree(temp);
	ft_xfree(str);
	ft_xfree(var);
}

char	*change_input_with_var(char *str, char **env, int i, t_var t_var)
{
	int		j;
	char	*var;
	char	*new;
	char	*temp;

	j = 0;
	var = ft_calloc (t_var.maxlen + 1, sizeof(char));
	while (str[i] && (ft_isalnum(str[i]) == YES || str[i] == '?'
			|| str[i] == '_'))
		var[j++] = str[i++];
	if (ft_strncmp(var, "?", 1) == 0)
	{
		temp = ft_strdup(var + 1);
		ft_xfree(var);
		var = ft_fstrjoin(ft_itoa(t_var.err_code), temp);
	}
	else
	{
		temp = ft_fstrjoin(var, "=");
		var = ft_strdup(get_var_parsing(temp, env));
	}
	ft_str_search_replace(&str, i, var);
	new = ft_strdup(str);
	free_guedille(temp, str, var);
	return (new);
}
