#include "../../include/parsing.h"

char	**string_handler(char *input)
{
	t_token	token_handler;

	if (if_all_quote_closed(input, DOUBLE_QUOTE) == 0
		|| if_all_quote_closed(input, SINGLE_QUOTE) == 0)
		printf ("MARDE\n");
	token_separator(input, &token_handler);
	return (token_handler.token);
}

void	token_separator(char *str, t_token *token_handler)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	temp = NULL;
	token_handler->token = ft_calloc(3 + 1, sizeof(char *));
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
		{
			printf("BEGIN_COMMAND\n");
			len = ft_strlen_until(&str[i], "\"\'-\0", 1);
			printf("LEN: %d\n", len);
			temp = ft_calloc(len + 1, sizeof(char));
			ft_sstrlcpy(temp, &str[i], len);
			printf("COPY: %s\n", temp);
			token_handler->token[0] = ft_sstrjoin(token_handler->token[0], temp);
			printf("RESULT: %s\n", token_handler->token[0]);
			ft_xfree(temp);
			while (str[i] && (str[i] != DOUBLE_QUOTE && str[i] != SINGLE_QUOTE && str[i] != MINUS && str[i] != SPACE))
				i++;
		}
		if (str[i] == MINUS)
		{
			printf("BEGIN_MINUS\n");
			len = ft_strlen_until(&str[i], "\0", 1);
			printf("LEN: %d\n", len);
			temp = ft_calloc(len + 1, sizeof(char));
			ft_sstrlcpy(temp, &str[i], len);
			printf("COPY: %s\n", temp);
			token_handler->token[1] = ft_sstrjoin(token_handler->token[1], temp);
			printf("RESULT: %s\n", token_handler->token[1]);
			ft_xfree(temp);
			while (str[i] && str[i] != SPACE)
				i++;
		}
		if (str[i] && (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE))
		{
			printf("BEGIN_QUOTE\n");
			len = ft_strlen_until(&str[i], "\"\'-\0", 1);
			temp = ft_calloc(len + 1, sizeof(char));
			printf("LEN: %d\n", len);
			ft_sstrlcpy(temp, &str[i], len);
			printf("COPY: %s\n", temp);
			token_handler->token[2] = ft_sstrjoin(token_handler->token[2], temp);
			printf("RESULT: %s\n", token_handler->token[2]);
			ft_xfree(temp);
			if (str[i] == DOUBLE_QUOTE)
				while (str[i] && !(str[i - 1] == DOUBLE_QUOTE && str[i] == SPACE))
					i++;
			else if (str[i] == SINGLE_QUOTE)
				while (str[i] && !(str[i - 1] == SINGLE_QUOTE && str[i] == SPACE))
					i++;
		}
		if (str[i])
			i++;
	}
	//printf ("%s\n", token_handler->token[0]);
	//printf ("%s\n", token_handler->token[1]);
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