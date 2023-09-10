#include "../../include/parsing.h"

static int	skip_quote(char *input, int i, int quote)
{
	i++;
	if (quote == 1)
		while (input[i] && input[i] != SINGLE_QUOTE)
			i++;
	else if (quote == 2)
		while (input[i] && input[i] != DOUBLE_QUOTE)
			i++;
	return (i);
}

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
			*input = wagadoo_machine_2(*input, env, i, max_len);
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
	//printf ("STRING DE LA PATANTE: %s\n", str);
	//printf ("TRUC DE LA PATANTE: %d\n", len);
	res = ft_calloc((ft_strlen(str) - len + 1) + 1, sizeof(char));
	ft_strlcpy(res, str, k + 1);
	k += len + 1;
	res = ft_fstrjoin(res, &str[k]);
	ft_xfree(str);
	return (res);
}

static char	*wagadoo_machine_3(char *str, int start, char *var)
{
	char	*res;

	res = ft_calloc(start, sizeof(char));
	ft_strlcpy(res, str, start + 1);
	printf ("PREMIER CPY: %s\n", res);
	res = ft_fstrjoin(res, var);
	printf ("DEUXIEME CPY: %s\n", res);
	if (str[start])
		start++;
	while (str[start] && str[start] != '$')
		start++;
	res = ft_fstrjoin(res, &str[start]);
	printf ("TROISIEME CPY: %s\n", res);
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
	//printf ("UWU: %d\n", i);
	//printf ("SADASDASDASDASD: %s	%d\n", *input, i);
	if (var == NULL)
		*input = clean_var(*input, i);
	else
		*input = wagadoo_machine_3(*input, start, var);
	//printf ("%s\n", *input);
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
