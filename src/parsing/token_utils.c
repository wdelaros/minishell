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
		len = ft_strlen_until(str, "\"\0", 0);
		len++;
	}
	else if (str[len] == SINGLE_QUOTE)
	{
		len = ft_strlen_until(str, "\'\0", 0);
		len++;
	}
	else
		len = ft_strlen_until(str, "\"\'\0", 0);
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
	ft_sstrlcpy(temp, &str[i], len);
	res = ft_sstrjoin(res, temp);
	ft_xfree(temp);
	return (res);
}

char	**convert_list_to_string(t_input **ih)
{
	char	**res;
	int		i;
	int		len;

	i = 0;
	res = NULL;
	len = 0;
	len = node_len((*ih));
	res = ft_calloc(len, sizeof(char *));
	while ((*ih))
	{
		res[i] = ft_strdup((*ih)->input);
		i++;
		(*ih) = (*ih)->next;
	}
	return (res);
}