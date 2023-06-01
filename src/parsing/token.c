#include "../../include/parsing.h"

static int	command_separator(char *str, char **res, int i)
{
	int		len;
	char	*temp;

	temp = NULL;
	len = ft_strlen_until(&str[i], "\"\'-\0", 1);
	temp = ft_calloc(len + 1, sizeof(char));
	ft_sstrlcpy(temp, &str[i], len);
	*res = ft_sstrjoin(*res, temp);
	ft_xfree(temp);
	while (str[i] && (str[i] != DOUBLE_QUOTE && str[i] != SINGLE_QUOTE
			&& str[i] != MINUS && str[i] != SPACE))
		i++;
	return (i);
}

static int	option_separator(char *str, char **res, int i)
{
	int		len;
	char	*temp;

	temp = NULL;
	len = ft_strlen_until(&str[i], "\"\'-\0", 1);
	temp = ft_calloc(len + 1, sizeof(char));
	ft_sstrlcpy(temp, &str[i], len);
	*res = ft_sstrjoin(*res, temp);
	ft_xfree(temp);
	while (str[i] && str[i] != SPACE)
		i++;
	return (i);
}

static int	argument_seperator(char *str, char **res, int i)
{
	int		len;
	char	*temp;

	temp = NULL;
	printf ("%s\n", &str[i]);
	len = ft_strlen_until(&str[i], "\0", 1);
	printf("%d\n", len);
	temp = ft_calloc(len + 1, sizeof(char));
	ft_sstrlcpy(temp, &str[i], len);
	if (*res != NULL)
	{
		*res = ft_realloc(*res, sizeof(char), ft_strlen(*res),
				ft_strlen(*res) + 1);
		*res[ft_strlen(*res)] = SPACE;
	}
	*res = ft_sstrjoin(*res, temp);
	ft_xfree(temp);
	while (str[i] && str[i] != SPACE)
			i++;
	printf ("INDEX: %d\n", i);
	return (i);
}

void	token_separator(char *str, t_token *th)
{
	int	i;

	i = 0;
	th->token = ft_calloc(2, sizeof(char *));
	while (str[i])
	{
		if (th->token[th->index] == NULL && ft_isalpha(str[i]))
		{
			do_need_realloc(th, &th->index);
			i = command_separator(str, &th->token[th->index], i);
			th->index++;
		}
		if (th->token[th->index] == NULL && str[i] == MINUS)
		{
			do_need_realloc(th, &th->index);
			i = option_separator(str, &th->token[th->index], i);
			th->index++;
		}
		if (str[i] && (str[i] == DOUBLE_QUOTE
				|| str[i] == SINGLE_QUOTE || ft_isalpha(str[i])))
		{
			do_need_realloc(th, &th->index);
			i = argument_seperator(str, &th->token[th->index], i);
			th->index++;
		}
		if (str[i])
			i++;
	}
}
