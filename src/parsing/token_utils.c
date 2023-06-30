#include "../../include/parsing.h"

int	token_handler_quote(char *str, int i)
{
	if (str[i] == DOUBLE_QUOTE)
		while (str[i] && !(str[i - 1] == DOUBLE_QUOTE && str[i] == SPACE))
			i++;
	else if (str[i] == SINGLE_QUOTE)
		while (str[i] && !(str[i - 1] == SINGLE_QUOTE && str[i] == SPACE))
			i++;
	else
		while (str[i] && str[i] != SPACE)
			i++;
	return (i);
}

int	token_len_quote(char *str)
{
	int	len;

	len = 0;
	if (str[len] == DOUBLE_QUOTE)
	{
		len = ft_strlen_until(str, "\"", 0);
		len++;
	}
	else if (str[len] == SINGLE_QUOTE)
	{
		len = ft_strlen_until(str, "\'", 0);
		len++;
	}
	else
		len = ft_strlen_until(str, "\"\'|><\0", 0);
	return (len);
}

int	ft_strlen_until_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == SPACE)
			return (i);
		i++;
	}
	return (i);
}

char	*copy_and_join(char *str, int i)
{
	int		len;
	char	*res;
	char	*temp;

	res = NULL;
	temp = NULL;
	len = token_len_quote(&str[i]);
	temp = ft_calloc(len + 1, sizeof(char));
	if (!temp)
		return (NULL);
	ft_sstrlcpy(temp, &str[i], len);
	res = ft_strdup(temp);
	ft_xfree(temp);
	return (res);
}

int	is_command(char *str, int i, t_input *ih)
{
	if (str[i] && (str[i] == PIPE || str[i] == RED_IN || str[i] == RED_OUT
			|| ft_isspace(str[i]) == YES))
		return (NO);
	if (i == 0 && ft_isspace(str[i]) == NO)
		return (YES);
	while (ih->next)
		ih = ih->next;
	ih = ih->prev;
	if (ih && ih->token == 3)
		return (YES);
	while (str[i] && str[i - 1])
	{
		i--;
		if (str[i] == '\0' || str[i] == PIPE
			|| str[i] == RED_IN || str[i] == RED_OUT)
			return (YES);
		else if (ft_isspace(str[i]) == 0)
			return (NO);
	}
	return (YES);
}

int	ft_strlen_until_alpha(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == YES)
			return (len);
		len++;
		i++;
	}
	return (len);
}

char	*red_handler(char *str, int *i)
{
	size_t	len;
	char	*res;

	len = (*i);
	while (str[len] && (str[len] == RED_IN || str[len] == RED_OUT))
		len++;
	while (str[len] && str[len] == SPACE)
		len++;
	if (str[len] == DOUBLE_QUOTE || str[len] == SINGLE_QUOTE)
	{
		if (str[len] == DOUBLE_QUOTE)
			len += ft_strlen_until(&str[len], "\"", 0);
		else
			len += ft_strlen_until(&str[len], "\'", 0);
	}
	else
	{
		while (str[len] && ft_isascii(str[len]) == YES && str[len] != SPACE
			&& str[len] != PIPE && str[len] != RED_IN && str[len] != RED_OUT)
			len++;
	}
	// while (str[len] && ft_isascii(str[len]) == YES && str[len] != SPACE
	// 	&& str[len] != PIPE && str[len] != RED_IN && str[len] != RED_OUT)
	// 	len++;
	res = ft_calloc((len - (*i)) + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, &str[*i], len - (*i) + 1);
	(*i) = len;
	return (res);
}
