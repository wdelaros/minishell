#include "../../include/parsing.h"

static int	command_separator(char *str, char *res, int i)
{
	int		len;
	char	*temp;

	temp = NULL;
	len = ft_strlen_until(&str[i], "\"\'-\0", 1);
	temp = ft_calloc(len + 1, sizeof(char));
	ft_sstrlcpy(temp, &str[i], len);
	if (token_handler->token[0] != NULL)
	{
		token_handler->token[0] = ft_realloc(token_handler->token[0],
				sizeof(char), ft_strlen(token_handler->token[0]),
				ft_strlen(token_handler->token[0]) + 1);
		token_handler->token[0][ft_strlen(token_handler->token[0])] = SPACE;
	}
	token_handler->token[0] = ft_sstrjoin(token_handler->token[0], temp);
	ft_xfree(temp);
	while (str[i] && (str[i] != DOUBLE_QUOTE && str[i] != SINGLE_QUOTE
			&& str[i] != MINUS && str[i] != SPACE))
		i++;
	return (i);
}

static int	option_separator(char *str, char *res, int i)
{
	int		len;
	char	*temp;

	temp = NULL;
	len = ft_strlen_until(&str[i], "\"\'-\0", 1);
	temp = ft_calloc(len + 1, sizeof(char));
	ft_sstrlcpy(temp, &str[i], len);
	token_handler->token[1] = ft_sstrjoin(token_handler->token[1], temp);
	ft_xfree(temp);
	while (str[i] && str[i] != SPACE)
		i++;
	return (i);
}

static int	argument_seperator(char *str, char *res, int i)
{
	int		len;
	char	*temp;

	temp = NULL;
	len = ft_strlen_until(&str[i], "\"\'-\0", 1);
	temp = ft_calloc(len + 1, sizeof(char));
	ft_sstrlcpy(temp, &str[i], len);
	token_handler->token[2] = ft_sstrjoin(token_handler->token[2], temp);
	ft_xfree(temp);
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

void	token_separator(char *str, t_token *th)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (th->token[th->index] == NULL)
		{

			i = command_separator(str, th, i);
		}
		if (th->token[th->index] == NULL && str[i] == MINUS)
		{

			i = option_separator(str, th, i);
		}
		if (str[i] && (str[i] == DOUBLE_QUOTE
				|| str[i] == SINGLE_QUOTE || ft_isalpha(str[i])))
		{

			i = argument_seperator(str, th, i);
		}
		if (str[i])
			i++;
	}
}
