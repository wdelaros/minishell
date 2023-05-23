#include "../../include/parsing.h"

char	**string_handler(char *input)
{
	t_token	token;

	if (if_all_quote_closed(input, DOUBLE_QUOTE) == 0
		|| if_all_quote_closed(input, SINGLE_QUOTE) == 0)
		printf ("MARDE\n");
	token_separator(input, &token);
	return (token.token);
}

void	token_separator(char *str, t_token *token)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	temp = NULL;
	token->token = ft_calloc(4, sizeof(char *));
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
		{
			len = ft_strlen_until(&str[i], "\"\'-");
			temp = ft_calloc(len + 1, sizeof(char));
			ft_sstrlcpy(temp, &str[i], len);
			token->token[0] = ft_sstrjoin(token->token[0], temp);
			ft_xfree(temp);
			while (str[i] && (str[i] != DOUBLE_QUOTE && str[i] != SINGLE_QUOTE && str[i] != MINUS))
				i++;
		}
		if (str[i] == MINUS)
		{
			len = ft_strlen_until(&str[i], " ");
			temp = ft_calloc(len + 1, sizeof(char));
			ft_sstrlcpy(temp, &str[i], len + 1);
			token->token[1] = ft_sstrjoin(token->token[1], temp);
			ft_xfree(temp);
			while (str[i] && str[i] != SPACE)
				i++;
		}
		if (str[i] && (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE))
		{
			len = ft_strlen_until(&str[i], "\"\'-");
			temp = ft_calloc(len + 1, sizeof(char));
			ft_sstrlcpy(temp, &str[i], len + 2);
			token->token[2] = ft_sstrjoin(token->token[2], temp);
			ft_xfree(temp);
			while (str[i] && (!(str[i - 1] == DOUBLE_QUOTE && str[i] == SPACE) || !(str[i - 1] == SINGLE_QUOTE && str[i] == SPACE)))
				i++;
		}
		if (str[i])
			i++;
	}
	printf ("%s\n", token->token[0]);
	printf ("%s\n", token->token[1]);
	printf ("%s\n", token->token[2]);
}

int	if_all_quote_closed(char *str, int quote)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == quote && flag == 0) // QUOTE OPEN
		{
			flag = 1;
			i++;
		}
		if (str[i] == quote && flag == 1) // QUOTE CLOSED
		{
			flag = 0;
			i++;
		}
		i++;
	}
	if (flag == 0)
		return (1);
	return (0);
}