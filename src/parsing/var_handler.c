/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:37 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/12 12:56:05 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	double_quote_condition(char **input, char **env, int i, int err)
{
	int		start;
	t_var	t_var;

	t_var.err_code = err;
	t_var.maxlen = skip_quote(*input, i, DQ);
	start = i;
	while (i < t_var.maxlen)
	{
		start = i;
		if ((*input)[i] && (*input)[i] == '$' && i++)
		{
			if ((*input)[i] == DQ || (ft_isalnum((*input)[i]) == NO
				&& (*input)[i] != '?' && (*input)[i] != '_')
				|| (*input)[i] == '$')
				continue ;
			else
			{
				*input = change_input_with_var(*input, env, i, t_var);
				i = start;
				t_var.maxlen = skip_quote(*input, start, DQ);
			}
		}
		i++;
	}
	return (i);
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
			&& str[start] != DQ && str[start] != SQ
			&& (ft_isalnum(str[start]) || str[start] == '_'
				|| str[start] == '?')))
		start++;
	res = ft_fstrjoin(res, &str[start]);
	ft_xfree(var);
	ft_xfree(str);
	return (res);
}

int	normal_condition(char **input, char **env, int i, int err)
{
	char	*temp;
	char	*var;
	int		j;
	int		start;

	temp = ft_strdup(*input);
	start = i;
	j = 0;
	if (!temp[i] || (temp[i + 1] && temp[i + 1] == '$'))
		return (free(temp), i + 1);
	var = ft_calloc(ft_strlen(temp), sizeof(char));
	if (valid_var(&temp[i]) == NO)
		return (free(var), free(temp), i + 2);
	if (temp[i] == '$')
		i++;
	while (temp[i] && (ft_isalnum(temp[i]) == YES || temp[i] == '?'
			|| temp[i] == '_'))
		var[j++] = temp[i++];
	var = return_var(var, err, env);
	if (var == NULL)
		*input = clean_var(*input, i);
	else
		*input = put_var_in_input(*input, start, var);
	ft_xfree(temp);
	return (start);
}

void	var_handler(char **input, char **env, int err_code)
{
	int		i;

	i = 0;
	while (i < (int)ft_strlen(*input))
	{
		if ((*input)[i] == '<' && (*input)[i + 1] && (*input)[i + 1] == '<')
		{
			while ((*input)[i] && (*input)[i] != DQ && (*input)[i] != SQ)
				i++;
			if ((*input)[i] == DQ || (*input)[i] == SQ)
				i = skip_quote(*input, i, (*input)[i]);
		}
		else if ((*input)[i] == '$')
			i = normal_condition(input, env, i, err_code);
		else if ((*input)[i] == DQ)
			i = double_quote_condition(input, env, i, err_code);
		else if ((*input)[i] == SQ)
			i = skip_quote(*input, i, SQ);
		if (i < (int)ft_strlen(*input) && (*input)[i] && (*input)[i] != '$'
			&& (*input)[i] != SQ
			&& (*input)[i] != DQ)
			i++;
	}
}
