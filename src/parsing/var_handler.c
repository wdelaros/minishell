#include "../../include/parsing.h"

static int	double_quote_condition(char **input, char **env, int i)
{
	int		max_len;
	int		start;

	max_len = skip_quote(*input, i, 2);
	start = i;
	while (i < max_len)
	{
		if ((*input)[i] && (*input)[i] == '$' && i++)
		{
			*input = change_input_with_var(*input, env, i, max_len);
			i = start;
			max_len = skip_quote(*input, start, 2);
		}
		i++;
	}
	return (skip_quote(*input, start, 2));
}

static char	*clean_var(char *str, int k)
{
	int		len;
	char	*res;

	len = 0;
	while (str[--k] && str[k] != '$')
		len++;
	res = ft_calloc((ft_strlen(str) - len + 1) + 1, sizeof(char));
	ft_strlcpy(res, str, k + 1);
	k += len + 1;
	res = ft_fstrjoin(res, &str[k]);
	ft_xfree(str);
	return (res);
}

static char	*put_var_in_input(char *str, int start, char *var)
{
	char	*res;

	res = ft_calloc(start + 1, sizeof(char));
	ft_strlcpy(res, str, start + 1);
	res = ft_fstrjoin(res, var);
	if (str[start] == '$')
		start++;
	while (str[start] && (str[start] != '$'
			&& str[start] != DOUBLE_QUOTE && str[start] != SINGLE_QUOTE))
		start++;
	res = ft_fstrjoin(res, &str[start]);
	ft_xfree(var);
	ft_xfree(str);
	return (res);
}

static int	normal_condition(char **input, char **env, int i)
{
	char	*temp;
	char	*var;
	char	*var_temp;
	int		j;
	int		start;

	temp = ft_strdup(*input);
	start = i;
	j = 0;
	var = ft_calloc(ft_strlen(temp), sizeof(char));
	if (temp[i] == '$')
		i++;
	while (temp[i] && ft_isalpha(temp[i]) == YES)
		var[j++] = temp[i++];
	var_temp = ft_fstrjoin(var, "=");
	var = ft_strdup(get_var_parsing(var_temp, env));
	if (var == NULL)
		*input = clean_var(*input, i);
	else
		*input = put_var_in_input(*input, start, var);
	ft_xfree(var_temp);
	ft_xfree(temp);
	return (0);
}

void	var_handler(t_input **list, char **env)
{
	t_input	*temp;
	int		i;

	temp = *list;
	while (temp->next)
	{
		i = 0;
		while (temp->input[i])
		{
			if (temp->input[i] == '$')
				i = normal_condition(&temp->input, env, i);
			else if (temp->input[i] == DOUBLE_QUOTE)
				i = double_quote_condition(&temp->input, env, i);
			else if (temp->input[i] == SINGLE_QUOTE)
				i = skip_quote(temp->input, i, 1);
			if (temp->input[i] && temp->input[i] != '$')
				i++;
		}
		temp = temp->next;
	}
}
