/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:32 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/11 16:55:18 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	is_there_after_here(char *input, int i, char c)
{
	(void)c;
	while (i > 0)
	{
		if (i > 0)
			i--;
		if (i > 0 && input[i] == RD_I && input[i - 1] && input[i - 1] == RD_I)
			return (YES);
		if (ft_isspace(input[i]) == NO)
			return (NO);
	}
	return (NO);
}

static void	print_inside_quote(char **input, size_t *i, char **res, size_t *j)
{
	char	c;

	c = (*input)[*i - 1];
	while (*i < ft_strlen((*input)) && (*input)[*i] && (*input)[*i] != c)
	{
		(*res)[*j] = (*input)[*i];
		if ((*res)[*j] == SPACE)
			(*res)[*j] = 31;
		(*j)++;
		(*i)++;
	}
	if ((*input)[*i] == c)
		(*i)++;
}

static void	print_inside_heredoc(char **input, size_t *i, char **res, size_t *j)
{
	char	c;
	int		max_len;

	c = (*input)[*i];
	if (c == DQ)
		max_len = ft_strlen_until(*input, *i, "\"");
	else if (c == SQ)
		max_len = ft_strlen_until(*input, *i, "\'");
	while (*i < ft_strlen(*input) && *i <= (size_t)max_len)
	{
		(*res)[*j] = (*input)[*i];
		if ((*res)[*j] == SPACE)
			(*res)[*j] = 31;
		(*j)++;
		(*i)++;
	}
}

char	*quote_interpreter(char *input, size_t i, size_t j, char c)
{
	char	*res;

	res = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	while (i < ft_strlen(input))
	{
		c = input[i];
		if ((c == DQ || c == SQ) && is_there_after_here(input, i, c) == YES)
			print_inside_heredoc(&input, &i, &res, &j);
		else if ((c == DQ || c == SQ) && ++i)
		{
			res[j++] = 30;
			print_inside_quote(&input, &i, &res, &j);
			res[j++] = 30;
		}
		else if (input[i] && input[i] != DQ && input[i] != SQ)
			res[j++] = input[i++];
	}
	free(input);
	return (res);
}

char	*quote_handler(char *input)
{
	char	*res;

	res = NULL;
	if (is_quote(input) == YES)
		res = quote_interpreter(input, 0, 0, 'a');
	else
		return (input);
	return (res);
}
