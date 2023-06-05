#include "../../include/parsing.h"

/// @brief Seperate the command from the raw input.
/// @param str raw input.
/// @param res the command seperated from the input.
/// @param i current index in the raw input.
/// @return Index after the command has been seperated.
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
	i++;
	return (i);
}

/// @brief Seperate the option from the raw input.
/// @param str raw input.
/// @param res the option seperated from the input.
/// @param i current index in the raw input.
/// @return Index after the option has been seperated.
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
	while (str[i] == SPACE)
		i++;
	return (i);
}

/// @brief Seperate the argument from the raw input.
/// @param str raw input.
/// @param res the argument seperated from the input.
/// @param i current index in the raw input.
/// @return Index after the argument has been seperated.
static int	argument_seperator(char *str, char **res, int i)
{
	*res = copy_and_join(str, i);
	if (str[i] == DOUBLE_QUOTE)
	{
		i++;
		while (str[i] && str[i] != DOUBLE_QUOTE)
			i++;
		i++;
	}
	else if (str[i] == SINGLE_QUOTE)
	{
		i++;
		while (str[i] && str[i] != SINGLE_QUOTE)
			i++;
		i++;
	}
	else
		while (str[i] && str[i] != DOUBLE_QUOTE && str[i] != SINGLE_QUOTE)
			i++;
	return (i);
}

static void	token_if(char *str, t_token *th, int i)
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
	if (str[i] && (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE
			|| ft_isalpha(str[i]) || str[i] == SPACE))
	{
		do_need_realloc(th, &th->index);
		i = argument_seperator(str, &th->token[th->index], i);
		th->index++;
	}
}

/// @brief Handle the seperation of the raw input.
/// @param str raw input.
/// @param th token struct.
/// @return No return value.
void	token_separator(char *str, t_token *th)
{
	int	i;

	i = 0;
	th->token = ft_calloc(2, sizeof(char *));
	while (str[i])
	{
		token_if(str, th, i);
		if (str[i] == SPACE)
			i++;
	}
}
