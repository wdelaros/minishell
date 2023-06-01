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
		while (str[len] && !(str[len] == DOUBLE_QUOTE
				&& (str[len + 1] == '\0' || str[len + 1] == SPACE)))
			len++;
	else if (str[len] == SINGLE_QUOTE)
		while (str[len] && !(str[len] == SINGLE_QUOTE
				&& (str[len + 1] == '\0' || str[len + 1] == SPACE)))
			len++;
	else
		while (str[len] && ft_isalpha(str[len])
			&& (str[len + 1] != '\0' || str[len + 1] != SPACE))
			len++;
	len++;
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
